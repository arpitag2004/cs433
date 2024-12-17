// Remember to add comments to your code

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <vector>
#include <iomanip>

#include "fifo_replacement.h"
#include "lru_replacement.h"
#include "lifo_replacement.h"

// Check if an integer is power of 2
bool isPowerOfTwo(unsigned int x) {
    return x && (!(x & (x - 1)));
}

int main(int argc, char *argv[]) {
    //Print basic information about the program
    std::cout << "=================================================================" << std::endl;
    std::cout << "CS 433 Programming assignment 5" << std::endl;
    std::cout << "Arpita Godbole & Svetya Kopisetty" << std::endl;
    std::cout << "Date: 12/06/2024" << std::endl;
    std::cout << "Course: CS433 (Operating Systems)" << std::endl;
    std::cout << "Description : Program to simulate different page replacement algorithms" << std::endl;
    std::cout << "=================================================================\n" << std::endl;

    if (argc < 3) {
        // user does not enter enough parameters
        std::cout << "You have entered too few parameters to run the program.  You must enter" << std::endl
                  << "two command-line arguments:" << std::endl
                  << " - page size (in bytes): between 256 and 8192, inclusive" << std::endl
                  << " - physical memory size (in megabytes): between 4 and 64, inclusive" << std::endl;
        exit(1);
    }

    // Page size and Physical memory size
    // Their values should be read from command-line arguments, and always a power of 2
    unsigned int page_size = atoi(argv[1]);
    if (!isPowerOfTwo(page_size)) {
        std::cout << "You have entered an invalid parameter for page size (bytes)" << std::endl
                  << "  (must be an power of 2 between 256 and 8192, inclusive)." << std::endl;
        return 1;
    }
    unsigned int phys_mem_size = atoi(argv[2]) << 20; // convert from MB to bytes
    if (!isPowerOfTwo(phys_mem_size)) {
        std::cout << "You have entered an invalid parameter for physical memory size (MB)" << std::endl
                  << "  (must be an even integer between 4 and 64, inclusive)." << std::endl;
        return 1;
    }

    // calculate number of pages and frames;
    int logic_mem_bits = 27;        // 27-bit logical memory (128 MB logical memory assumed by the assignment)
    int phys_mem_bits = std::log2(
            phys_mem_size);        // Num of bits for physical memory addresses, calculated from physical memory size, e.g. 24 bits for 16 MB memory
    int page_offset_bits = std::log2(
            page_size);                // Num of bits for page offset, calculated from page size, e.g. 12 bits for 4096 byte page
    // Number of pages in logical memory = 2^(logic_mem_bits - page_bit)
    int num_pages = 1 << (logic_mem_bits - page_offset_bits);
    // Number of free frames in physical memory = 2^(phys_mem_bits - page_offset_bits)
    int num_frames = 1 << (phys_mem_bits - page_offset_bits);

    std::cout << "Page size = " << page_size << " bytes" << std::endl;
    std::cout << "Physical Memory size = " << phys_mem_size << " bytes" << std::endl;
    std::cout << "Number of pages = " << num_pages << std::endl;
    std::cout << "Number of physical frames = " << num_frames << std::endl;

    // Test 1: Read and simulate the small list of logical addresses from the input file "small_refs.txt"
    std::cout << "\n================================Test 1==================================================\n";
    std::ifstream in;
    in.open("small_refs.txt");
    if (!in.is_open()) {
        std::cerr << "Cannot open small_refs.txt to read. Please check your path." << std::endl;
        return 1;
    }
    int val;
    std::vector<int> small_refs;
    while (in >> val) {
        small_refs.push_back(val);
    }
    // Runs the FIFOReplacement test on the list for small_refs and provides the statistics
    FIFOReplacement vm(num_pages, num_frames);
    for (std::vector<int>::const_iterator it = small_refs.begin(); it != small_refs.end(); ++it) {
        int page_num = (*it) >> page_offset_bits;
        bool is_page_fault = vm.access_page(page_num, 0);
        PageEntry pg = vm.getPageEntry(page_num);
        std::cout << "Logical address: " << *it << ", \tpage number: " << page_num;
        std::cout << ", \tframe number = " << pg.frame_num << ", \tis page fault? " << is_page_fault << std::endl;
    }
    in.close();
    vm.print_statistics();

    // Test 2: Read and simulate the large list of logical addresses from the input file "large_refs.txt"
    std::cout << "\n================================Test 2==================================================\n";
    std::ifstream in2;
    in2.open("large_refs.txt");
    if(!in2.is_open()) {
        std::cerr<< "cannot open large_refs.txt to read. Please check your path." << std::endl;
        return 1;
    }
    int val2;
    std::vector<int> large_refs;
    while(in2 >> val2){
        large_refs.push_back(val2);
    }
    std::cout<<"Total number of references: "<<large_refs.size()<<std::endl;

    std::cout << "****************Simulate FIFO replacement****************************" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    
    // Runs the FIFOReplacement test on the list for small_refs and provides the statistics as well as a time duration
    FIFOReplacement fifo(num_pages,num_frames);
    for (std::vector<int>::const_iterator it = large_refs.begin(); it != large_refs.end(); ++it) {
        int page_num = (*it) >> page_offset_bits;
        bool isPageFault = fifo.access_page(page_num, 0);
        PageEntry pg = fifo.getPageEntry(page_num);
    
    }
    auto end = std::chrono::high_resolution_clock::now(); //stop the timer
    fifo.print_statistics();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Elapsed time = " << std::fixed << std::setprecision(6) << duration / 1000000.0 << " seconds" << std::endl;
    LIFOReplacement lifo(num_pages,num_frames);

    std::cout << "****************Simulate LIFO replacement****************************" << std::endl;

    auto start2 = std::chrono::high_resolution_clock::now();

    // Runs the LIFOReplacement test on the list for small_refs and provides the statistics as well as a time duration
    for (std::vector<int>::const_iterator it = large_refs.begin(); it != large_refs.end(); ++it) {
        int page_num = (*it) >> page_offset_bits;
        bool isPageFault = lifo.access_page(page_num, 0);
        PageEntry pg = lifo.getPageEntry(page_num);
 
    }

    auto end2 = std::chrono::high_resolution_clock::now();
    lifo.print_statistics();
     auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count();
    std::cout << "Elapsed time = " << std::fixed << std::setprecision(6) << duration2 / 1000000.0 << " seconds" << std::endl;

    // Runs the LRUReplacement test on the list for small_refs and provides the statistics as well as a time duration
    LRUReplacement lru(num_pages,num_frames);

    std::cout << "****************Simulate LRU replacement****************************" << std::endl;
    auto start3 = std::chrono::high_resolution_clock::now();
    for (std::vector<int>::const_iterator it = large_refs.begin(); it != large_refs.end(); ++it) {
        int page_num = (*it) >> page_offset_bits;
        bool isPageFault = lru.access_page(page_num, 0);
        PageEntry pg = lru.getPageEntry(page_num);
    }

    lru.print_statistics();
     auto end3 = std::chrono::high_resolution_clock::now();
     auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(end3 - start3).count();
    std::cout << "Elapsed time = " << std::fixed << std::setprecision(6) << duration3 / 1000000.0 << " seconds" << std::endl;
    in2.close();
}
