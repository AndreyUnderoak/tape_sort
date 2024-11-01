#include "ConfigParser.hpp"

#include <json/json.h>

#include "Colors.hpp"

ConfigParser::ConfigParser(){};
ConfigParser::ConfigParser(const char* filename){
    parse(filename);
}

void ConfigParser::parse(const char* filename){
    std::cout << YELLOW_COLOR << "Парсинг файла " << filename << std::endl;
    std::ifstream file(filename, std::ifstream::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка: невозможно открыть файл " + std::string(filename) + ". Запускайте скрипт из директории где в корне находится "+ std::string(filename));
    }

    Json::Value root;
    file >> root;

    mem = root["memory_int"].asInt();
    delay_rw = root["delays"]["read_write"].asInt();
    delay_go_to = root["delays"]["go_to"].asInt();
    delay_go_end = root["delays"]["go_end"].asInt();


    std::cout << GREEN_COLOR << "Конфигурация загружена:"<< RESET_COLOR << std::endl;
    std::cout << "Memory: " << mem << " (int)" << std::endl;
    std::cout << "Задержка на запись/чтение: " << delay_rw << " (миллисекунд)" << std::endl;
    std::cout << "Задержка на сдвиг на 1 позицию: " << delay_go_to << " (миллисекунд)" << std::endl;
    std::cout << "Задержка на перемотку: " << delay_go_end << " (миллисекунд)" << std::endl << std::endl;

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