#ifndef PROBLEM_H
#define PROBLEM_H

#include "permutacja.h"
#include "zadanie.h" 

struct Node{
    Permutacja perm;
    std::vector<int> pozostale;

    int LB;

    bool operator > (const Node& inny) const{
        return LB>inny.LB;
    }
};

class Problem { 
    int n;
    int m;
public:

    Problem(int ilosc_zadan, int ilosc_maszyn): n(ilosc_zadan), m(ilosc_maszyn) {}

    void setN(int N) {n=N;}
    void setM(int M) {m=M;}
    int getN() {return n;}
    int getM() {return m;}
    int kryterium(Permutacja p, const std::vector<Zadanie>& dane);   
    int Algorytm_zupelny(const std::vector<Zadanie>& dane);
    int Algorytm_NEH(const std::vector<Zadanie>& dane, bool show=true);
    int Oblicz_LB(Node dziecko, const std::vector<Zadanie>& dane);
    int Algorytm_BandB(std::vector<Zadanie>& dane);
    int Algorytm_AkceptacjiProgu(const std::vector<Zadanie>& dane);
};

#endif