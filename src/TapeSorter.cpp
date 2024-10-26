#include <cmath>
#include <utility>
#include <set>

#include "TapeSorter.hpp"

TapeSorter::TapeSorter(Tape *in_tape, Tape *temp_tape, Tape *out_tape, int memory_size):in_tape(in_tape), temp_tape(temp_tape), out_tape(out_tape), memory_size(memory_size){
    // get size of our buffer = RAM / 2 
    buffer_size = memory_size / 2;
    // get number of iterations
    int num_iters = ceil(in_tape->get_size()/buffer_size);
    // start from out tape if iterations mod 2 = 1
    if(num_iters % 2) std::swap(out_tape, temp_tape);
     
}

void TapeSorter::sort(){
    size_t out_counter_start = 0;
    std::set<int> buff1, buff2; 
     while(out_counter_start < in_tape->get_size()){
        bf_filler(buff1, out_counter_start);
        bf_tp_sort(buff1, *temp_tape, *out_tape);
        // std::swap();
        out_counter_start += buffer_size;
     }
}


// NOTE: start from 0
void TapeSorter::bf_filler(std::set<int> &buffer, int start){
    // clear our buffer
    buffer.clear();
    // filling the buffer 
    for(int i = start; i < start + buffer_size && i < in_tape->get_size(); ++i){
        in_tape->go_to(i);
        buffer.insert(in_tape->read_value());
    }
}
void TapeSorter::bf_tp_sort(std::set<int> &buffer, Tape &temp_tape, Tape &out_tape){
    // counters for out Tape and temp Tape
    size_t out_counter = 0;
    size_t temp_counter = 0;
    // goto start
    out_tape.go_front();
    temp_tape.go_front();
    // get temp num to save rw time
    int temp_num = out_tape.read_value();
    // get start pointer
    auto buff_pointer = buffer.begin();
    // while one of containers not empty
    while(buff_pointer != buffer.end() 
      || (temp_counter < temp_tape.get_size())){

        if(temp_num < *buff_pointer){
            out_tape.write_value(temp_num);
            temp_tape.go_to(++temp_counter);
            temp_num = temp_tape.read_value();
        }
        else{
            out_tape.write_value(*buff_pointer);
            ++buff_pointer;
        }
        out_tape.go_to(++out_counter);
    }
    //fill from buffer if not empty
    for(; buff_pointer != buffer.end(); ++buff_pointer){
        out_tape.write_value(*buff_pointer);

        out_tape.go_to(++out_counter);
    }
    //fill from tape if not empty
    for(;temp_counter < temp_tape.get_size(); ++temp_counter){
        out_tape.write_value(temp_num);
        temp_tape.go_to(++temp_counter);
        temp_num = temp_tape.read_value();

        out_tape.go_to(++out_counter);        
    }
    out_tape.set_size(out_counter + 1);
}