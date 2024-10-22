#include <iostream>
#include <memory>
#include "Tape.hpp"
#include "ConfigParser.hpp"


int main(int argc, char *argv[]){
    if (argc!=3) {
        std::cout << "Usage: ./tape_sort <filename>\n";
        return 1;
    }
    
    ConfigParser cp("config.json");

    Tape t(argv[1], cp.get_delay_rw(), 
                    cp.get_delay_goto(), 
                    cp.get_delay_full());

    std::cout<<"--------- 5 ---------"<<std::endl;
    t.go_to(5);
    std::cout<<5<<" -> "<<t.read_value()<<std::endl;
    std::cout<<"WRITE ON 5"<<std::endl;
    t.write_value(100);
    std::cout<<"--------- 5 ---------"<<std::endl;
    t.go_to(5);
    std::cout<<5<<" -> "<<t.read_value()<<std::endl;
    std::cout<<"--------- 1 ---------"<<std::endl;
    t.go_to(1);
    std::cout<<1<<" -> "<<t.read_value()<<std::endl;
    std::cout<<"--------- 5 ---------"<<std::endl;
    t.go_to(5);
    std::cout<<5<<" -> "<<t.read_value()<<std::endl;
    std::cout<<"--------- 1 ---------"<<std::endl;
    t.go_to(1);
    std::cout<<1<<" -> "<<t.read_value()<<std::endl;


    return 0;
}