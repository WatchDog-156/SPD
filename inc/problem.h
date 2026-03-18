#include "permutacja.h"

class Problem {
    int n;
public:
    Problem(int liczba): n(liczba){}

    void setN(int N) {n=N;}
    int getN() {return n;}
    int kryterium(Permutacja p);
    //Algorytm1();
    //Algorytm2();
};