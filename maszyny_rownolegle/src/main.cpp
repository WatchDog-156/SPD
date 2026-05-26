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
    std::string nazwa_pliku = "../dane.txt";

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
        iss.clear();
        iss.str(linia);

        if(!(iss >> ilosc_maszyn >> ilosc_zadan >> trash)){
            aktualna_instancja++;
            if(aktualna_instancja==wybrana_instancja){
                std::cout << "Ilość zadań: " << ilosc_zadan << ", ilość maszyn: " << ilosc_maszyn << std::endl;
                break;
            } 
        }
    }

    std::vector<Zadanie> zadania;

    std::getline(plik, linia);
    iss.clear();
    iss.str(linia);
    int czas;
    for (int i=0; i<ilosc_zadan; i++){
        if(!(iss >> czas)){
            std::cerr << "Niepoprawne dane wejściowe zadania!" << std::endl;
            return 1;
        }
        zadania.emplace_back(czas);
        // zadania[i].wyswietl();
    }

    plik.close();

    Problem prob(ilosc_zadan, ilosc_maszyn);

    prob.setN(ilosc_zadan);
    prob.setM(4);
    std::cout << std::endl;
    std::cout << "Algorytm LSA" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    prob.Algorytm_LSA(zadania);
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms = stop - start;
    std::cout << "Czas: " << ms.count() << " ms" << std::endl;

    std::cout << std::endl;
    std::cout << "Algorytm LPT" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    prob.Algorytm_LPT(zadania);
    stop = std::chrono::high_resolution_clock::now();
    ms = stop - start;
    std::cout << "Czas: " << ms.count() << " ms" << std::endl;

    prob.setM(2);
    std::cout << std::endl;
    std::cout << "Algorytm programowania dynamicznego dla 2 maszyn" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    prob.Algorytm_PD2(zadania);
    stop = std::chrono::high_resolution_clock::now();
    ms = stop - start;
    std::cout << "Czas: " << ms.count() << " ms" << std::endl;

    prob.setN(10);
    std::cout << std::endl;
    std::cout << "Przegląd zupełny dla 2 maszyn" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    prob.Algorytm_zupelny(zadania);
    stop = std::chrono::high_resolution_clock::now();
    ms = stop - start;
    std::cout << "Czas: " << ms.count() << " ms" << std::endl;

    prob.setN(ilosc_zadan);
    std::cout << std::endl;
    std::cout << "Algorytm PTAS dla 2 maszyn" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    prob.Algorytm_PTAS(zadania, 5);
    stop = std::chrono::high_resolution_clock::now();
    ms = stop - start;
    std::cout << "Czas: " << ms.count() << " ms" << std::endl;

    std::cout << std::endl;
    std::cout << "Algorytm FPTAS dla 2 maszyn" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    prob.Algorytm_FPTAS2(zadania, 5);
    stop = std::chrono::high_resolution_clock::now();
    ms = stop - start;
    std::cout << "Czas: " << ms.count() << " ms" << std::endl;

    prob.setM(3);
    std::cout << std::endl;
    std::cout << "Algorytm PTAS dla 3 maszyn" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    prob.Algorytm_PTAS(zadania, 5);
    stop = std::chrono::high_resolution_clock::now();
    ms = stop - start;
    std::cout << "Czas: " << ms.count() << " ms" << std::endl;

    prob.setN(10);
    std::cout << std::endl;
    std::cout << "Przegląd zupełny dla 3 maszyn" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    prob.Algorytm_zupelny(zadania);
    stop = std::chrono::high_resolution_clock::now();
    ms = stop - start;
    std::cout << "Czas: " << ms.count() << " ms" << std::endl;

    prob.setN(ilosc_zadan);
    std::cout << std::endl;
    std::cout << "Algorytm programowania dynamicznego dla 3 maszyn" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    prob.Algorytm_PD3(zadania);
    stop = std::chrono::high_resolution_clock::now();
    ms = stop - start;
    std::cout << "Czas: " << ms.count() << " ms" << std::endl;

    return 0;
}
