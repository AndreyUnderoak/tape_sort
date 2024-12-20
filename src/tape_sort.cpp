#include <iostream>
#include <memory>
#include <cstdio>
#include <chrono>

#include "Colors.hpp"
#include "Tape.hpp"
#include "ConfigParser.hpp"
#include "TapeSorter.hpp"


int main(int argc, char *argv[]){

    std::cout<<">>>>>>>>>>>TAPE SORT<<<<<<<<<<<"<<std::endl<<std::endl;

    // filenames
    const char *in_filename, *out_filename;
    if (argc!=3) {
        std::cout << RED_COLOR << "Недостаточно аргументов. Введите: ./tape_sort <имя_входного_файла> <имя_выходного_файла>\n" << RESET_COLOR << std::endl;
        return 1;
    }
    else{
        in_filename = argv[1];
        out_filename = argv[2];
    }
    // config and temp files
    const char* temp_filename   = "./tmp/temp.bin";
    const char* config_filename = "./configs/config.json";

    // pointers for tapes and config
    std::shared_ptr<Tape> tape_in, tape_temp, tape_out;
    std::unique_ptr<ConfigParser> cp;
    
    // opening all files to start sort
    try{
        cp = std::make_unique<ConfigParser>(config_filename);

        tape_in = std::make_shared<Tape>(in_filename, 
                                         cp->get_delay_rw(), 
                                         cp->get_delay_goto(), 
                                         cp->get_delay_full()
                                         );

        tape_temp = std::make_shared<Tape>(temp_filename, 
                                         cp->get_delay_rw(), 
                                         cp->get_delay_goto(), 
                                         cp->get_delay_full()
                                         );

        tape_out = std::make_shared<Tape>(out_filename, 
                                         cp->get_delay_rw(), 
                                         cp->get_delay_goto(), 
                                         cp->get_delay_full()
                                         );

        tape_out->clear_after(tape_in->get_size());
    } 
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1; 
    }
    
    std::cout << YELLOW_COLOR << "Инициализация сортировщика ..." <<RESET_COLOR << std::endl;
    TapeSorter ts(tape_in, tape_temp, tape_out, cp->get_mem());
    
    std::cout << GREEN_COLOR << "Начало сортировки:" << RESET_COLOR << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    ts.sort();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << GREEN_COLOR << "Время выполнения сортировки: "<< RESET_COLOR << std::fixed << std::setprecision(2)
              << elapsed_seconds.count() << " (сек)" << std::endl;


    return 0;
}