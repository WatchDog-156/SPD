#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "zadanie.h"
//#include "permutacja.h"
//#include "rozwiazanie.h"
//#include "problem.h"


int main() {

    std::vector<Zadanie> Zadania;

    std::string nazwa_pliku = "../dane_299.txt";
    std::ifstream plik(nazwa_pliku);
    if(!plik.is_open()) {
        std::cerr << "Nie można otworzyć pliku " << nazwa_pliku << "!" << std::endl;
        return 1;
    }
 
    std::string linia;
    while (std::getline(plik, linia)) {
        std::istringstream iss(linia);

        int rj;
        int pj;
        int dj;
        if(iss >> rj >> pj >> dj) 
            Zadania.emplace_back(rj, pj, dj);
        else
            std::cerr << "Niepoprawne dane wejściowe zadania!" << std::endl;
    }

    plik.close();

    std::sort(Zadania.begin(), Zadania.end(), [](const Zadanie& a, const Zadanie& b){
        return a.pj < b.pj;
    });
   
   for(const Zadanie& s : Zadania) {
        s.wyswietl();
    }

    //next_perm() 

    return 0;
}
