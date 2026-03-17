#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "zadanie.h"



int main() {

    std::vector<Zadanie> Zadania;
    std::ifstream plik("dane.txt");

    if(!plik.is_open()) {
        std::cerr << "Nie można otworzyć pliku dane.txt!" << std::endl;
        return 1;
    }
 
    std::string linia;
    while (std::getline(plik, linia)) {
        std::istringstream iss(linia);
        int rj;
        int pj;
        int dj;
        if (iss >> rj >> pj >> dj) {
            Zadania.emplace_back(rj, pj, dj);
        }
    }

    plik.close();
    //next_perm() i sort()
    std::sort(Zadania.begin(), Zadania.end(), [](int a, int b)
                                  {
                                      return a > b;
                                  });
   
   for (const auto& s : Zadania) {
        s.wyswietl();
    }
    return 0;
}
