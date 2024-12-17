/**
 * Assignment 2: Simple UNIX Shell
 * @file pcbtable.h
 * @author Arpita Godbole and Svetya Koppisetty
 * @brief This is the main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

#define MAX_LINE 80 // The maximum length command

/**
 * @brief parse out the command and arguments from the input command separated by spaces
 *
 * @param command
 * @param args
 * @return int
 */
int parse_command(char command[], char *args[])
{
    char *token = strtok(command, " \n");  
    int i = 0;
    
    while (token != nullptr) 
    {
        args[i] = token; 
        i++;
        token = strtok(nullptr, " \n");
    }
    if (strcmp(args[i - 1], "&") != 0)
    {args[i] = nullptr; // remove  the ampresand
    } 
    return i;
}


/**
 * @brief Code that will redirect the input and output functions
 *
 * @param arguments
 * @param the number of arguments
 * @return void function
 */
void redirect(char *args[], int num_args){
  int input_fd = -1; //input flags
  int output_fd = -1; //outputs flags

  for(int i = 0; i < num_args; i++) //loop checks for < >
    {
      //input
    if(strcmp(args[i], "<") == 0)
      { 
	if(num_args > i+1)
	  {
	    input_fd = open(args[i+1], O_RDONLY); //read only open
	    if (input_fd < 0) // error message for file not opening
	      {
				perror("unable to open input file");
				exit(1);
	      }
	    dup2(input_fd, STDIN_FILENO);
	    close(input_fd);
	  }
	    args[i] = nullptr; //removes <
      }
  //output redirection
    else if (strcmp(args[i], ">") == 0)
 //checks for >
      { 
	if (num_args > (i+1))
	  { //check for file
	    output_fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC); //opens the file in  write only, create
	    if (output_fd < 0)
	      {
		perror("unable to open input file");
		exit(1);
	      }
	    //opened
	    dup2(output_fd, STDOUT_FILENO);
	    close(output_fd);
	  }
	args[i] = nullptr; //removes >
      }
    }   
}
/**
 * @brief The main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @param argc The number of arguments
 * @param argv The array of arguments
 * @return The exit status of the program
 */
int main(int argc, char *argv[])
{
    char command[MAX_LINE];       // the command that was entered
    char histrycommand[MAX_LINE]; //history command for the history feature
    char *args[MAX_LINE / 2 + 1]; // hold parsed out command line arguments
    int should_run = 1;           /* flag to determine when to exit program */

    // TODO: Add additional variables for the implementation.

    while (should_run)
      {
        printf("osh>");
        fflush(stdout);
        // Read the input command
        fgets(command, MAX_LINE, stdin);

	// Parse the input command
	//        int num_args = parse_command(command, args);

	if(strcmp(command, "exit\n") == 0) {break;} //breaks when command is exit 

	if(strcmp(command, "!!\n") == 0) //executes recent command
	  {
	    if(strlen(histrycommand) == 0) //nothing is in history
	      {
		printf("No command history\n");
		continue;
	      }
	      else
		{
		  printf("%s\n", histrycommand); //prints
		  strcpy(command, histrycommand); //copies history into command
		}
	  }
	else{strcpy(histrycommand, command);} //if they didn't enter !!,it copiescommand to historycommand
	// }
	int num_args = parse_command(command, args);

	//(1)
	int ampsand = 0; //ampersand is in
	if(strstr(args[num_args - 1], "&")) //checks second last token to see if & is in
	  {
	    args[num_args-1] = nullptr;
	    ampsand = 1; // there is &
	  }

	pid_t pid = fork(); //new process 
	if(pid < 0)
	  {
	    perror("Fails"); //error message  
	    exit(1); //exits out of program
	  }
        else if(pid == 0)//child process
	  {            
	    if(!ampsand){redirect(args, num_args);} //if there is no then redirect is called
            if (execvp(args[0],args) < 0) //(2) command is executed
	      {                  
                printf("Command not found\n"); //error message
                exit(1); //exits out of program
	      }
	  }
	//(3) parent's turn
	else
	  {
	    if(!ampsand)
		{wait(nullptr);} //check for & 	
      }
      }
    
    return 0;

}


