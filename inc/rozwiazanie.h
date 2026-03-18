#ifndef ROZWIAZANIE_H
#define ROZWIAZANIE_H

#include "permutacja.h"

class Rozwiazanie {
public:
    Rozwiazanie(int kryt, Permutacja perm): kryterium(kryt), p(perm){}

    int kryterium;
    Permutacja p;
};

#endif