/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority.cpp
 * @author ??? (TODO: your name)
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_priority.h"
#include "pcb.h"
#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Construct a new SchedulerPriority object
 */
SchedulerPriority::SchedulerPriority() {
    // Constructor logic if needed
}

/**
 * @brief Destroy the SchedulerPriority object
 */
SchedulerPriority::~SchedulerPriority() {
    // Destructor logic if needed
}

/**
 * @brief Initializes the process list for the priority scheduler.
 * @param process_list The list of processes to be scheduled.
 */
void SchedulerPriority::init(std::vector<PCB>& process_list) {
    processes = process_list;

    // Sort the processes based on priority (lower number means higher priority).
    // Processes with the same priority should retain their original order.
    for (size_t i = 0; i < processes.size(); ++i) {
        for (size_t j = i + 1; j < processes.size(); ++j) {
            // Swap if process[j] has a higher priority than process[i].
            // Lower priority value means higher priority.
            if (processes[j].priority < processes[i].priority) {
                PCB temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    // Display the initialized list for verification.
    for (size_t i = 0; i < processes.size(); ++i) {
        cout << "Process " << i << ": " << processes[i].id << " has priority "
             << processes[i].priority << " and burst time " << processes[i].burst_time << "\n";
    }
}

/**
 * @brief Simulates the Priority scheduling by executing processes based on their priority.
 */
void SchedulerPriority::simulate() {
    int current_time = 0;
    completion_times.resize(processes.size());

    for (size_t i = 0; i < processes.size(); ++i) {
        PCB& process = processes[i];

        // Start time is the current time (since processes are assumed to arrive at time 0).
        int start_time = current_time;
        int completion_time = start_time + process.burst_time;
        current_time = completion_time;

        // Store the completion time for later calculation of waiting time.
        completion_times[i] = completion_time;

        // Print the process being run.
        cout << "Running Process " << process.id << " for " << process.burst_time << " time units\n";
    }
}

/**
 * @brief Prints the results of the Priority scheduling, including average waiting time.
 */
void SchedulerPriority::print_results() {
    int total_turnaround_time = 0;
    int total_waiting_time = 0;

    for (size_t i = 0; i < processes.size(); ++i) {
        int turnaround_time = completion_times[i];
        int waiting_time = turnaround_time - processes[i].burst_time;
        total_turnaround_time += turnaround_time;
        total_waiting_time += waiting_time;

        cout << processes[i].id << " turn-around time = " << turnaround_time
             << ", waiting time = " << waiting_time << "\n";
    }

    double average_turnaround_time = static_cast<double>(total_turnaround_time) / processes.size();
    double average_waiting_time = static_cast<double>(total_waiting_time) / processes.size();

    cout << "Average turn-around time = " << average_turnaround_time
         << ", Average waiting time = " << average_waiting_time << "\n";
}
