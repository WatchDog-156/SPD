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

std::pair<Permutacja, int> Problem::Algorytm_PD2(const std::vector<Zadanie>& dane, bool show){
    if(m!=2) return {Permutacja(n,m), -1};

    int s = 0;
    for(auto it=dane.begin(); it!=dane.end(); ++it)
        s += it->time;

    std::vector<std::vector<bool>> B(n+1, std::vector<bool>(s/2+1, false));
    B[0][0] = true;

    for(int j=1; j<=n; j++){
        for(int k=0; k<=s/2; k++){
            if(B[j-1][k] == true || (k >= dane[j-1].time && B[j-1][k-dane[j-1].time] == true))
                B[j][k] = true;
        }
    }

    int c_opt = s;
    int k_opt = 0;
    
    for(int k=0; k<=s/2; k++){
        if(B[n][k] == true){
            int t = s-k;
            int current_max = std::max(t, k);
            if(current_max < c_opt){
                c_opt = current_max;
                k_opt = k;
            }
        }
    }

    Permutacja best_p(n, m);
    int obecne_k = k_opt;
    
    for(int j=n; j>0; j--) {
        if(obecne_k >= dane[j-1].time && B[j-1][obecne_k - dane[j-1].time] == true) {
            best_p.podzial[j-1] = 0; 
            obecne_k -= dane[j-1].time; 
        } else 
            best_p.podzial[j-1] = 1;
    }

    if(show)
        std::cout << "Najmniejsze C_max dla algorytmu programowania dynamicznego dla 2 maszyn: " << c_opt << std::endl;

    return {best_p, c_opt};
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

int Problem::Algorytm_PTAS(const std::vector<Zadanie>& dane, int k){
    k = std::min(k, n);

    std::vector<Zadanie> posortowane_dane = dane;

    std::sort(posortowane_dane.begin(), posortowane_dane.end(), [](const Zadanie& a, const Zadanie& b) {
        return a.time > b.time;
    });

    std::vector<Zadanie> male;
    std::vector<Zadanie> duze;

    for(int i=0; i<n; i++){
        if(i<k)
            duze.push_back(posortowane_dane[i]);
        else    
            male.push_back(posortowane_dane[i]);
    }

    Permutacja p(k,m);
    for(int i=0; i<k; i++) p.podzial[i]=0;

    int best_c_max = 9999999;
    Permutacja best_p = p;

    do{
        std::vector<int> maszyny(m,0);
        for(int i=0; i<k; i++)
            maszyny[p.podzial[i]] += duze[i].time;

        for(int i=0; i<male.size(); i++){
            int zadanie = male[i].time;
            auto wybrana_maszyna = std::min_element(maszyny.begin(), maszyny.end());
            *wybrana_maszyna += zadanie;
        }

        int aktualny = *std::max_element(maszyny.begin(), maszyny.end());
        if(aktualny < best_c_max){
            best_c_max = aktualny;
            best_p = p;
        }
    } while(p.next_perm());

    std::cout << "Najmniejsze C_max dla algorytmu PTAS dla " << m << " maszyn: " << best_c_max << std::endl;

    return best_c_max;
}

int Problem::Algorytm_FPTAS2(const std::vector<Zadanie>& dane, int k){
    if(m!=2) return -1;
    if(k <= 0) k=1;

    std::vector<Zadanie> przeskalowane_dane = dane;

    for(int i=0; i<n; i++)
        przeskalowane_dane[i].time = przeskalowane_dane[i].time/k;

    auto rozwiazanie = this->Algorytm_PD2(przeskalowane_dane, false);
    Permutacja best_p = rozwiazanie.first;

    int best_c_max = this->kryterium(best_p, dane);

    std::cout << "Najmniejsze C_max dla algorytmu FPTAS dla 2 maszyn: " << best_c_max << std::endl;

    return best_c_max;    
}

int Problem::Algorytm_PD3(const std::vector<Zadanie>& dane){
    if(m!=3) return -1;

    int s = 0;
    for(auto it=dane.begin(); it!=dane.end(); ++it)
        s += it->time;

    std::vector<std::vector<std::vector<bool>>> B(n+1, std::vector<std::vector<bool>>(s+1, std::vector<bool>(s+1, false)));
    B[0][0][0] = true;

    for(int k=1; k<=n; k++){
        for(int t1=0; t1<=s; t1++){
            for(int t2=0; t2<=s; t2++){
                if(B[k-1][t1][t2] == true){
                    if(t1+dane[k-1].time <= s)
                        B[k][t1+dane[k-1].time][t2] = true;

                    if(t2+dane[k-1].time <= s)
                        B[k][t1][t2+dane[k-1].time] = true;

                    B[k][t1][t2] = true;
                }
            }
        }
    }

    int c_opt = s;

    for(int t1=0; t1<=s; t1++){
        for(int t2=0; t2<=s; t2++){
            if(B[n][t1][t2] == true){
                int t3 = s-(t1+t2);
                int current_max = std::max({t1, t2, t3});
                if(current_max < c_opt)
                    c_opt = current_max;
            }
        }
    }

    std::cout << "Najmniejsze C_max dla algorytmu programowania dynamicznego dla 3 maszyn: " << c_opt << std::endl;

    return c_opt;
}