#include "Tape.hpp"


Tape::Tape(char* filename, int delay, int pose): tape_delay(delay), pose(pose){
    reader.open(filename);
}

int Tape::read_value(){
    return reader.get_value(pose);
}
void Tape::write_value(int val){
    reader.set_value(pose, val);
}
void Tape::delay(int scale){
}

void Tape::go_to(int new_pose){
    delay(abs(pose - new_pose));
    pose = new_pose;
}

