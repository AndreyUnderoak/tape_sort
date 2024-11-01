#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <iostream>
#include <fstream>

class ConfigParser{
private:
    std::ifstream file;
    // params
    int mem, delay_rw, delay_go_to, delay_go_end;

public:
    /**
    * Empty parser
    * */
    ConfigParser();
    /**
    * @param filename name of the file to parse
    */
    ConfigParser(const char* filename);
    /**
    * @param filename name of the file to parse
    */
    void parse(const char* filename);
    int get_delay_rw();
    int get_delay_goto();
    int get_delay_full();
    int get_mem();
    // int get_by_key(char* key);
};


#endif