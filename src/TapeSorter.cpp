#include <cmath>
#include <utility>
#include <set>
#include <iostream>

#include "TapeSorter.hpp"
#include "Colors.hpp"

TapeSorter::TapeSorter(Tape *in_tape, Tape *temp_tape, Tape *out_tape, int memory_size):in_tape(in_tape), temp_tape(temp_tape), out_tape(out_tape), memory_size(memory_size){
    // prepare temp and out tape
    temp_tape->set_size(0);
    out_tape->set_size(0);
    
    // get size of our buffer = RAM / 2 
    buffer_size = memory_size / 2;
    std::cout<<"Размер буфера: " << buffer_size <<std::endl;
}

void TapeSorter::sort(){
    size_t out_counter_start = 0;
    std::set<int> buff1, buff2; 
    // get number of iterations
    int num_iters = ceil(in_tape->get_size()/buffer_size);
    // start from out tape if iterations mod 2 = 1
    if(num_iters % 2 == 0) 
        std::swap(out_tape, temp_tape);

    while(out_counter_start < in_tape->get_size()){
        std::cout<<"Позиция чтения ленты: " << out_counter_start <<std::endl;
        bf_filler(buff1, out_counter_start);
        std::cout<<YELLOW_COLOR<<"Загрузка буффера: "<<RESET_COLOR<<std::endl;
        for(const auto &t : buff1) std::cout<<t<<std::endl;
        bf_tp_sort(buff1, *temp_tape, *out_tape);
        std::swap(out_tape, temp_tape);

        out_counter_start += buffer_size;
    }

    
    // for(int i = 0; i < 10; i++) {
    //     out_tape->write_value(i);
    //     out_tape->go_to(++i);
    // }
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
void TapeSorter::bf_tp_sort(std::set<int> &buffer, Tape &temp, Tape &out){
    // counters for out Tape and temp Tape
    size_t out_counter = 0;
    size_t temp_counter = 0;
    // goto start
    out.go_front();
    temp.go_front();
    // get temp num to save rw time
    int temp_num = temp.read_value();
    // get start pointer
    auto buff_pointer = buffer.begin();

    std::cout<<"Размер временной ленты: "<<temp.get_size()<<std::endl;
    // while one of containers not empty
    while(buff_pointer != buffer.end() 
      && (temp_counter < temp.get_size())){

        if(temp_num < *buff_pointer){
            out.write_value(temp_num);
            temp.go_to(++temp_counter);
            temp_num = temp.read_value();
            std::cout<<"Записал из временной ленты "<<out_counter<<std::endl;
        }
        else{
            out.write_value(*buff_pointer);
            ++buff_pointer;
            std::cout<<"Записал из буффера "<<out_counter<<std::endl;
        }
        out.go_to(++out_counter);
    }
    //fill from buffer if not empty
    for(; buff_pointer != buffer.end(); ++buff_pointer){
        out.write_value(*buff_pointer);

        out.go_to(++out_counter);
        std::cout<<"Записал из буффера "<<out_counter<<std::endl;
    }
    //fill from tape if not empty
    for(;temp_counter < temp.get_size();){
        out.write_value(temp_num);
        temp.go_to(++temp_counter);
        temp_num = temp.read_value();

        out.go_to(++out_counter);
        std::cout<<"Записал из временной ленты "<<out_counter<<std::endl;     
    }
    out.set_size(out_counter);

}