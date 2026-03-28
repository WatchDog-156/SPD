#ifndef PROBLEM_H
#define PROBLEM_H

#include "permutacja.h"
#include "zadanie.h"

class Problem {
    int n;
public:
    Problem(int liczba): n(liczba){}

    void setN(int N) {n=N;}
    int getN() {return n;}
    int kryterium(Permutacja p, const std::vector<Zadanie>& dane);
    int Algorytm_ERD(const std::vector<Zadanie>& dane);
    int Algorytm_EDD(const std::vector<Zadanie>& dane);
    int Algorytm_zupelny(const std::vector<Zadanie>& dane);
    int Algorytm_wlasny(const std::vector<Zadanie>& dane);
    // int Algorytm_BandB(const std::vector<Zadanie>& dane);
};

#endif