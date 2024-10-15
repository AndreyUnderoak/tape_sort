#include "ReaderEmulator.hpp"

/**
 * Tape class
 */
class Tape{
private:
    // current pose and read/write delay
    int pose, tape_delay;
    // Reader emulator type int
    ReaderEmulator<int> reader;
    /**
    * Delay scale times
    * @param scale times needed for delay
    */
    void delay(int scale);
public:
    /**
    * @param filename name of the file to work with for emulator
    * @param delay delay of tape
    * @param pos starting position
    * 
    */
    Tape(char* filename, int delay, int pos);

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

};