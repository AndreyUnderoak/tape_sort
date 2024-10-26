#include "ConfigParser.hpp"

#include "Colors.hpp"

ConfigParser::ConfigParser(){};
ConfigParser::ConfigParser(char* filename){
    parse(filename);
}

void ConfigParser::parse(char* filename){
    std::cout << YELLOW_COLOR << "Парсинг файла " << filename << std::endl;
    std::ifstream file("config.json", std::ifstream::binary);
    // if (!file.is_open()) {
    //     std::cerr << "Ошибка открытия файла!" << std::endl;
    //     return 1;
    // }

    Json::Value root;
    file >> root;

    int mem = root["memory_int"].asInt();
    int delay_rw = root["delays"]["read_write"].asInt();
    int delay_go_to = root["delays"]["go_to"].asInt();
    int delay_go_end = root["delays"]["go_end"].asInt();


    std::cout << GREEN_COLOR << "Конфигурация загружена:"<< RESET_COLOR << std::endl;
    std::cout << "Memory: " << mem << " (int)" << std::endl;
    std::cout << "Delay rw: " << delay_rw << " (sec)" << std::endl;
    std::cout << "Delay go_to: " << delay_go_to << " (sec)" << std::endl;
    std::cout << "Delay go_end: " << delay_go_end << " (sec)" << std::endl << std::endl;

}

int ConfigParser::get_mem(){
    return mem;
}

int ConfigParser::get_delay_rw(){
    return delay_rw;
}

int ConfigParser::get_delay_goto(){
    return delay_go_to;
}

int ConfigParser::get_delay_full(){
    return delay_go_end;
}