#include "zadanie.h"
#include <iostream>

void Zadanie::wyswietl() const {
    std::cout << "Czasy na maszynach: ";
    for (int czas : times) {
        std::cout << czas << " ";
    }
    std::cout << std::endl;
}