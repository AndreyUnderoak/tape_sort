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

    mem = root["memory_int"].asInt();
    delay_rw = root["delays"]["read_write"].asInt();
    delay_go_to = root["delays"]["go_to"].asInt();
    delay_go_end = root["delays"]["go_end"].asInt();


    std::cout << GREEN_COLOR << "Конфигурация загружена:"<< RESET_COLOR << std::endl;
    std::cout << "Memory: " << mem << " (int)" << std::endl;
    std::cout << "Задержка на запись/чтение: " << delay_rw << " (milliseconds)" << std::endl;
    std::cout << "Задержка на сдвиг на 1 позицию: " << delay_go_to << " (milliseconds)" << std::endl;
    std::cout << "Задержка на перемотку: " << delay_go_end << " (milliseconds)" << std::endl << std::endl;

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