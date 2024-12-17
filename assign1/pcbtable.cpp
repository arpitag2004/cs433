/**
 * Assignment 1: priority queue of processes
 * @file pcbtable.h
 * @author Arpita Godbole & Svetya Koppisetty 
 * @brief This is the implementation file for the PCBTable class.
 * //You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
 * // Remember to add sufficient comments to your code
 */

#include "pcbtable.h"

/**
 * @brief Construct a new PCBTable object of the given size (number of PCBs)
 *
 * @param size: the capacity of the PCBTable
 */
PCBTable::PCBTable(int size) {
   pcbTable.resize(size);
}

/**
 * @brief Destroy the PCBTable object. Make sure to delete all the PCBs in the table.
 *
 */
PCBTable::~PCBTable() {
   // Delete all the PCBs in the table
   for(long int i = 0; i < pcbTable.size(); i++)
   {
     delete pcbTable.at(i);
   }
   pcbTable.clear();
}

/**
 * @brief Get the PCB at index "idx" of the PCBTable.
 *
 * @param idx: the index of the PCB to get
 * @return PCB*: pointer to the PCB at index "idx"
 */
PCB* PCBTable::getPCB(unsigned int idx) {
    return pcbTable.at(idx);
}

/**
 * @brief Add a PCB pointer to the PCBTable at index idx.
 *
 * @param pcb: the PCB to add
 */
void PCBTable::addPCB(PCB *pcb, unsigned int idx) {
    if(pcbTable.size() <= idx)
    {
        pcbTable.resize(idx*2);
    }
    // Adds a PCB pointer to the PCBTable at index idx.
    pcbTable.at(idx)= pcb;
}
