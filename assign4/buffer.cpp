/**
* Assignment 4: Producer Consumer Problem
 * @file buffer.cpp
 * @author Svetya Koppisetty and Arpita Godbole (TODO: your name)
 * @brief Implementation file for the buffer class
 * @version 0.1
 */

// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "buffer.h"
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

// TODO: Add your implementation of the buffer class here

Buffer::Buffer(int size)
{
    buffer[0] = 0;
    this->size = size;
    this->counter = 0;
    this->front = 0;
    this->last = 0;
}


Buffer::~Buffer()
{
    while(!is_empty())
    {
        buffer_item bi = buffer[front];
        remove_item(&bi);
    }
}


bool Buffer::insert_item(buffer_item item)
{
    if(!is_full())
    {
      if(counter == 0) { buffer[front] = item; } 
      else 
        {
	  last = (last + 1) % get_size();
	  buffer[last] = item;
        }
      counter++;
      return true;
    }
    return false;
}


bool Buffer::remove_item(buffer_item *item)
{
  if(!is_empty())
    {
      *item = buffer[front];
      front = (front + 1) % get_size();
      counter--;
      return true;
    }

  return false;
}


int Buffer::get_size()
{
  return size;
}

int Buffer::get_count()
{
  return counter;
}

bool Buffer::is_empty()
{
  return counter == 0;
}

bool Buffer::is_full()
{
  return this->counter == this->size;
}

void Buffer::print_buffer()
{
  if(is_empty())
    {
        cout << "[ Empty ]" << endl;
    }
  else
    {
        int temp = front;
        cout << "Buffer [";
        for(int i = 0; i < counter - 1; i++)
	  {
            cout << buffer[temp] << ", ";
            temp = (temp + 1) % size;
	  }
        cout << buffer[last] << "]" << endl;
    }
}
