/**
 * Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author Svetya Koppisetty and Arpita Godbole (TODO: your name)
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <iostream>
#include "buffer.h"
#include <unistd.h>
#include <mutex>

using namespace std;

// global buffer object
Buffer buffer;

pthread_mutex_t mtx;
pthread_attr_t attr;

sem_t filled;
sem_t blank;

// Producer thread function
// TODO: Add your implementation of the producer thread here
void *producer(void *param) {
  // Each producer insert its own ID into the buffer
  // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.

  buffer_item item = *((int *)param);
  
  while (true) {
    /* sleep for a random period of time */
    usleep(rand()%1000000);
    {
      // TODO: Add synchronization code here
     sem_wait(&blank);
     
     pthread_mutex_lock(&mtx);

      if (buffer.insert_item(item)) {
	cout << "Producer " << item << ": Inserted item " << item << endl;
	buffer.print_buffer();
      }
      else { cout << "Producer error condition"  << endl; }    // shouldn't come here
      pthread_mutex_unlock(&mtx);

      sem_post(&filled);
  }
}}
// Consumer thread function
// TODO: Add your implementation of the consumer thread here
void* consumer(void* param) 
{   
  buffer_item item;
  while (true) 
    {
      usleep(rand() % 1000000); 
      
      sem_wait(&filled);

      pthread_mutex_lock(&mtx);

      if (buffer.remove_item(&item)) {
            cout << "Consumer " << item << ": Removed item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Consumer error condition" << endl;    // shouldn't come here
        }
        pthread_mutex_unlock(&mtx);
        sem_post(&blank);
    }
}

int main(int argc, char *argv[]) {
  /* TODO: 1. Get command line arguments argv[1],argv[2],argv[3] */
  /* TODO: 2. Initialize buffer and synchronization primitives */
  /* TODO: 3. Create producer thread(s).
     
   * You should pass an unique int ID to each producer thread, starting from 1 to number of threads */
  /* TODO: 4. Create consumer thread(s) */
  /* TODO: 5. Main thread sleep */
  /*TODO: 6. Exit*/
  
  // Command-line argument parsing
  
  if (argc != 4) { //0,1,2,3
    cout << "Error, usage is:\n" << "./assign4 <sleeptime> <pthreadc> <cthreadc> \n";
    return 1;
  }
  int sleep_time = atoi(argv[1]); // main thread to sleep
  int Producers = atoi(argv[2]); //num of producer threads
  int Consumers = atoi(argv[3]); //num of consumer threads
  
  //store IDs 
  pthread_t pThreads;
  pthread_t cThreads;
  
  pthread_mutex_init(&mtx,nullptr);

  sem_init(&blank, 0, buffer.get_size());

  sem_init(&filled, 0, 0);

  // producer threads
 for (int i = 0; i < Producers; i++){ 
    int *arg = new int; //ptr
    if(arg == nullptr){return 0;}
    *arg = i + 1;
    pthread_create(&pThreads, &attr, producer, (void*) arg);
}

  // consumer threads
  for(int i = 0 ; i < Consumers ; i++){pthread_create(&cThreads, &attr, consumer, nullptr);}

  sleep(sleep_time);
  
  cout << "Exiting." << endl;
  return 0;
}
