#include "problem.h"
#include <algorithm>
#include <queue> 
#include <cmath>

int Problem::kryterium(Permutacja p, const std::vector<Zadanie>& dane){
    int czasy_zadan[p.perm.size()] = {0};
    for(int i=0; i<m; i++){
        for(int j=0; j<p.perm.size(); j++){
            int idx = p.perm[j];

            if(j==0)
                czasy_zadan[j] = czasy_zadan[j] + dane[idx].times[i];
            else
                czasy_zadan[j] = std::max(czasy_zadan[j], czasy_zadan[j-1]) + dane[idx].times[i];
        }
    }

    return czasy_zadan[n-1];
}

int Problem::Algorytm_zupelny(const std::vector<Zadanie>& dane){
    Permutacja p(n);
    for(int i=0; i<n; i++) p.perm[i]=i;

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
    std::cout << "Permutacja dla przeglądu zupełnego: " << best_p << std::endl;

    return best_c_max;
}

int Problem::Algorytm_NEH(const std::vector<Zadanie>& dane){
    std::vector<std::pair<int, int>> sumy_zadan(n);
    for(int i=0; i<n; i++){
        int suma=0;
        for(int j=0; j<m; j++)
            suma += dane[i].times[j];
        sumy_zadan[i] = {i, suma};
    }

    std::sort(sumy_zadan.begin(), sumy_zadan.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second > b.second; 
    });

    Permutacja p(0);
    p.perm.push_back(sumy_zadan[0].first);
    
    for(int i=1; i<n; i++){
        int nowe_zadanie = sumy_zadan[i].first;

        int best_c_max = 9999999;
        Permutacja best_p(i+1);

        for(int j=0; j<i+1; j++){
            Permutacja tmp_p = p;
            tmp_p.perm.insert(tmp_p.perm.begin()+j, nowe_zadanie);

            int c_max = kryterium(tmp_p, dane);

            if(c_max < best_c_max){
                best_c_max = c_max;
                best_p = tmp_p;
            }
        }

        p = best_p;
    }

    int best_c_max = kryterium(p, dane);

    std::cout << "Najmniejsze C_max dla algorytmu NEH: " << best_c_max << std::endl;
    std::cout << "Permutacja dla algorytmu NEH: " << p << std::endl;

    return best_c_max;
}

int Problem::Algorytm_BandB(std::vector<Zadanie>& dane){
    int UB = Algorytm_NEH(dane);

    int LB = 0;
    for(int i=0; i<m; i++)
        LB += dane[0].times[i];
    for(int i=1; i<n; i++)
        LB += dane[i].times[m-1];

    Permutacja best_p(1);
    for(int i=0; i<n; i++){



        
        int c_max

        int current_LB = c_max;
        

        if(current_LB > UB)
            continue;

    }

    int best_c_max = kryterium(best_p, dane);

    std::cout << "Najmniejsze C_max dla algorytmu Branch and Bound: " << best_c_max << std::endl;
    std::cout << "Permutacja dla algorytmu Branch and Bound: " << best_p << std::endl;

    return best_c_max;
}

int Problem::Algorytm_AkceptacjiProgu(const std::vector<Zadanie>& dane){
    Permutacja p_init(n), p(n);
    for(int i=0; i<n; i++) p_init.perm[i]=i;

    int best_c_max = kryterium(p_init, dane);
    Permutacja best_p = p_init;

    float T=10;
    int k=1;

    while(k<=1000){
        p.perm=p_init.new_neighbour();
        int c_max = kryterium(p, dane);

        if((c_max-kryterium(p_init, dane))<T)
            p_init=p;
        if(c_max<best_c_max){
            best_c_max=c_max;
            best_p=p;
        }

        T=100*sin(0.1*k)/k;
        k++;
    }

    std::cout << "Najmniejsze C_max dla algorytmu akceptacji progu: " << best_c_max << std::endl;
    std::cout << "Permutacja dla algorytmu akceptacji progu: " << best_p << std::endl;

    return best_c_max;
}