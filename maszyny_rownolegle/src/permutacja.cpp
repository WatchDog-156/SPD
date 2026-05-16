#include "permutacja.h"
#include <algorithm>

Permutacja::Permutacja(int ilosc_zadan=0, int ilosc_maszyn=0): n(ilosc_zadan), m(ilosc_maszyn){
    podzial.resize(ilosc_zadan);
}

bool Permutacja::next_perm(){
    for(int i=n-1; i>=0; --i){
        if(podzial[i] < m-1){
            podzial[i]++;
            return true;
        } else
            podzial[i] = 0; 
    }
    
    return false;
}


int& Permutacja::operator[](int indeks){
    if(indeks < 0 || indeks >= n){
        std::cerr << "Podany błędny indeks podziału!";
        throw std::out_of_range("Indeks poza zakresem!");
    }

    return podzial[indeks];
}

bool Permutacja::operator==(const Permutacja& other) const{
    if(n != other.podzial.size())
        return false;

    for(int i=0; i<n; i++){
        if(podzial[i] != other.podzial[i])
            return false;
    }

    return true;
}

Permutacja& Permutacja::operator=(const Permutacja& other){
    if (this == &other) {
        return *this; 
    }

    this->n = other.podzial.size();
    this->podzial = other.podzial; 

    return *this;
}

std::ostream& operator<<(std::ostream& os, const Permutacja& permutacja){
    os << "(";
    for(int i=0; i<permutacja.n; i++){
        os << permutacja.podzial[i];
        if(i != permutacja.n-1)
            os << ","; 
    }
    os << ")";

    return os;
}