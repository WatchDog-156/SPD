#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "zadanie.h"
#include "permutacja.h"
#include "rozwiazanie.h"
#include "problem.h"


int main() {

    std::vector<Zadanie> zadania;

    std::string nazwa_pliku = "../dane_299.txt";
    // std::string nazwa_pliku = "../test.txt";
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
        if(iss >> rj >> pj >> dj) 
            zadania.emplace_back(rj, pj, dj);
        else
            std::cerr << "Niepoprawne dane wejściowe zadania!" << std::endl;
    }

    plik.close();


    Problem prob(zadania.size());

    std::cout << "Algorytm ERD" << std::endl;
    prob.Algorytm_ERD(zadania);
    std::cout << std::endl;

    std::cout << "Algorytm EDD" << std::endl;
    prob.Algorytm_EDD(zadania);
    std::cout << std::endl;

    prob.setN(10);
    std::cout << "Przegląd zupełny" << std::endl;
    prob.Algorytm_zupelny(zadania);
    std::cout << std::endl;

    prob.setN(zadania.size());
    std::cout << "Algorytm wlasny" << std::endl;
    prob.Algorytm_wlasny(zadania);
    std::cout << std::endl;

    std::cout << "Algorytm Schrage" << std::endl;
    prob.Algorytm_Schrage(zadania);
    std::cout << std::endl;

    std::cout << "Algorytm Schrage z przerwaniami" << std::endl;
    prob.Algorytm_Schrage_z_podzialem(zadania);
    std::cout << std::endl;

    // prob.setN(30);
    std::cout << "Algorytm Branch and Bound (algorytm Carliera)" << std::endl;
    prob.Algorytm_BandB(zadania);
    std::cout << "Najlepsze L_max dla algorytmu B&B: " << prob.UB << std::endl;
    std::cout << "Permutacja dla algorytmu B&B: " << prob.best_p << std::endl;
    std::cout << std::endl;

    return 0;
}
