#include "problem.h"
#include <algorithm>

int Problem::kryterium(Permutacja p, const std::vector<Zadanie>& dane){
    int czas = 0;
    int L_max = -99999;
    for(int i=0; i<n; i++){
        int idx = p.perm[i];

        czas = std::max(czas, dane[idx].rj)+dane[idx].pj;
        L_max = std::max(L_max, czas-dane[idx].dj);
    }

    return L_max;
}

int Problem::Algorytm_ERD(const std::vector<Zadanie>& dane){
    Permutacja p(n);
    
    std::vector<int> idx(n);
    for(int i=0; i<n; i++) idx[i]=i;

    std::sort(idx.begin(), idx.end(), [&](int a, int b){
        return dane[a].rj < dane[b].rj;
    }); 

    for(int i=0; i<n; i++) p.perm[i] = idx[i];

    int L = this->kryterium(p, dane);

    std::cout << "L_max dla ERD: " << L << std::endl;
    std::cout << "Permutacja dla ERD: " << p << std::endl;

    return L;
}

int Problem::Algorytm_EDD(const std::vector<Zadanie>& dane){
    Permutacja p(n);
    
    std::vector<int> idx(n);
    for(int i=0; i<n; i++) idx[i]=i;

    std::sort(idx.begin(), idx.end(), [&](int a, int b){
        return dane[a].dj < dane[b].dj;
    }); 

    for(int i=0; i<n; i++) p.perm[i] = idx[i];

    int L = this->kryterium(p, dane);

    std::cout << "L_max dla EDD: " << L << std::endl;
    std::cout << "Permutacja dla EDD: " << p << std::endl;

    return L;
}

int Problem::Algorytm_zupelny(const std::vector<Zadanie>& dane){
    Permutacja p(n);
    for(int i=0; i<n; i++) p.perm[i]=i;

    int best_l = 99999;
    Permutacja best_p = p;

    do{
        int aktualny = this->kryterium(p, dane);
        if(aktualny < best_l){
            best_l = aktualny;
            best_p = p;
        }
    } while(p.next_perm());

    std::cout << "Nalepsze L_max: " << best_l << std::endl;
    std::cout << "Permutacja: " << best_p << std::endl;

    return best_l;
}