#ifndef ZADANIA_H
#define ZADANIA_H

#include <vector>

class Zadanie {
public:
    std::vector<int> times;   

    Zadanie(const std::vector<int>& t) : times(t) {}
    void wyswietl() const;
};

#endif