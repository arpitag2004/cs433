/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.cpp
 * @author  Arpita Godbole & Svetya Koppisetty (TODO: your name)
 * @brief This Scheduler class implements the FCSF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

// TODO: add implementation of SchedulerFCFS constructor, destrcutor and 
// member functions init, print_results, and simulate here

#include "scheduler_fcfs.h"
#include <iostream>
using namespace std;


/**
 * @brief Construct a new SchedulerFCFS object
 */
SchedulerFCFS::SchedulerFCFS() {}

/**
 * @brief Destroy the SchedulerFCFS object
 */
SchedulerFCFS::~SchedulerFCFS() {}

/**
 * @brief This function is called once before the simulation starts.
 *        It is used to initialize the scheduler.
 * @param process_list The list of processes in the simulation.
 */
void SchedulerFCFS::init(vector<PCB>& process_list) 
{
    processes = process_list;
    completion_times.resize(processes.size()); 
}

   /**
     * @brief This function simulates the scheduling of processes in the ready queue.
     *        It stops when all processes are finished.
     */
void SchedulerFCFS::simulate() 
{
    int current_time = 0;
    for (size_t i = 0; i < processes.size(); ++i) 
    {
        int start_time;
        if (current_time > processes[i].arrival_time) 
        {
            start_time = current_time;
        } 
        else 
        {
            start_time = processes[i].arrival_time;
        }
        completion_times[i] = start_time + processes[i].burst_time;

        current_time = completion_times[i];

        cout << "Running Process " << processes[i].name << " for " << processes[i].burst_time << " time units\n";
    }
}

 /**
     * @brief This function is called once after the simulation ends.
     *        It is used to print out the results of the simulation.
     */
void SchedulerFCFS::print_results() 
{
    int total_turnaround_time = 0;
    int total_waiting_time = 0;

    // calculate  turnaround time and waiting time for each process
    for (size_t i = 0; i < processes.size(); ++i) 
    {
        int turnaround_time = completion_times[i] - processes[i].arrival_time;
        
        int waiting_time = turnaround_time - processes[i].burst_time;

    // running totals
        total_turnaround_time += turnaround_time;
        total_waiting_time += waiting_time;

        cout << processes[i].name << " turnaround time = " << turnaround_time 
             << ", waiting time = " << waiting_time << "\n";
    }

    double average_turnaround_time = static_cast<double>(total_turnaround_time) / processes.size();
    double average_waiting_time = static_cast<double>(total_waiting_time) / processes.size();

    cout << "Average turnaround time = " << average_turnaround_time << "\n";
    cout << "Average waiting time = " << average_waiting_time << "\n";
}