#include "Tape.hpp"


Tape::Tape(char* filename, int delay_rw, int delay_goto, int delay_full): 
           delay_rw(delay_rw), delay_goto(delay_goto), delay_full(delay_full), pose(pose){
    reader.open(filename);
    num_of_el = reader.get_num();
}

int Tape::read_value(){
    delay(delay_rw);
    return reader.get_value(pose);
}
void Tape::write_value(int val){
    delay(delay_rw);
    reader.set_value(pose, val);
}
void Tape::delay(int sec){
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

