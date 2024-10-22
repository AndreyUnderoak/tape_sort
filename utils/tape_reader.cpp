#include <iostream>
#include <memory>
#include "Tape.hpp"
#include "ConfigParser.hpp"


int main(int argc, char *argv[]){
    if (argc!=2) {
        std::cout << "Usage: ./tape_recorder <filename>\n";
        return 1;
    }
    
    ConfigParser cp("config.json");

    Tape t(argv[1], cp.get_delay_rw(), 
                    cp.get_delay_goto(), 
                    cp.get_delay_full());
    t.go_to(0);
    for(size_t i = 0; i < t.get_size(); ++i) {
        t.go_to(i);
        std::cout<<t.read_value()<<std::endl;
    }
    return 0;
}