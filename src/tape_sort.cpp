#include <iostream>
#include <memory>
#include "Tape.hpp"


int main(int argc, char *argv[]){
    if (argc!=3) {
        std::cout << "Usage: ./tape_sort <filename>\n";
        return 1;
    }
    
    auto t = new Tape(argv[1], 0, 0);
    // std::cout<<atoi(argv[2])<<" "<<std::endl;
    // std::cout<<t->get_value(atoi(argv[2]))<<std::endl;
    std::cout<<"--------- 5 ---------"<<std::endl;
    t->go_to(5);
    std::cout<<5<<" -> "<<t->read_value()<<std::endl;
    std::cout<<"WRITE ON 5"<<std::endl;
    t->write_value(100);
    std::cout<<"--------- 5 ---------"<<std::endl;
    t->go_to(5);
    std::cout<<5<<" -> "<<t->read_value()<<std::endl;
    std::cout<<"--------- 1 ---------"<<std::endl;
    t->go_to(1);
    std::cout<<1<<" -> "<<t->read_value()<<std::endl;
    std::cout<<"--------- 5 ---------"<<std::endl;
    t->go_to(5);
    std::cout<<5<<" -> "<<t->read_value()<<std::endl;
    std::cout<<"--------- 1 ---------"<<std::endl;
    t->go_to(1);
    std::cout<<1<<" -> "<<t->read_value()<<std::endl;
    // for(int i = 0; i < 2; i++){
    //     t->step_backward();
    // }
    // std::cout<<1<<" -> "<<t->get_value(1)<<std::endl;
    // std::cout<<5<<" -> "<<t->get_value(5)<<std::endl;
    // std::cout<<t->get_value(5)<<std::endl;

    return 0;
}