#include "Tape.hpp"

#include "Colors.hpp"

#include <thread>
#include <chrono>

Tape::Tape(char* filename, int delay_rw, int delay_goto, int delay_full): 
           delay_rw(delay_rw), delay_goto(delay_goto), delay_full(delay_full), pose(pose){
    reader.open(filename);
    num_of_el = reader.get_num();
    std::cout << GREEN_COLOR << "Лента "<< filename << " создана" << RESET_COLOR << std::endl << std::endl;
}

int Tape::read_value(){
    // if(pose > num_of_el) return 0; //RAISE
    delay(delay_rw);
    return reader.get_value(pose);
}
void Tape::write_value(int val){
    delay(delay_rw);
    reader.set_value(pose, val);
}
void Tape::delay(int msec){
    std::this_thread::sleep_for(std::chrono::milliseconds(msec));
}

size_t Tape::get_size(){
    return num_of_el;
}

void Tape::set_size(size_t size){
    num_of_el = size;
}


void Tape::go_to(int new_pose){
    delay(abs(pose - new_pose)*delay_goto);
    pose = new_pose;
}

void Tape::go_front(){
    delay(delay_full);
    pose = 0;
}

