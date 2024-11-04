#include "Tape.hpp"

#include "Colors.hpp"

#include <thread>
#include <chrono>

Tape::Tape(){}

Tape::Tape(const char* filename, int delay_rw, int delay_goto, int delay_full): 
           delay_rw(delay_rw), delay_goto(delay_goto), delay_full(delay_full), pose(pose){
    try{
        reader.open(filename);
    }
    catch (const std::runtime_error& e) {
        throw;
    }
    pose = 0;
    num_of_el = reader.get_num();
    std::cout << GREEN_COLOR << "Лента "<< filename << " создана" << RESET_COLOR << std::endl << std::endl;
}

int Tape::read_value(){
    // if(pose > num_of_el) return 0; //RAISE
    delay(delay_rw);
    return reader.get_value(pose);
}
void Tape::write_value(const int val){
    delay(delay_rw);
    reader.set_value(pose, val);
}
void Tape::delay(const int msec){
    std::this_thread::sleep_for(std::chrono::milliseconds(msec));
}

size_t Tape::get_size(){
    return num_of_el;
}

void Tape::set_size(const size_t size){
    num_of_el = size;
}


void Tape::go_to(const int new_pose){
    if(new_pose < 0) throw std::runtime_error("У ленты нет отрицательных ячеек");
    delay(abs(pose - new_pose)*delay_goto);
    pose = new_pose;
}

void Tape::go_front(){
    delay(delay_full);
    pose = 0;
}

void Tape::clear_after(const size_t new_end){
    reader.set_end(new_end);
}
