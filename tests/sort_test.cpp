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
#include "TapeSorter.hpp"

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
    * Checking if tape equal to set
    * @return true if equal
*/
bool tape2set_equal(std::shared_ptr<Tape>& tape, const std::multiset<int>& mset){
    tape->go_front();
    size_t tape_pos = 0;
    for(const auto& num : mset){
        std::cout<<num<<" vs "<<tape->read_value()<< std::endl;
        if(num != tape->read_value()) return false;
        tape->go_to(++tape_pos);
    }
    return true;
}


int main() {

    // ============ PREPARE =================
    // filenames
    const char* in_filename     = "../tests/files/in.bin";
    const char* out_filename    = "../tests/files/out.bin";
    const char* temp_filename   = "../tests/files/temp.bin";
    
    // raw input data
    std::vector<std::vector<int>> raw_data = {
        // normal
        {5, 1, 3, 4, 6, 1},
        {6, 5, 4, 3, 2, 1, 9},
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

    // sorted data
    std::vector<std::multiset<int>> sort_data;
    for (const auto& row_arr : raw_data) {
        sort_data.emplace_back(row_arr.begin(), row_arr.end());
    }
    
    std::shared_ptr<Tape> tape_in, tape_temp, tape_out;

    std::cout<< "START TESTING" << std::endl;
    // ============ TEST SORT BY ALL DATA =================
    for(size_t i = 0; i < raw_data.size(); ++i){
        std::cout<< "TESTING SORTING: " << i << std::endl;
        // clear files
        if(std::filesystem::exists(in_filename))   std::remove(in_filename);
        if(std::filesystem::exists(out_filename))  std::remove(out_filename);
        if(std::filesystem::exists(temp_filename)) std::remove(temp_filename);
        
        // opening all files to start sort
        try{
            tape_in = std::make_shared<Tape>(in_filename, 0, 0, 0);
            tape_temp = std::make_shared<Tape>(temp_filename, 0, 0, 0);
            tape_out = std::make_shared<Tape>(out_filename, 0, 0, 0);
        } 
        catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            return 1; 
        }

        vector2tape(raw_data.at(i), tape_in);

        TapeSorter ts(tape_in, tape_temp, tape_out, 4);

        ts.sort();

        // test if size is ok
        if(tape_in->get_size() != tape_out->get_size()){
            std::cerr << "Test iter " << i <<" not equal sizes: "<<tape_in->get_size()<<" vs "<<tape_out->get_size()<<std::endl;
            assert(false);
        }
        
        // test if it sorted correctly
        if(!tape2set_equal(tape_out, sort_data.at(i))){
            std::cerr << "Test iter " << i <<" not equal tape and sorted data"<<std::endl;
            assert(false);
        }

    }

    // ============ TEST SORT WITH DIFFERENT RAM BY LAST DATA =================
    std::cout<< "START TESTING SORTING WITH DIFFERENT RAM INPUT" << std::endl;
    TapeSorter ts(tape_in, tape_temp, tape_out, 2);

    // BAD RAM: need exeption
    try{
        ts = TapeSorter(tape_in, tape_temp, tape_out, 0);
        std::cerr << "Test RAM " << 0 <<" Sorter doesn't throw an exeption "<<std::endl;
        assert(false);
    }
    catch (const std::runtime_error& e) {
        assert(true);
    }

    try{
        ts = TapeSorter(tape_in, tape_temp, tape_out, -1);
        std::cerr << "Test RAM " << -1 <<" Sorter doesn't throw an exeption "<<std::endl;
        assert(false);
    }
    catch (const std::runtime_error& e) {
        assert(true);
    }

    try{
        ts = TapeSorter(tape_in, tape_temp, tape_out, -100);
        std::cerr << "Test RAM " << -100 <<" Sorter doesn't throw an exeption "<<std::endl;
        assert(false);
    }
    catch (const std::runtime_error& e) {
        assert(true);
    }




    // RAM % 2 == 0
    ts = TapeSorter(tape_in, tape_temp, tape_out, 2);
    ts.sort();
    // test if size is ok
    if(tape_in->get_size() != tape_out->get_size()){
        std::cerr << "Test iter RAM % 2 == 0 not equal sizes: "<<tape_in->get_size()<<" vs "<<tape_out->get_size()<<std::endl;
        assert(false);
    }
    // test if it sorted correctly
    if(!tape2set_equal(tape_out, sort_data.back())){
        std::cerr << "Test RAM % 2 == 0 not equal tape and sorted data"<<std::endl;
        assert(false);
    }

    // RAM % 2 == 1
    ts = TapeSorter(tape_in, tape_temp, tape_out, 3);
    ts.sort();
    // test if size is ok
    if(tape_in->get_size() != tape_out->get_size()){
        std::cerr << "Test iter RAM % 2 == 1 not equal sizes: "<<tape_in->get_size()<<" vs "<<tape_out->get_size()<<std::endl;
        assert(false);
    }
    // test if it sorted correctly
    if(!tape2set_equal(tape_out, sort_data.back())){
        std::cerr << "Test RAM % 2 == 1 not equal tape and sorted data"<<std::endl;
        assert(false);
    }

    // RAM == data.size / 2
    ts = TapeSorter(tape_in, tape_temp, tape_out, tape_in->get_size()/2);
    ts.sort();
    // test if size is ok
    if(tape_in->get_size() != tape_out->get_size()){
        std::cerr << "Test iter RAM == data.size / 2 not equal sizes: "<<tape_in->get_size()<<" vs "<<tape_out->get_size()<<std::endl;
        assert(false);
    }
    // test if it sorted correctly
    if(!tape2set_equal(tape_out, sort_data.back())){
        std::cerr << "Test RAM == data.size / 2 not equal tape and sorted data"<<std::endl;
        assert(false);
    }

    // RAM == data.size 
    ts = TapeSorter(tape_in, tape_temp, tape_out, tape_in->get_size());
    ts.sort();
    // test if size is ok
    if(tape_in->get_size() != tape_out->get_size()){
        std::cerr << "Test iter RAM == data.size  not equal sizes: "<<tape_in->get_size()<<" vs "<<tape_out->get_size()<<std::endl;
        assert(false);
    }
    // test if it sorted correctly
    if(!tape2set_equal(tape_out, sort_data.back())){
        std::cerr << "Test RAM == data.size  not equal tape and sorted data"<<std::endl;
        assert(false);
    }

    // RAM == data.size * 2 
    ts = TapeSorter(tape_in, tape_temp, tape_out, tape_in->get_size() * 2);
    ts.sort();
    // test if size is ok
    if(tape_in->get_size() != tape_out->get_size()){
        std::cerr << "Test iter RAM == data.size  not equal sizes: "<<tape_in->get_size()<<" vs "<<tape_out->get_size()<<std::endl;
        assert(false);
    }
    // test if it sorted correctly
    if(!tape2set_equal(tape_out, sort_data.back())){
        std::cerr << "Test RAM == data.size  not equal tape and sorted data"<<std::endl;
        assert(false);
    }

    return 0; 
}


