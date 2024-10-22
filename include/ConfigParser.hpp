#include <iostream>
#include <fstream>
#include <json/json.h>


class ConfigParser{
private:
    std::ifstream file;
    int mem, delay_rw, delay_go_to, delay_go_end;

public:
    /**
    * Empty parser
    * */
    ConfigParser();
    /**
    * @param filename name of the file to parse
    */
    ConfigParser(char* filename);
    /**
    * @param filename name of the file to parse
    */
    void parse(char* filename);
    int get_delay_rw();
    int get_delay_goto();
    int get_delay_full();
    int get_mem();
    // int get_by_key(char* key);
};
