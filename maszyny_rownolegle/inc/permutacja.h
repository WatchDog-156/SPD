#ifndef PERMUTACJA_H
#define PERMUTACJA_H

#include <vector>
#include <iostream>

class Permutacja {
    int n;
    int m;
public:
    Permutacja(int ilosc_zadan=0, int ilosc_maszyn=0);

    std::vector<int> podzial;              
    bool next_perm(); 

    int& operator[](int indeks);
    bool operator==(const Permutacja& other) const;
    Permutacja& operator=(const Permutacja& other);
    friend std::ostream& operator<<(std::ostream& os, const Permutacja& perm);
};

#endif