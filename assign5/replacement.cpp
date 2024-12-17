/**
 * Assignment 5: Page replacement algorithms
 * @file replacement.cpp
 * @author Arpita Godbole & Svetya Kopisetty
 * @brief A base class for different page replacement algorithms.
 * @version 0.1
 */

#include <iostream>
#include "replacement.h"

// TODO: Add your implementation of the Replacement member functions here

// Constructor
Replacement::Replacement(int num_pages, int num_frames)
: page_table(num_pages)
{
    page_total = num_pages;
    frame_total = num_frames;
    reference = 0;
    page_fault = 0;
    replaced_page = 0;
    frame_count = 0;
}

// Destructor
Replacement::~Replacement()
{

}

// Simulate a single page access
// @return true if it's a page fault
bool Replacement::access_page(int page_num, bool is_write)
{
    
    // TODO: Add your implementation here
    reference++;

// If the page is valid, it calls the touch_page function. 
    if (!page_table[page_num].valid && frame_count < frame_total) 
    {
        load_page(page_num);
        return true;
    }
 // If the page is not valid but free frames are available, it calls the load_page function.
    else if (!page_table[page_num].valid && frame_count >= frame_total) 
    {
        replace_page(page_num);
        return true;
    }
  // If the page is not valid and there is no free frame, it calls the replace_page function.
    else 
    {
        touch_page(page_num);
    }

    // It's not a page fault
    return false;
}

// Print out statistics of simulation
void Replacement::print_statistics() const 
{
    std::cout << "Number of references: \t\t" << reference << std::endl;
    std::cout << "Number of page faults: \t\t" << page_fault << std::endl;
    std::cout << "Number of page replacements: \t" << replaced_page << std::endl;
}
