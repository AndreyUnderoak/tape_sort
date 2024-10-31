#ifndef READEREMULATOR_H
#define READEREMULATOR_H


#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <memory>
#include <filesystem>

#include "Colors.hpp"

/**
 * Emulator for physical devices via binary file
 *
 * @tparam T the type of data stored in one unit on physical device 
 */
template <class T>
class ReaderEmulator{
private:
    // file for read and write
    std::unique_ptr<std::fstream> file;
public:
    /**
    * @param filename name of the file to work with
    */
    ReaderEmulator(char* filename){
        open(filename);
    }
    /**
    *  Empty. Do open(filename) to start working
    */
    ReaderEmulator(){}

    /**
    * Opens the file to work with
    * @param filename name of the file to work with
    * TODO: check if file ok?
    */
    virtual void open(char* filename){
        
        if (!std::filesystem::exists(filename)) {
            std::cout << YELLOW_COLOR << "Файл " << filename << " не найден"<< RESET_COLOR << std::endl;
            std::ofstream temp(filename);
            if (temp.is_open()) {
                std::cout << GREEN_COLOR << "Файл " << filename << " создан" << RESET_COLOR << std::endl;
            } else {
                std::cerr << YELLOW_COLOR << "Не удалось создать "<< filename <<"файл"<< RESET_COLOR << std::endl;
            }
            temp.close();
        }

        file = std::make_unique<std::fstream>(
               std::fstream(filename, std::ios::in  |
                                      std::ios::out | 
                                      std::ios::ate | 
                                      std::ios::binary)
               );

        if (!file->is_open()) {
            std::cout << RED_COLOR << "Файл " << filename << " найден, но не может быть откыт" << RESET_COLOR << std::endl;
        }
    }

    virtual ~ReaderEmulator(){
        file->close();
    }

    /**
    *  Getting value by position
    *  @param pos number of position to be readed
    *  TODO: check if file ok?
    */
    T get_value(int pos){
        file->clear();
        file->seekg(pos*sizeof(T));
        T temp;
        file->read((char *)&temp, sizeof(T));
        return temp;
    }

    /**
    *  Setting value by position
    *  @param pos number of position to be set
    *  @param val value to be set
    *  TODO: check if file ok?
    */
    void set_value(int pos, T val){
        file->clear();
        file->seekp(pos*sizeof(T));
        file->write((char *)&val, sizeof(T));
    }

    /**
    *  Get number of elements
    */
    size_t get_num(){
        return file->tellg() / sizeof(T);
    }


};


#endif