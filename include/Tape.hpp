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
    // Reader emulator type int
    ReaderEmulator<int> reader;
    /**
    * Delay scale times
    * @param sec seconds to be delayed
    */
    void delay(int sec);

    bool at_start, at_end;
public:
    /**
    * @param filename name of the file to work with for emulator
    * @param delay delay of tape
    * @param pos starting position
    * 
    */
    Tape(char* filename, int delay_rw, int delay_goto, int delay_full);

    /**
    * Read value from tape by current pose
    * @return value from tape by current pose
    */
    int read_value();
    /**
    * Write value into current pose tape
    * @param value to write
    */
    void write_value(int val);
     /**
    * Go to pos
    * @param new_pose where to go
    */
    void go_to(int new_pose);

    size_t get_size();

};