#include "problem.h"
#include <algorithm>
#include <queue> 
#include <cmath>

int Problem::kryterium(Permutacja p, const std::vector<Zadanie>& dane){
    int size = p.podzial.size();
    if(size==0) return 0;

    std::vector<int> czasy_maszyn(m, 0);

    for(int i=0; i<size; i++)
        czasy_maszyn[p.podzial[i]] += dane[i].time;

    return *std::max_element(czasy_maszyn.begin(), czasy_maszyn.end());
}

int Problem::Algorytm_zupelny(const std::vector<Zadanie>& dane){
    Permutacja p(n,m);
    for(int i=0; i<n; i++) p.podzial[i]=0;

    int best_c_max = 9999999;
    Permutacja best_p = p;

    do{
        int aktualny = this->kryterium(p, dane);
        if(aktualny < best_c_max){
            best_c_max = aktualny;
            best_p = p;
        }
    } while(p.next_perm());

    std::cout << "Najmniejsze C_max dla przeglądu zupełnego: " << best_c_max << std::endl;
    std::cout << "Podział zadań na maszynach dla przeglądu zupełnego: " << best_p << std::endl;

    return best_c_max;
}

int Problem::Algorytm_LSA(const std::vector<Zadanie>& dane, bool show){
    Permutacja p(n,m);
    std::vector<int> czasy_maszyn(m, 0);

    for(int i=0; i<n; i++){
        int zadanie = dane[i].time;
        auto wybrana_maszyna = std::min_element(czasy_maszyn.begin(), czasy_maszyn.end());
        p.podzial[i] = std::distance(czasy_maszyn.begin(), wybrana_maszyna);
        *wybrana_maszyna += zadanie;
    }

    int best_c_max = this->kryterium(p, dane);

    if(show){
        std::cout << "Najmniejsze C_max dla algorytmu LSA: " << best_c_max << std::endl;
        std::cout << "Podział zadań na maszynach dla algorytmu LSA: " << p << std::endl;
    }

    return best_c_max;
}

int Problem::Algorytm_LPT(const std::vector<Zadanie>& dane){
    std::vector<Zadanie> posortowane_dane = dane;

    std::sort(posortowane_dane.begin(), posortowane_dane.end(), [](const Zadanie& a, const Zadanie& b) {
        return a.time > b.time;
    });

    int best_c_max = this->Algorytm_LSA(posortowane_dane, false);

    std::cout << "Dane posortowano malejąco po czasie wykonania" << std::endl;
    std::cout << "Najmniejsze C_max dla algorytmu LPT: " << best_c_max << std::endl;

    return best_c_max;
}