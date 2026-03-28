#ifndef PROBLEM_H
#define PROBLEM_H

#include "permutacja.h"
#include "zadanie.h"

class Problem {
    int n;
    int UB=999999;
    Permutacja best_p = Permutacja(n);
public:
    Problem(int liczba): n(liczba){}

    void setN(int N) {n=N;}
    int getN() {return n;}
    int kryterium(Permutacja p, const std::vector<Zadanie>& dane);
    void Search_critical_block(Permutacja p, const std::vector<Zadanie>& dane, int critical_parameters[]);    
    int Algorytm_ERD(const std::vector<Zadanie>& dane);
    int Algorytm_EDD(const std::vector<Zadanie>& dane);
    int Algorytm_zupelny(const std::vector<Zadanie>& dane);
    int Algorytm_wlasny(const std::vector<Zadanie>& dane);
    std::pair<int, Permutacja> Algorytm_Schrage(const std::vector<Zadanie>& dane);
    int Algorytm_BandB(std::vector<Zadanie>& dane);
};

#endif