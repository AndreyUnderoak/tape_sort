#ifndef TAPESORTER_H
#define TAPESORTER_H

#include <set>

#include "Tape.hpp"

class TapeSorter{
protected:
    Tape *in_tape, *temp_tape, *out_tape;
    int memory_size, buffer_size;
    std::set<int> buffer, merge_buffer;

    void bf_filler(std::set<int> &buffer, int start);
    void bf_tp_sort(std::set<int> &buffer, Tape &temp_tape, Tape &out_tape);
public:
    TapeSorter(Tape *in_tape, Tape *temp_tape, Tape *out_tape, int memory_size);
    void sort();
};


#endif