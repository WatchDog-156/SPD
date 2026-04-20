#include "problem.h"
#include <algorithm>
#include <queue>

struct PorownajZadania{
    const std::vector<Zadanie>& dane;
    PorownajZadania(const std::vector<Zadanie>& d) : dane(d) {}

    bool operator()(int a, int b) const{
        return dane[a].dj > dane[b].dj;
    }
};

struct PorownajZadaniaRj {
    const std::vector<Zadanie>& dane;
    PorownajZadaniaRj(const std::vector<Zadanie>& d) : dane(d) {}

    bool operator()(int a, int b) const {
        return dane[a].rj > dane[b].rj;
    }
};

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

    std::cout << "Najlepsze L_max dla ERD: " << L << std::endl;
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

    std::cout << "Najlepsze L_max dla EDD: " << L << std::endl;
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

    std::cout << "Nalepsze L_max dla przeglądu zupełnego: " << best_l << std::endl;
    std::cout << "Permutacja dla przeglądu zupełnego: " << best_p << std::endl;

    return best_l;
}

int Problem::Algorytm_wlasny(const std::vector<Zadanie>& dane, double alpha){
    Permutacja p(n);
    std::vector<bool> czy_wykonane(n, false);
    int aktulany_czas = 0;
    // double alpha = 0.5;


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

    // std::cout << "Nalepsze L_max dla algorytmu wlasnego: " << L << std::endl;
    // std::cout << "Permutacja dla algorytmu własnego: " << p << std::endl;

    return L;
}



std::pair<int, Permutacja> Problem::Algorytm_Schrage(const std::vector<Zadanie>& dane, bool show){
    Permutacja p(n);
    int aktualny_czas = 0; 
    int wykonane_zadania = 0;

    PorownajZadaniaRj komparator_rj(dane);
    PorownajZadania komparator_dj(dane);

    std::priority_queue<int, std::vector<int>, PorownajZadaniaRj> N(komparator_rj);
    std::priority_queue<int, std::vector<int>, PorownajZadania> G(komparator_dj);

    for(int i = 0; i < n; i++){
        N.push(i);
    }

    while(!N.empty() || !G.empty()){
        while(!N.empty() && dane[N.top()].rj <= aktualny_czas){
            G.push(N.top());
            N.pop();
        }

        if(G.empty()){
            aktualny_czas = dane[N.top()].rj;
            continue; 
        }

        int najlepsze_zadanie = G.top();
        G.pop();

        p.perm[wykonane_zadania] = najlepsze_zadanie;
        aktualny_czas += dane[najlepsze_zadanie].pj;
        wykonane_zadania++;
    }
    int L = this->kryterium(p, dane);

    if(show){
        std::cout << "Nalepsze L_max dla algorytmu Schrage " << L << std::endl;
        std::cout << "Permutacja dla algorytmu Schrage: " << p << std::endl;
    }

    return {L, p};
}

int Problem::Algorytm_Schrage_z_podzialem(const std::vector<Zadanie> &dane, bool show){
    int aktualny_czas = 0;
    int L_max=-1e9;
    std::vector<int> permutacja;

    //zadania posortowane po rj
    std::vector<int> idx(n);
    for(int i=0; i<n; i++) idx[i]=i;

    std::sort(idx.begin(), idx.end(), [&](int a, int b){
        return dane[a].rj < dane[b].rj;
    }); 

    //Kolejka priorytetowa G
    std::priority_queue<int, std::vector<int>, PorownajZadania> G{PorownajZadania(dane)};

    std::vector<int> pozostale_pj(n);
    for(int i=0; i<n; i++) pozostale_pj[i] = dane[i].pj;

    int nastepne_idx=0;
    int obecne_zadanie=-1;

    while(!G.empty() || nastepne_idx < n ){
        while(nastepne_idx < n && dane[idx[nastepne_idx]].rj <= aktualny_czas){
            int nowe_zadanie = idx[nastepne_idx];
            G.push(nowe_zadanie);
            nastepne_idx++;
        }
        if(G.empty()){
            aktualny_czas = dane[idx[nastepne_idx]].rj;
            continue;
        }
        int najlepsze_zadanie = G.top();
        G.pop();
        if (najlepsze_zadanie != obecne_zadanie) {
            permutacja.push_back(najlepsze_zadanie);
            obecne_zadanie = najlepsze_zadanie;
        }

        //pobranie czasu do nastepnego rj (rj nastpnego czasu - aktualny czas), ew koniec.
        int czas_do_nastepnego_rj = (nastepne_idx < n) ? dane[idx[nastepne_idx]].rj - aktualny_czas : 1e9;
        int czas_wykonania = std::min(pozostale_pj[najlepsze_zadanie], czas_do_nastepnego_rj);

        aktualny_czas += czas_wykonania;
        pozostale_pj[najlepsze_zadanie] -= czas_wykonania;

        if(pozostale_pj[najlepsze_zadanie] == 0){
            L_max = std::max(L_max, aktualny_czas - dane[najlepsze_zadanie].dj);
            obecne_zadanie =-1;
        }else{
            G.push(najlepsze_zadanie);
        }
    }

    if(show){
        std::cout << "Najlepsze L_max dla algorytmu Schrage z przerwaniami: " << L_max << std::endl;
        std::cout << "Kolejność wykonywania zadań z przewaniami: ";
        for(int id : permutacja) std::cout << id << " ";
        std::cout << std::endl;
    }

    return L_max;
}

void Problem::Search_critical_block(Permutacja p, const std::vector<Zadanie>& dane, int critical_parameters[]){
    int Lmax = -999999;
    int time = 0;
    std::vector<int> end_time(this->n);

    // b
    for(int i=0; i<this->n; i++){
        int idx = p.perm[i];
        time = std::max(time, dane[idx].rj) + dane[idx].pj;
        end_time[i] = time;
        int L = time - dane[idx].dj;
        if(L >= Lmax){
            Lmax = L;
            critical_parameters[1] = i;
        }
    }

    // a
    critical_parameters[0] = critical_parameters[1]; 
    for(int i = critical_parameters[1]; i > 0; i--){
        if(end_time[i-1] < dane[p.perm[i]].rj){
            break; 
        }
        critical_parameters[0] = i - 1; 
    }

    // c
    critical_parameters[2] = -1;
    for(int i=critical_parameters[1]-1; i>=critical_parameters[0]; i--){
        if(dane[p.perm[i]].dj > dane[p.perm[critical_parameters[1]]].dj){
            critical_parameters[2] = i;
            break;
        }
    }
}

int Problem::Algorytm_BandB(std::vector<Zadanie>& dane){
    std::pair<int, Permutacja> wynik_schrage = this->Algorytm_Schrage(dane,false);
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
    if(this->Algorytm_Schrage_z_podzialem(dane,false) < this->UB){
        this->Algorytm_BandB(dane);
    }
    dane[idx_c].dj = old_dj;

    // prawa gałąź, c po bloku K
    int old_rj = dane[idx_c].rj;
    dane[idx_c].rj = std::max(dane[idx_c].rj, r_star + p_star);
    if(this->Algorytm_Schrage_z_podzialem(dane,false) < this->UB){
        this->Algorytm_BandB(dane);
    }
    dane[idx_c].rj = old_rj;

    return this->UB;
}

void Problem::Alpha_Analysis(const std::vector<Zadanie>& dane, int opt_L, int liczba_prob) {
    double min_blad = 1e12, max_blad = -1e12, suma_bledow = 0;
    double best_alpha = 0, worst_alpha = 0, blad_wzgledny = 0;

    std::cout << "\nAnaliza wplywu parametru alpha (liczba prob: " << liczba_prob << ")" << std::endl;

    for (int i = 0; i <= liczba_prob; i++) {
        double alpha = static_cast<double>(i) / liczba_prob;
        
        int L_wlasny = this->Algorytm_wlasny(dane, alpha);
        double blad = static_cast<double>(L_wlasny - opt_L);

        if (blad < min_blad) {
            min_blad = blad;
            best_alpha = alpha;
        }
        if (blad > max_blad) {
            max_blad = blad;
            worst_alpha = alpha;
        }
        suma_bledow += blad;
        if (opt_L != 0){
            blad_wzgledny = min_blad /abs(opt_L) *100;
        }
    }

    double sredni_blad = suma_bledow / (liczba_prob + 1);

    // Wypisanie sformatowanego podsumowania
    std::cout << "Analiza parametru alpha:" << std::endl;
    std::cout << "Najlepsza alpha: " << best_alpha << " (Blad: " << min_blad << ")" << std::endl;
    std::cout << "Najgorsza alpha: " << worst_alpha << " (Blad: " << max_blad << ")" << std::endl;
    std::cout << "Sredni blad:    " << sredni_blad << std::endl;
    std::cout << "Wzgledny blad minimalny (najlepszego przypadku): " << blad_wzgledny <<std::endl;
}