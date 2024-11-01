#include <cmath>
#include <utility>
#include <set>
#include <iostream>
#include <thread>

#include "TapeSorter.hpp"
#include "Colors.hpp"

TapeSorter::TapeSorter(std::shared_ptr<Tape> in_tape, std::shared_ptr<Tape> temp_tape, std::shared_ptr<Tape> out_tape, int memory_size):in_tape(in_tape), temp_tape(temp_tape), out_tape(out_tape), memory_size(memory_size){
    // prepare temp and out tape
    temp_tape->set_size(0);
    out_tape->set_size(0);
    
    // get size of our buffer = RAM / 2 
    buffer_size = memory_size / 2;
    std::cout<<"Размер буфера: " << buffer_size <<std::endl;
}

void TapeSorter::sort(){
    size_t out_counter_start = 0;
    std::multiset<int> buff1, buff2; 
    // get number of iterations
    int num_iters = ceil(in_tape->get_size()/buffer_size);
    // if buffer cover all array
    if(num_iters == 0) num_iters = 1;
    // start from out tape if iterations mod 2 = 1
    if(num_iters % 2 != 0) 
        std::swap(out_tape, temp_tape);

    // thread for filling the buffer q
    std::thread fill_thread;

    while(out_counter_start < in_tape->get_size() + buffer_size ){
        // push fill to thread
        fill_thread = std::thread(&TapeSorter::bf_filler, this, std::ref(buff1), out_counter_start);

        // bf_filler(buff1, out_counter_start);

        bf_tp_sort(buff2, *temp_tape, *out_tape);

        // swapping buffers for filling and sorting
        std::swap(out_tape, temp_tape);
        out_counter_start += buffer_size;

        // wait for filling buffer, just in case
        if (fill_thread.joinable()) {
            fill_thread.join();
        }
        // swapping buffers for filling and sorting
        std::swap(buff1, buff2);
    }
}


// NOTE: start from 0
void TapeSorter::bf_filler(std::multiset<int> &buffer, size_t start){
    // LOGS
        std::cout<<"Позиция чтения входной ленты для буффера: " << start <<std::endl;

    // clear our buffer
    buffer.clear();
    // filling the buffer 
    for(int i = start; i < start + buffer_size && i < in_tape->get_size(); ++i){
        in_tape->go_to(i);
        buffer.insert(in_tape->read_value());
    }
}
void TapeSorter::bf_tp_sort(std::multiset<int> &buffer, Tape &temp, Tape &out){
    // LOGS
            std::cout<<YELLOW_COLOR<<"Загрузка буффера для сортировки: "<<RESET_COLOR<<std::endl;
            for(const auto &t : buffer) std::cout<<t<<std::endl;

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
            out.go_to(++out_counter);

            if(temp.get_size() <= ++temp_counter) break;
            
            temp.go_to(temp_counter);
            temp_num = temp.read_value();
            std::cout<<"Записал из временной ленты "<<out_counter<<std::endl;
        }
        else{
            out.write_value(*buff_pointer);
            out.go_to(++out_counter);
            ++buff_pointer;
            std::cout<<"Записал из буффера "<<out_counter<<std::endl;
        }
        
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
        out.go_to(++out_counter);

        if(temp.get_size() <= ++temp_counter) break;

        temp.go_to(temp_counter);
        temp_num = temp.read_value();

        
        std::cout<<"Записал из временной ленты "<<out_counter<<std::endl;     
    }
    out.set_size(out_counter);

}