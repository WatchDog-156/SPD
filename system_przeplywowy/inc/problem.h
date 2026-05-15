#ifndef PROBLEM_H
#define PROBLEM_H

#include "permutacja.h"
#include "zadanie.h" 

class Problem { 
    int n;
    int m;
public:
    // int UB=999999;
    // Permutacja best_p = Permutacja(n);

    Problem(int ilosc_zadan, int ilosc_maszyn): n(ilosc_zadan), m(ilosc_maszyn) {}

    void setN(int N) {n=N;}
    void setM(int M) {m=M;}
    int getN() {return n;}
    int getM() {return m;}
    int kryterium(Permutacja p, const std::vector<Zadanie>& dane);   
    int Algorytm_zupelny(const std::vector<Zadanie>& dane);
    int Algorytm_NEH(const std::vector<Zadanie>& dane);
    int Algorytm_BandB(std::vector<Zadanie>& dane);
    int Algorytm_AkceptacjiProgu(const std::vector<Zadanie>& dane);
};

#endif