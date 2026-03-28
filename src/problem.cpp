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
    double alpha = 0.5;


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

std::pair<int, Permutacja> Problem::Algorytm_Schrage(const std::vector<Zadanie>& dane){
    Permutacja p(n);
    std::vector<bool> czy_wykonane(n, false);
    int aktulany_czas = 0;

    for(int i=0; i<n; i++){
        int najlepsze_zadanie = -1;
        double min_dj = 1e12;


        bool dostepne = false;
        for(int j=0; j<n; j++){
            if(!czy_wykonane[j] && dane[j].rj < aktulany_czas){
                dostepne = true;

                if(dane[j].dj < min_dj){
                    min_dj = dane[j].dj;
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

    std::cout << "Nalepsze L_max dla algorytmu Schrage " << L << std::endl;
    std::cout << "Permutacja: " << p << std::endl;

    return {L, p};
}

void Problem::Search_critical_block(Permutacja p, const std::vector<Zadanie>& dane, int critical_parameters[]){
    int Lmax = -999999;
    int time = 0;
    std::vector<int> end_time(this->n);

    // b
    for(int i=0; i<this->n; i++){
        int idx = p.perm[i];
        time = std::max(time, dane[idx].rj + dane[idx].pj);
        end_time[i] = time;
        int L = time - dane[idx].dj;
        if(L >= Lmax){
            Lmax = L;
            critical_parameters[1] = i;
        }
    }

    // a
    critical_parameters[0] = critical_parameters[1];
    int suma_p = 0;
    for(int i = critical_parameters[1]; i>=0; i--){
        suma_p += dane[p.perm[i]].pj;
        int time_before = 0;
        if(i==0){
            time_before = dane[p.perm[i]].rj;
        } else{
            time_before = end_time[i-1];
        }
        if(end_time[critical_parameters[1]] - time_before == suma_p){
            critical_parameters[0] = i;
        }
    }

    // c
    critical_parameters[2] = -1;
    for(int i=critical_parameters[1]-1; i>=critical_parameters[0]; i--){
        if(dane[p.perm[i]].dj > dane[p.perm[critical_parameters[1]]].dj){
            critical_parameters[3] = i;
            break;
        }
    }
}

int Problem::Algorytm_BandB(std::vector<Zadanie>& dane){
    std::pair<int, Permutacja> wynik_schrage = this->Algorytm_Schrage(dane);
    int current_Lmax = wynik_schrage.first;
    Permutacja current_perm = wynik_schrage.second;

    if(current_Lmax < this->UB){
        this->UB = current_Lmax;
        this->best_p = current_perm;
    }

    int critical_parameters[3] = {-1,-1,-1};                                    // a = 0, b = 1, c = 2
    this->Search_critical_block(current_perm, dane, critical_parameters);

    // zadanie jest optymalne w tej gałęzi
    if(critical_parameters[2]==-1){
        return this->UB;
    }

    // parametry dla bloku K
    int r_star = 999999;
    int p_star = 0;
    int d_star = -999999;
    for(int i=critical_parameters[2]+1; i<=critical_parameters[1]; i++){
        int idx = current_perm.perm[i];
        r_star = std::min(r_star, dane[idx].rj);
        d_star = std::max(d_star, dane[idx].dj);
        p_star += dane[idx].pj;
    }

    int idx_c = current_perm.perm[critical_parameters[2]];

    // lewa gałąź, c przed blokiem K
    int old_dj = dane[idx_c].dj;
    dane[idx_c].dj = std::min(dane[idx_c].dj, d_star - p_star);
    if(this->Algorytm_Schrage_z_podzialem(dane) < this->UB){
        this->Algorytm_BandB(dane);
    }
    dane[idx_c].dj = old_dj;

    // prawa gałąź, c po bloku K
    int old_rj = dane[idx_c].rj;
    dane[idx_c].rj = std::max(dane[idx_c].rj, r_star + p_star);
    if(this->Algorytm_Schrage_z_podzialem(dane) < this->UB){
        this->Algorytm_BandB(dane);
    }
    dane[idx_c].rj = old_rj;

    return this->UB;
}