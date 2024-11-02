#ifndef TAPE_H
#define TAPE_H

#include "ReaderEmulator.hpp"

/**
 * Tape class
 */
class Tape{
private:
    // current pose and read/write delay
    int pose = 0, delay_rw, delay_goto, delay_full;
    // number of elements in tape
    size_t num_of_el;
    
    /**
    * Delay scale times
    * @param msec milliseconds to be delayed
    */
    void delay(const int msec);

public:
    // Reader emulator type int
    ReaderEmulator<int> reader;
    /**
    * @param filename name of the file to work with for emulator
    * @param delay delay of tape
    * @param pos starting position
    * 
    */
    Tape(const char* filename, const int delay_rw, const int delay_goto, const int delay_full);

    /**
    * Empty Tape
    * */
    Tape();

    /**
    * Read value from tape by current pose
    * @return value from tape by current pose
    */
    int read_value();
    /**
    * Write value into current pose tape
    * @param value to write
    */
    void write_value(const int val);
     /**
    * Go to pos
    * @param new_pose where to go
    */
    void go_to(const int new_pose);

    void go_front();

    size_t get_size();

    void set_size(const size_t size);

};


#endif