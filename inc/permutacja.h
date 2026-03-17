#include <vector>
#include <iostream>

class Permutacja {
    int n;
public:
    Permutacja(int rozmiar): n(rozmiar) {} 

    std::vector<int> perm[];
    //next_permutacja

    friend std::ostream& operator<<(std::ostream& os, const Permutacja& perm);
    int& operator[](int indeks);
    bool operator==(const Permutacja& other) const;
    Permutacja& operator=(const Permutacja& other);
};