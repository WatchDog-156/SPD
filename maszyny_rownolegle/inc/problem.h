#ifndef PROBLEM_H
#define PROBLEM_H

#include "permutacja.h"
#include "zadanie.h" 

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
    int Algorytm_LSA(const std::vector<Zadanie>& dane, bool show=true);
    int Algorytm_LPT(const std::vector<Zadanie>& dane);
    std::pair<Permutacja, int> Algorytm_PD2(const std::vector<Zadanie>& dane);
    int Algorytm_zupelny(const std::vector<Zadanie>& dane);
    int Algorytm_PTAS(const std::vector<Zadanie>& dane, int k);
    int Algorytm_FPTAS2(const std::vector<Zadanie>& dane, int k);
    int Algorytm_PD3(const std::vector<Zadanie>& dane);
};

#endif