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

int Problem::Algorytm_wlasny(const std::vector<Zadanie>& dane){
    Permutacja p(n);
    std::vector<bool> czy_wykonane(n, false);
    int aktulany_czas = 0;
    double alpha = 0.9;


    for (int i=0; i<n; i++){
        int najlepsze_zadanie=-1;
        double min_priorytet=1e12;

        bool dostepne = false;
        for (int j=0; j<n; j++){
            if(!czy_wykonane[j] && dane[j].rj < aktulany_czas ){
                dostepne = true;

                double priorytet = alpha*dane[j].dj + (1-alpha)*dane[j].rj;
                if(priorytet < min_priorytet){
                    min_priorytet = priorytet;
                    najlepsze_zadanie = j;
                }
            }
        }
        if(!dostepne){
            double nastepny_rj = 1e12;
            for(int j=0; j<n; j++){
                if(!czy_wykonane[j] && dane[j].rj < nastepny_rj){
                    nastepny_rj = dane[j].rj;
                    najlepsze_zadanie = j;
                }
            }
            aktulany_czas = dane[najlepsze_zadanie].rj;
        }
        p.perm[i] = najlepsze_zadanie;
        czy_wykonane[najlepsze_zadanie] = true;
        aktulany_czas += dane[najlepsze_zadanie].pj;
    }

int L = this->kryterium(p, dane);

std::cout << "Nalepsze L_max dla algorytmu wlasnego: " << L << std::endl;
std::cout << "Permutacja: " << p << std::endl;

    return L;




}

// int Problem::Algorytm_BandB(const std::vector<Zadanie>& dane){
//     Permutacja p(n);
//     for(int i=0; i<n; i++) p.perm[i]=i;

//     Permutacja best_p = p;

//     int LB=this->Algorytm_Schrage_z_podzialem(dane);
//     int UB=this->Algorytm_Schrage(dane);



//     int B=this->Algorytm_Schrage(dane);
//     if(B<UB){
//         UB = B;
//         best_p = p;
//     }

// }