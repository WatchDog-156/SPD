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
    // void Search_critical_block(Permutacja p, const std::vector<Zadanie>& dane, int critical_parameters[]);    
    // int Algorytm_ERD(const std::vector<Zadanie>& dane);
    // int Algorytm_EDD(const std::vector<Zadanie>& dane);
    // int Algorytm_zupelny(const std::vector<Zadanie>& dane);
    // int Algorytm_wlasny(const std::vector<Zadanie>& dane, double alpha);
    // std::pair<int, Permutacja> Algorytm_Schrage(const std::vector<Zadanie>& dane, bool show=true);
    // int Algorytm_Schrage_z_podzialem(const std::vector<Zadanie>& dane, bool show=true);
    // int Algorytm_BandB(std::vector<Zadanie>& dane);
};

#endif