#ifndef TAPESORTER_H
#define TAPESORTER_H

#include <set>

#include "Tape.hpp"

class TapeSorter{
protected:
    Tape *in_tape, *temp_tape, *out_tape;
    int memory_size, buffer_size;
    std::set<int> buffer, merge_buffer;
public:
    void bf_filler(std::multiset<int> &buffer, size_t start);
    void bf_tp_sort(std::multiset<int> &buffer, Tape &temp_tape, Tape &out_tape);

    TapeSorter(Tape *in_tape, Tape *temp_tape, Tape *out_tape, int memory_size);
    void sort();
};


#endif