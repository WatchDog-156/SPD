#include "problem.h"
#include <algorithm>
#include <queue> 
#include <cmath>

int Problem::kryterium(Permutacja p, const std::vector<Zadanie>& dane){
    int size = p.perm.size();
    if(size==0) return 0;

    std::vector<int> czasy_zadan(size, 0);

    for(int i=0; i<m; i++){
        for(int j=0; j<size; j++){
            int idx = p.perm[j];

            if(j==0)
                czasy_zadan[j] = czasy_zadan[j] + dane[idx].times[i];
            else
                czasy_zadan[j] = std::max(czasy_zadan[j], czasy_zadan[j-1]) + dane[idx].times[i];
        }
    }

    return czasy_zadan[size-1];
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

int Problem::Algorytm_NEH(const std::vector<Zadanie>& dane, bool show){
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

    if(show){
        std::cout << "Najmniejsze C_max dla algorytmu NEH: " << best_c_max << std::endl;
        std::cout << "Permutacja dla algorytmu NEH: " << p << std::endl;
    }

    return best_c_max;
}

int Problem::Oblicz_LB(Node dziecko, const std::vector<Zadanie>& dane){
    int size = dziecko.perm.perm.size();
    std::vector<int> C(m, 0); 
    std::vector<int> czasy_zadan(size, 0);

    for (int k = 0; k < m; k++) {
        for (int j = 0; j < size; j++) {
            int idx = dziecko.perm.perm[j];
            if (j == 0)
                czasy_zadan[j] = czasy_zadan[j] + dane[idx].times[k];
            else
                czasy_zadan[j] = std::max(czasy_zadan[j], czasy_zadan[j-1]) + dane[idx].times[k];
        }
        C[k] = czasy_zadan[size - 1]; 
    }

    int max_LB = 0;
    for (int k = 0; k < m; k++) {
        int suma_niezapl_k = 0;
        int min_ogon;

        if(dziecko.pozostale.empty())
            min_ogon = 0;
        else 
            min_ogon = 9999999;

        for (int u : dziecko.pozostale) {
            suma_niezapl_k += dane[u].times[k];

            int ogon = 0;
            for (int q =k+1; q<m; q++) 
                ogon += dane[u].times[q];
            if (ogon < min_ogon)
                min_ogon = ogon;
        }
    
        int LB_k = C[k] + suma_niezapl_k + min_ogon;
        if (LB_k > max_LB) {
            max_LB = LB_k;
        }
    }

    return max_LB;
}

int Problem::Algorytm_BandB(std::vector<Zadanie>& dane){
    int UB = Algorytm_NEH(dane,false);
    Permutacja best_p(n);

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> kolejka;

    Node korzen;
    for(int i=0; i<n; i++) korzen.pozostale.push_back(i);
    korzen.LB = 0;
    kolejka.push(korzen);

    while(!kolejka.empty()){
        Node obecny = kolejka.top();
        kolejka.pop();

        for(int i=0; i<obecny.pozostale.size(); i++){            
            Node dziecko = obecny;
            dziecko.perm.perm.push_back(obecny.pozostale[i]);
            dziecko.pozostale.erase(dziecko.pozostale.begin() + i);

            dziecko.LB = Oblicz_LB(dziecko, dane);

            if(dziecko.LB < UB){
                if(dziecko.pozostale.size()==0){
                    UB = dziecko.LB;
                    best_p = dziecko.perm;
                } else
                    kolejka.push(dziecko);
            }
        }
    }

    std::cout << "Najmniejsze C_max dla algorytmu Branch and Bound: " << UB << std::endl;
    std::cout << "Permutacja dla algorytmu Branch and Bound: " << best_p << std::endl;          // jeżli permutacja to same 0, to najlepsza permutacja 
                                                                                                // została znaleziona za pomocą algorytmu NEH
    return UB;
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

        T=T*0.99;
        k++;
    }

    std::cout << "Najmniejsze C_max dla algorytmu akceptacji progu: " << best_c_max << std::endl;
    std::cout << "Permutacja dla algorytmu akceptacji progu: " << best_p << std::endl;

    return best_c_max;
}