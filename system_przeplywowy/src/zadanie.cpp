#include "zadanie.h"
#include <iostream>

void Zadanie::wyswietl() const {
    std::cout << "Termin dostępności: " << rj
              << "\nCzas wykonywania: " << pj
              << "\nPorządany termin zakończenia wykonywania: " << dj << std::endl << std::endl;
}