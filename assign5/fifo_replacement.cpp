/**
 * Assignment 5: Page replacement algorithms
 * @file fifo_replacement.cpp
 * @author Arpita Godbole & Svetya Kopisetty
 * @brief A class implementing the FIFO page replacement algorithms
 * @version 0.1
 */

#include "fifo_replacement.h"

// Constructor
FIFOReplacement::FIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames) , fifo_queue() 
{

}

// Destructor
FIFOReplacement::~FIFOReplacement()
 {

    while(!fifo_queue.empty())
    {
        fifo_queue.pop_back();
    }
}

void FIFOReplacement::load_page(int page_num) 
{
    page_fault++;
    
    page_table[page_num].valid = true;
    fifo_queue.push_back(page_num);
 
    page_table[page_num].frame_num = frame_count;
    

    frame_count++;
}

int FIFOReplacement::replace_page(int page_num) 
{
    page_fault++;
    replaced_page++;

    int front_index = fifo_queue.front();
    
    page_table[front_index].valid = false;
    
    fifo_queue.erase(fifo_queue.begin()); // remove from fifo queue
    page_table[page_num].valid = true;
    fifo_queue.push_back(page_num);
    
    return 0;
}
