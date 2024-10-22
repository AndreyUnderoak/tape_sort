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
    int num, i = 0;
    std::cout<<"Вводите числа поочередно с новой строки для записи в ленту:"<<std::endl;
    while (std::cin >> num) {
        t.write_value(num);
        t.go_to(++i);
    }
    return 0;
}