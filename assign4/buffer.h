/**
 * Assignment 4: Producer Consumer Problem
 * @file buffer.h
 * @author Svetya Koppisetty and Arpita Godbole (TODO: your name)
 * @brief header file for the buffer class
 * @version 0.1
 */

#ifndef ASSIGN4_BUFFER_H
#define ASSIGN4_BUFFER_H

#include <iostream>
#include <vector>
#include <semaphore.h>
#include <pthread.h>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mutex>
#include <condition_variable>
using namespace std;

// Define the data type of the buffer items
typedef int buffer_item;

/**
 * @brief The bounded buffer class. The number of items in the buffer cannot exceed the size of the buffer.
 */
const int buff_size = 5;

class Buffer {
private:
  // TODO: Add your implementation of the buffer class here
  buffer_item buffer[buff_size];
  int size;
  int counter;
  int front;
  int last;
  
public:
  /**
   * @brief Construct a new Buffer object
   * @param size the size of the buffer
   */
  Buffer(int size = 5);
  
  /**
   * @brief Destroy the Buffer object
   */
  ~Buffer();
  
  /**
   * @brief Insert an item into the buffer
   * @param item the item to insert
   * @return true if successful
   * @return false if not successful
   */
  bool insert_item(buffer_item item);
  
  /**
   * @brief Remove an item from the buffer
   * @param item the item to remove
   * @return true if successful
   * @return false if not successful
   */
  bool remove_item(buffer_item *item);
  
  /**
   * @brief Get the size of the buffer
   * @return the size of the buffer
   */
  int get_size();
  
  /**
   * @brief Get the number of items in the buffer
   * @return the number of items in the buffer
   */
  int get_count();
  
  /**
   * @brief Chceck if the buffer is empty
   * @return true if the buffer is empty, else false
   */
  bool is_empty();
  /**
   * @brief Check if the buffer is full
   * @return true if the buffer is full, else false
   */
  bool is_full();
  
  /**
   * @brief Print the buffer
   */
  void print_buffer();
};
#endif //ASSIGN4_BUFFE//R_H
