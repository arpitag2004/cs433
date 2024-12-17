/**
* Assignment 5: Page replacement algorithms
 * @file fifo_replacement.h
 * @author Arpita Godbole & Svetya Kopisetty
 * @brief A class implementing the FIFO page replacement algorithms
 * @version 0.1
 */

#pragma once

#include "replacement.h"

/**
 * @brief A class to simulate FIFO page replacement algorithm.
 */
class FIFOReplacement : public Replacement 
{
private:
    //fifo_queue vector
    vector <int> fifo_queue;

public:
    /**
     * @brief Constructor
     * @param num_pages Total number of available free frames.
     * @param num_frames Total number of free frames.
     */
    FIFOReplacement(int num_pages, int num_frames);

    /**
    * @brief Destructor
    */
    virtual ~FIFOReplacement();

    /**
     * @brief Access an invalid page, but free frames are available.
     * Assign the page to an available  frame, not replacement needed
     * @param page_num The logical page number.
     */
    virtual void load_page(int page_num);

    /**
     * @brief Access an invalid page, and there is no free frame.
     * Replace the page with the page that has been in memory the longest.
     * @param page_num The logical page number.
     * @return Selected victim page #
     */
    virtual int replace_page(int page_num);

};

