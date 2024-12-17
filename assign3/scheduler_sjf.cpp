/**
* Assignment 3: CPU Scheduler
 * @file scheduler_sjf.cpp
 * @author Arpita Godbole & Svetya Koppisetty (TODO: your name)
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_sjf.h"
#include "pcb.h"
#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Construct a new SchedulerSJF object
 */
SchedulerSJF::SchedulerSJF() {}

/**
 * @brief Destroy the SchedulerSJF object
 */
SchedulerSJF::~SchedulerSJF() {}

/**
 * @brief This function is called once before the simulation starts.
 *        It is used to initialize the scheduler.
 * @param process_list The list of processes in the simulation.
 */
void SchedulerSJF::init(vector<PCB>& process_list) 
{
    processes = process_list;
// using selection sort, sorting list of processes
    for (size_t i = 0; i < processes.size(); ++i) 
    {
        size_t min_index = i;
        for (size_t j = i + 1; j < processes.size(); ++j) 
        {
            if (processes[j].burst_time < processes[min_index].burst_time) 
            {
                min_index = j;
            }
        }
        if (min_index != i) 
        {
            PCB temp = processes[i];
            processes[i] = processes[min_index];
            processes[min_index] = temp;
        }
    }
}

/**
 * @brief This function simulates the scheduling of processes in the ready queue.
 *        It stops when all processes are finished.
 */
void SchedulerSJF::simulate() 
{
    int current_time = 0;
    completion_times.clear(); 

    for (auto& process : processes) 
    {
        int start_time ;

        if (current_time > process.arrival_time) 
        {
            start_time = current_time;
        } 
        else 
        {
            start_time = process.arrival_time;
        }
        int completion_time = start_time + process.burst_time;
        current_time = completion_time;
        completion_times.push_back(completion_time);

        cout << "Running Process " << process.name << " for " << process.burst_time << " time units\n";
    }
}

/**
 * @brief This function is called once after the simulation ends.
 *        It is used to print out the results of the simulation.
 */
void SchedulerSJF::print_results() 
{
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    for (size_t i = 0; i < processes.size(); i++) 
    {
        int turnaround_time = completion_times[i] - processes[i].arrival_time;

        int waiting_time = turnaround_time - processes[i].burst_time;

        total_turnaround_time += turnaround_time;
        total_waiting_time += waiting_time;

        cout << processes[i].name << " turn-around time = " << turnaround_time  << ", waiting time = " << waiting_time << "\n";
    }

    double average_turnaround_time = static_cast<double>(total_turnaround_time) / processes.size();
    double average_waiting_time = static_cast<double>(total_waiting_time) / processes.size();
    
    cout << "Average turn-around time = " << average_turnaround_time << "\n" << "Average waiting time = " << average_waiting_time << "\n";
}
