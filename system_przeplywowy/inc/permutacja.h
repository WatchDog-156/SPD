#ifndef PERMUTACJA_H
#define PERMUTACJA_H

#include <vector>
#include <iostream>

class Permutacja {
    int n;
public:
    Permutacja(int rozmiar);

    std::vector<int> perm;
    bool next_perm(); 
    std::vector<int> new_neighbour();

    int& operator[](int indeks);
    bool operator==(const Permutacja& other) const;
    Permutacja& operator=(const Permutacja& other);
    friend std::ostream& operator<<(std::ostream& os, const Permutacja& perm);
};

#endif