#include <iostream>
#include <memory>
#include <cstdio>
#include <chrono>

#include "Colors.hpp"
#include "Tape.hpp"
#include "ConfigParser.hpp"
#include "TapeSorter.hpp"


int main(int argc, char *argv[]){

    char *in_filename, *out_filename;
    if (argc!=3) {
        // std::cout << RED_COLOR << "Недостаточно аргументов. Введите: ./tape_sort <имя_входного_файла> <имя_выходного_файла>\n" << RESET_COLOR << std::endl;
        // return 1;
        in_filename = "files/in.bin";
        out_filename = "files/out.bin";
    }
    else{
        in_filename = argv[1];
        out_filename = argv[2];
    }
        
    ConfigParser cp("config.json");
    
    Tape t(in_filename, cp.get_delay_rw(), 
                    cp.get_delay_goto(), 
                    cp.get_delay_full());


    Tape in(in_filename, cp.get_delay_rw(), 
                     cp.get_delay_goto(), 
                     cp.get_delay_full());

    char* temp_file = "tmp/temp.bin";

    Tape t_temp(temp_file, cp.get_delay_rw(), 
                           cp.get_delay_goto(), 
                           cp.get_delay_full());

    Tape out(out_filename, cp.get_delay_rw(), 
                      cp.get_delay_goto(), 
                      cp.get_delay_full());
    
    std::cout << YELLOW_COLOR << "Инициализация сортировщика ..." << cp.get_mem() <<RESET_COLOR << std::endl;
    TapeSorter ts(&in, &t_temp, &out, cp.get_mem());
    
    std::cout << GREEN_COLOR << "Начало сортировки:" << RESET_COLOR << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    ts.sort();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << GREEN_COLOR << "Время выполнения сортировки: "<< RESET_COLOR << std::fixed << std::setprecision(2)
              << elapsed_seconds.count() << " (сек)" << std::endl;
    // std::cout<<"--------- 5 ---------"<<std::endl;
    // t.go_to(5);
    // std::cout<<5<<" -> "<<t.read_value()<<std::endl;
    // std::cout<<"WRITE ON 5"<<std::endl;
    // t.write_value(100);
    // std::cout<<"--------- 5 ---------"<<std::endl;
    // t.go_to(5);
    // std::cout<<5<<" -> "<<t.read_value()<<std::endl;
    // std::cout<<"--------- 1 ---------"<<std::endl;
    // t.go_to(1);
    // std::cout<<1<<" -> "<<t.read_value()<<std::endl;
    // std::cout<<"--------- 5 ---------"<<std::endl;
    // t.go_to(5);
    // std::cout<<5<<" -> "<<t.read_value()<<std::endl;
    // std::cout<<"--------- 1 ---------"<<std::endl;
    // t.go_to(1);
    // std::cout<<1<<" -> "<<t.read_value()<<std::endl;


    return 0;
}