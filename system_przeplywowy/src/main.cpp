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

    std::vector<Zadanie> zadania;

    std::string nazwa_pliku = "../100_Independent0376";

    std::ifstream plik(nazwa_pliku);
    if(!plik.is_open()) {
        std::cerr << "Nie można otworzyć pliku " << nazwa_pliku << "!" << std::endl;
        return 1;
    }
 
    int ilosc_zadan;
    std::string linia;
    std::getline(plik, linia);
    std::istringstream iss(linia);
    if(!(iss >> ilosc_zadan)){
        std::cerr << "Niepoprawnie zdefiniowana ilość zadań!" << std::endl;
        return 1;
    }

    while (std::getline(plik, linia)) {
        std::istringstream iss(linia);

        int rj;
        int pj;
        int dj;
        if(iss >> pj >> rj >> dj) 
            zadania.emplace_back(rj, pj, dj);
        else
            std::cerr << "Niepoprawne dane wejściowe zadania!" << std::endl;
    }

    plik.close();


    Problem prob(zadania.size());

    
    std::cout << "Algorytm ERD" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    prob.Algorytm_ERD(zadania);
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli>  ms = stop - start;
    std::cout << "Czas: " << ms.count() << " ms" << std::endl;
    std::cout << std::endl;

    std::cout << "Algorytm EDD" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    prob.Algorytm_EDD(zadania);
    stop = std::chrono::high_resolution_clock::now();
    ms = stop - start;
    std::cout << "Czas: " << ms.count() << " ms" << std::endl;
    std::cout << std::endl;

    // prob.setN(12);
    // std::cout << "Przegląd zupełny" << std::endl;
    // start = std::chrono::high_resolution_clock::now();
    // prob.Algorytm_zupelny(zadania);
    // stop = std::chrono::high_resolution_clock::now();
    // ms = stop - start;
    // std::cout << "Czas: " << ms.count() << " ms" << std::endl;
    // std::cout << std::endl;

    prob.setN(zadania.size());
    std::cout << "Algorytm wlasny" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    prob.Algorytm_wlasny(zadania, 0.5);
    stop = std::chrono::high_resolution_clock::now();
    ms = stop - start;
    std::cout << "Czas: " << ms.count() << " ms" << std::endl;
    std::cout << std::endl;

    std::cout << "Algorytm Schrage" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    prob.Algorytm_Schrage(zadania);
    stop = std::chrono::high_resolution_clock::now();
    ms = stop - start;
    std::cout << "Czas: " << ms.count() << " ms" << std::endl;
    std::cout << std::endl;

    std::cout << "Algorytm Schrage z przerwaniami" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    prob.Algorytm_Schrage_z_podzialem(zadania);
    stop = std::chrono::high_resolution_clock::now();
    ms = stop - start;
    std::cout << "Czas: " << ms.count() << " ms" << std::endl;
    std::cout << std::endl;

    // prob.setN(30);
    std::cout << "Algorytm Branch and Bound (algorytm Carliera)" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    prob.Algorytm_BandB(zadania);
    stop = std::chrono::high_resolution_clock::now();
    ms = stop - start;
    std::cout << "Czas: " << ms.count() << " ms" << std::endl;
    std::cout << "Najlepsze L_max dla algorytmu B&B: " << prob.UB << std::endl;
    std::cout << "Permutacja dla algorytmu B&B: " << prob.best_p << std::endl;
    std::cout << std::endl;

    int opt_L = prob.UB;
    start = std::chrono::high_resolution_clock::now();
    prob.Alpha_Analysis(zadania, opt_L, 50);
    stop = std::chrono::high_resolution_clock::now();
    ms = stop - start;
    std::cout << "Czas: " << ms.count() << " ms" << std::endl;
    std::cout << std::endl;


    return 0;
}
