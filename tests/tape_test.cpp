/**
    *  File provides testing of full pipeline of sorting algorithm
*/
#include <cassert>
#include <set>
#include <memory>
#include <vector>
#include <cstdio>
#include <filesystem>

#include "Tape.hpp"

/**
    * Converting vector to tape (NOT SORTED)
*/
void vector2tape(std::vector<int>& vec, std::shared_ptr<Tape>& tape){
    tape->go_front();
    tape->set_size(vec.size());
    size_t tape_pos = 0;
    for(const auto& num : vec){
        tape->write_value(num);
        tape->go_to(++tape_pos);
    }
}

/**
    * Checking if tape equal to vector
    * @return true if equal
*/
bool tape2vector(std::shared_ptr<Tape>& tape, std::vector<int>& vec){
    tape->go_front();
    size_t tape_pos = 0;
    for(const auto& num : vec){
        std::cout<<num<<" vs "<<tape->read_value()<< std::endl;
        if(num != tape->read_value()) return false;
        tape->go_to(++tape_pos);
    }
    return true;
}


int main() {
    // filenames
    const char* tape_filename     = "../tests/files/tape.bin";
    if(std::filesystem::exists(tape_filename))   std::remove(tape_filename);

    std::shared_ptr<Tape> tape;
    
    try{
        tape = std::make_shared<Tape>(tape_filename, 1, 2, 3);
        tape->set_size(5);
        if(tape->get_size() == 5) assert(true);
        else std::cerr << "Test set size failed "<<std::endl;
        tape->set_size(0);
        if(tape->get_size() == 0) assert(true);
        else std::cerr << "Test set size failed "<<std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Test set size failed "<<std::endl;
        assert(false);
    }

    if(std::filesystem::exists(tape_filename))   std::remove(tape_filename);

    try{
        tape = std::make_shared<Tape>(tape_filename, 1, 2, 3);
        tape->set_size(-1);
        tape->set_size(-100);
        std::cerr << "Test set size failed (got negative size)"<<std::endl;
        assert(false);
    }
    catch (const std::runtime_error& e) {
        assert(true);
    }

    // raw input data
    std::vector<std::vector<int>> raw_data = {
        // normal
        {5, 1, 3, 4, 6, 1},
        // sorted
        {1, 2, 3, 4, 5, 6},
        {6, 5, 4, 3, 2, 1},
        // minus
        {-1, 5, 0, 3, 2, 1},
        // empty
        {},
        // one element     
        {1},
        // one num
        {1,1},
        // big data
        {5, 1, 3, 4, 6, 1,5, 1, 3, 4, 6, 1,5, 1, 3, 4, 6, 1,5, 1, 3, 4, 6, 1,5, 1, 3, 4, 6, 1,5, 1, 3, 4, 6, 1,5, 1, 3, 4, 6, 1,5, 1, 3, 4, 6, 1,5, 1, 3, 4, 6, 1,5, 1, 3, 4, 6, 1},
    };

    // ============ TEST SORT BY ALL DATA =================
    for(size_t i = 0; i < raw_data.size(); ++i){
        std::cout<< "TESTING TAPE: " << i << std::endl;
        // clear files
        if(std::filesystem::exists(tape_filename))   std::remove(tape_filename);
        
        // opening all files to start sort
        try{
            tape = std::make_shared<Tape>(tape_filename, 0, 0, 0);
        } 
        catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            return 1; 
        }

        vector2tape(raw_data.at(i), tape);

        // test if size is ok
        if(tape->get_size() != raw_data.at(i).size()){
            std::cerr << "Test iter " << i <<" not equal sizes: "<<tape->get_size()<<" vs "<<raw_data.at(i).size()<<std::endl;
            assert(false);
        }
        
        // test if it puts correctly
        if(!tape2vector(tape, raw_data.at(i))){
            std::cerr << "Test iter " << i <<" not equal tape and raw data"<<std::endl;
            assert(false);
        }

    }

    return 0; 
}


