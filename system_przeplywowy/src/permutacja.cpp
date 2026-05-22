#include "permutacja.h"
#include <algorithm>

Permutacja::Permutacja(int rozmiar): n(rozmiar){
    perm.resize(rozmiar);
    srand(time(0));
}

bool Permutacja::next_perm(){
    bool result = std::next_permutation(perm.begin(), perm.end());
    return result;
}

std::vector<int> Permutacja::new_neighbour(){
    std::vector<int> neighbour = perm;
    int idx = rand()%(n-1);

    std::swap(neighbour[idx], neighbour[idx+1]);

    return neighbour;
}

int& Permutacja::operator[](int indeks){
    if(indeks < 0 || indeks >= n){
        std::cerr << "Podany błędny indeks permutacji!";
        throw std::out_of_range("Indeks poza zakresem!");
    }

    return perm[indeks];
}

bool Permutacja::operator==(const Permutacja& other) const{
    if(n != other.perm.size())
        return false;

    for(int i=0; i<n; i++){
        if(perm[i] != other.perm[i])
            return false;
    }

    return true;
}

Permutacja& Permutacja::operator=(const Permutacja& other){
    if (this == &other) {
        return *this; 
    }

    this->n = other.perm.size();
    this->perm = other.perm; 

    return *this;
}

std::ostream& operator<<(std::ostream& os, const Permutacja& permutacja){
    os << "(";
    for(int i=0; i<permutacja.perm.size(); i++){
        os << permutacja.perm[i];
        if(i != (int)permutacja.perm.size()-1)
            os << ","; 
    }
    os << ")";

    return os;
}