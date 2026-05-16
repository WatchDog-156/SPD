#ifndef ROZWIAZANIE_H
#define ROZWIAZANIE_H

#include "permutacja.h"

class Rozwiazanie {
public:
    int kryterium;
    Permutacja p;

    Rozwiazanie(int kryt, Permutacja perm): kryterium(kryt), p(perm){}
};

#endif