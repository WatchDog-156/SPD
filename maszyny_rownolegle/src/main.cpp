#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <chrono>

#include "zadanie.h"
#include "permutacja.h"
#include "rozwiazanie.h"
#include "problem.h"


int main() {
    std::string nazwa_pliku = "../test/tail.dat";

    std::ifstream plik(nazwa_pliku);
    if(!plik.is_open()) {
        std::cerr << "Nie można otworzyć pliku " << nazwa_pliku << "!" << std::endl;
        return 1;
    }
 
    int ilosc_instancji;
    std::string linia;
    std::getline(plik, linia);
    std::istringstream iss(linia);
    if(!(iss >> ilosc_instancji)){
        std::cerr << "Niepoprawnie zdefiniowana ilość instancji!" << std::endl;
        return 1;
    }

    int wybrana_instancja = 3;
    if(wybrana_instancja > ilosc_instancji || wybrana_instancja <= 0){
        std::cerr << "Niepoprawna instancja do pracy!" << std::endl;
        return 1;
    }

    int aktualna_instancja = 0;
    int ilosc_zadan = 0;
    int ilosc_maszyn = 0;
    int trash;
    while(std::getline(plik, linia)){
        std::istringstream iss(linia);

        if(!(iss >> ilosc_zadan >> ilosc_maszyn >> trash)){
            aktualna_instancja++;
            if(aktualna_instancja==wybrana_instancja){
                std::cout << "Ilość zadań: " << ilosc_zadan << ",ilość maszyn: " << ilosc_maszyn << std::endl;
                break;
            } 
        }
    }

    std::vector<Zadanie> zadania;

    for (int i=0; i<ilosc_zadan; i++) {
        zadania.emplace_back(std::vector<int>());

        std::getline(plik, linia);
        std::istringstream iss(linia);
        int czas;

        for(int j=0; j<2*ilosc_maszyn; j++) {
            if(iss >> czas){
                if(!(j%2)) continue;
                else zadania[i].time = czas;
            }else
                std::cerr << "Niepoprawne dane wejściowe zadania!" << std::endl;
        }
        // zadania[i].wyswietl();
    }

    plik.close();

    Problem prob(ilosc_zadan, ilosc_maszyn);

    prob.setN(9);
    std::cout << std::endl;
    std::cout << "Przegląd zupełny" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    prob.Algorytm_zupelny(zadania);
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms = stop - start;
    std::cout << "Czas: " << ms.count() << " ms" << std::endl;

    prob.setN(ilosc_zadan);
    std::cout << std::endl;
    std::cout << "Algorytm LSA" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    prob.Algorytm_LSA(zadania);
    stop = std::chrono::high_resolution_clock::now();
    ms = stop - start;
    std::cout << "Czas: " << ms.count() << " ms" << std::endl;

    std::cout << std::endl;
    std::cout << "Algorytm LPT" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    prob.Algorytm_LPT(zadania);
    stop = std::chrono::high_resolution_clock::now();
    ms = stop - start;
    std::cout << "Czas: " << ms.count() << " ms" << std::endl;

    return 0;
}
