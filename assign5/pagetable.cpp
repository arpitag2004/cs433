/**
 * Assignment 5: Page replacement algorithms
 * @file pagetable.cpp
 * @author Arpita Godbole & Svetya Kopisetty
 * @brief This class represents a traditional pagetable data structure.
 * @version 0.1
 */

#include "pagetable.h"

// Constructor
PageTable::PageTable(int num_pages) 
{
    for (int i = 0; i < num_pages; i++) 
    {
        PageEntry page;
        pages.push_back(page);
    }
}

// Destructor
PageTable::~PageTable() 
{
    while (!pages.empty()) 
    {
        pages.pop_back();
    }
}
