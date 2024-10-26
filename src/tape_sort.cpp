#include <iostream>
#include <memory>
#include <cstdio>

#include "Tape.hpp"
#include "ConfigParser.hpp"
#include "TapeSorter.hpp"


int main(int argc, char *argv[]){
    if (argc!=3) {
        std::cout << "Недостаточно аргументов. Введите: ./tape_sort <имя_входного_файла> <имя_выходного_файла>\n";
        return 1;
    }
    
    ConfigParser cp("config.json");

    Tape t(argv[1], cp.get_delay_rw(), 
                    cp.get_delay_goto(), 
                    cp.get_delay_full());


    Tape in(argv[1], cp.get_delay_rw(), 
                     cp.get_delay_goto(), 
                     cp.get_delay_full());

    char* temp_file = "tmp/temp.bin";

    remove(temp_file);

    Tape t_temp(temp_file, cp.get_delay_rw(), 
                           cp.get_delay_goto(), 
                           cp.get_delay_full());

    Tape out(argv[2], cp.get_delay_rw(), 
                      cp.get_delay_goto(), 
                      cp.get_delay_full());
    

    
    TapeSorter ts(&in, &t_temp, &out, cp.get_mem());

    ts.sort();
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