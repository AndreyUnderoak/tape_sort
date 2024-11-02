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
    ReaderEmulator(const char* filename){
        try{
            open(filename);
        }
        catch (const std::runtime_error& e) {
            throw;
        }
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
    virtual void open(const char* filename){
        std::filesystem::path file_path(filename);
        std::filesystem::path dir_path = file_path.parent_path();

        if (!std::filesystem::exists(dir_path) && dir_path!="") {
            throw std::runtime_error("Ошибка: директория " + std::string(dir_path)+ " несуществует, или не может быть найден\n");
        }

        if (!std::filesystem::exists(filename)) {
            std::cout << YELLOW_COLOR << "Файл " << filename << " не найден"<< RESET_COLOR << std::endl;
            std::ofstream temp(filename);
            if (!temp.is_open()) {
                throw std::runtime_error("Ошибка: не удалось создать "+ std::string(filename) + "файл. \nВозможно у приложения не хватает прав для его создания.\nПриложение не может создать директорию, где находится файл, создайте её заранее");
            } else {
                std::cout << GREEN_COLOR << "Файл " << filename << " создан" << RESET_COLOR << std::endl;
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
            throw std::runtime_error("Ошибка: невозможно открыть файл " + std::string(filename) + ". Запускайте скрипт из директории где в корне находится "+ std::string(filename));
        }
    }

    virtual ~ReaderEmulator(){
        if(file && file->is_open())
            file->close();
    }

    /**
    *  Getting value by position
    *  @param pos number of position to be readed
    *  TODO: check if file ok?
    */
    T get_value(const int pos){
        file->clear();
        // if(pos > file->get_num()) return 0; //RAISE
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
    void set_value(const int pos, const T val){
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