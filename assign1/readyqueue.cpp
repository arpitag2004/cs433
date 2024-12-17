#include <iostream>
#include "readyqueue.h"

using namespace std;

//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient comments to your code
/**
 * @brief Constructor for the ReadyQueue class.
 */
 ReadyQueue::ReadyQueue() : head(nullptr), count(0) {}

/**
 *@brief Destructor
*/
ReadyQueue::~ReadyQueue() 
{
    
    Node* current = head;
    while (current != nullptr) // traverses the list to delete each node.
    {
        Node* temp = current;
        current = current->next;  
        delete temp;
    }
    head = nullptr;
    count = 0; // resets the count to assure queue is empty again.
}

/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) 
{
    // When adding a PCB to the queue, you must change its state to READY.
    pcbPtr->state =  ProcState::READY;  

    Node* newNode = new Node(pcbPtr);

    // if priority queue is empty or the new pcb has the highest priority, insert it at the head of list
    if (head == nullptr || pcbPtr->priority > head->pcb->priority) 
    {
        newNode->next = head;
        head = newNode;
    } else
    {
        // traverses the list and insert the new pcb at priority position
        Node* current = head;
        while (current->next != nullptr && current->next->pcb->priority > pcbPtr->priority) 
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    count++;

}

/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB* ReadyQueue::removePCB() 
{
     if (head == nullptr) 
    {
        return nullptr;  //checks for empty queue
    }
    Node* temp = head;
    PCB* pcb = temp->pcb;
    head = head->next;  
    pcb->state =  ProcState::RUNNING; // When removing a PCB from the queue, you must change its state to RUNNING.
    delete temp; 

    count--;
    return pcb;
}

/**
 * @brief Returns the number of elements in the queue.
 *
 * @return int: the number of PCBs in the queue
 */
int ReadyQueue::size()
{
    return count;
}

/**
 * @brief Display the PCBs in the queue.
 */
void ReadyQueue::displayAll() 
{
    Node* current = head;
    while (current != nullptr) 
    {
        cout << "\tID: " << current->pcb->id << " Priority: " << current->pcb->priority << " is in READY state." << endl;
        current = current->next;
    }

}