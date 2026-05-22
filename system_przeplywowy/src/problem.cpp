#include "problem.h"
#include <algorithm>
#include <queue> 
#include <cmath>
#include <stdlib.h>

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

int Problem::Algorytm_Johnsona(const std::vector<Zadanie>& dane){
    std::vector<std::pair<int, int>> J_L;
    std::vector<std::pair<int, int>> J_R;

    for (int i=0; i<n; i++){
        if(dane[i].times[0]<dane[i].times[1]){
            J_L.push_back({i, dane[i].times[0]});
        }else{
            J_R.push_back({i, dane[i].times[1]});
        }
    }

    std::sort(J_L.begin(), J_L.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second <= b.second; 
    });

    std::sort(J_R.begin(), J_R.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second >= b.second; 
    });

    Permutacja p(n);
    size_t licznik = 0;
    p.perm.reserve(n);
    for(size_t i=0 ;i<J_L.size(); i++){
        p.perm[licznik]=J_L[i].first;
        licznik++;
    }
    for(size_t i=0 ;i<J_R.size(); i++){
        p.perm[licznik]=J_R[i].first;
        licznik++;
    }

    int best_c_max = kryterium(p, dane);

    std::cout << "Najmniejsze C_max dla algorytmu Johnsona: " << best_c_max << std::endl;
    std::cout << "Permutacja dla algorytmu Jonsona: " << p << std::endl;

    return best_c_max;
}

int Problem::Algorytm_FNEH(const std::vector<Zadanie> &dane)
{
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

    Permutacja p;
    int zadanie1 = sumy_zadan[0].first;
    int zadanie2 = sumy_zadan[1].first;

    Permutacja kombinacja1; kombinacja1.perm = {zadanie1, zadanie2};
    Permutacja kombinacja2; kombinacja2.perm = {zadanie2, zadanie1};


    if(kryterium(kombinacja1, dane) <= kryterium(kombinacja2, dane)){
        p=kombinacja1;
    }else{
        p=kombinacja2;
    }

    for(int k=2; k<n; k++){
        int nowe_zadanie=sumy_zadan[k].first;

        std::vector<std::vector<int>> F=Oblicz_Forward(p.perm, dane, m);
        std::vector<std::vector<int>> B=Oblicz_Backward(p.perm, dane, m);

        int best_c_max = 9999999;
        int best_pos = -1;

        for (int i=0; i<=k; i++){
            int c_max = Oblicz_Makespan_Wstawiania(F, B, dane, nowe_zadanie, i, m);

            if(c_max < best_c_max){
                best_c_max = c_max;
                best_pos=i;
            }
        }
    p.perm.insert(p.perm.begin() + best_pos, nowe_zadanie);
    }
    int best_c_max=kryterium(p, dane);

    std::cout << "Najmniejsze C_max dla algorytmu FNEH: " << best_c_max << std::endl;
    std::cout << "Permutacja dla algorytmu FNEH: " << p << std::endl;

    return best_c_max;
}

std::vector<std::vector<int>> Problem::Oblicz_Forward(const std::vector<int> &sekwencja, const std::vector<Zadanie> &dane, int m)
{
    int r=sekwencja.size();
    std::vector<std::vector<int>> F(r+1, std::vector<int>(m+1, 0));

    for(int i=1; i<=r; i++){
        int zadanie = sekwencja[i-1];

        for(int j=1; j<=m; j++){
            F[i][j] = std::max(F[i-1][j], F[i][j-1])+dane[zadanie].times[j-1];
        }
    }
    return F;
}

std::vector<std::vector<int>> Problem::Oblicz_Backward(const std::vector<int> &sekwencja, const std::vector<Zadanie> &dane, int m)
{
    int r=sekwencja.size();
    std::vector<std::vector<int>> B(r+2, std::vector<int>(m+2, 0));

    for(int i=r; i>=1; i--){
        int zadanie = sekwencja[i-1];

        for(int j=m; j>=1; j--){
            B[i][j] = std::max(B[i+1][j], B[i][j+1])+dane[zadanie].times[j-1];
        }
    }
    return B;
}

int Problem::Oblicz_Makespan_Wstawiania(std::vector<std::vector<int>> &F, std::vector<std::vector<int>> &B, const std::vector<Zadanie> &dane, int nowe_zadanie, int i, int m)
{
    std::vector<int> f_temp(m+1, 0);

    for (int j=1; j<=m; j++){
        f_temp[j] = std::max(f_temp[j-1], F[i][j]) + dane[nowe_zadanie].times[j-1];
    }

    int c_max = 0;
    for(int j=1; j<=m; j++){
        int tmp_c = f_temp[j] + B[i+1][j];
        if (tmp_c > c_max){
            c_max = tmp_c;
        }
    }
    return c_max;
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

int Problem::Algorytm_VNS(const std::vector<Zadanie> &dane, int k_max, int max_iteracji)
{
    Permutacja p(n);
    for(int i=0; i<n; i++) p.perm[i]=i;

    int best_c_max=kryterium(p, dane);
    Permutacja best_p = p;

    int iteracja = 0;
    while(iteracja<max_iteracji){
        int k=1;
        while(k<=k_max){
            Permutacja p_first=Shaking(p, k);
            Permutacja p_second=Przeszukanie_lokalne(p_first, dane);
            int c_max_kandydant = kryterium(p_second, dane);

            if(c_max_kandydant<best_c_max){
                p=p_second;
                best_p=p_second;
                best_c_max=c_max_kandydant;
                k=1;
            }else{
                k++;
            }
        }
        iteracja++;
    }
    std::cout << "Najmniejsze C_max dla algorytmu VNS: " << best_c_max << std::endl;
    std::cout << "Permutacja dla algorytmu VNS: " << best_p << std::endl;

    return best_c_max;
}

Permutacja Problem::Shaking(const Permutacja &p, int k)
{
    Permutacja wynik = p;

    if(k==1){
        int idx1=rand()%n;
        int idx2=rand()%n;
        std::swap(wynik.perm[idx1], wynik.perm[idx2]);
    }
    else if(k==2){
        int od_pozycji=rand()%n;
        int do_pozycji=rand()%n;
        int zadanie=wynik.perm[od_pozycji];
        wynik.perm.erase(wynik.perm.begin()+od_pozycji);
        wynik.perm.insert(wynik.perm.begin()+do_pozycji, zadanie);
    }
    else if(k==3){
        int idx1=rand()%n;
        int idx2=rand()%n;
        if(idx1>idx2) std::swap(idx1, idx2);
        std::reverse(wynik.perm.begin()+idx1, wynik.perm.begin()+idx2+1);
    }

    return wynik;
}

Permutacja Problem::Przeszukanie_lokalne(const Permutacja &p, const std::vector<Zadanie> &dane)
{
    Permutacja current_p=p;
    bool poprawiono=true;
    int current_c_max=kryterium(current_p, dane);

    while(poprawiono){
        poprawiono=false;

        for(int i=0;i<n-1;i++){
            for(int j=i+1; j<n; j++){
                Permutacja kandydant = current_p;
                std::swap(kandydant.perm[i], kandydant.perm[j]);
                int kandydant_c_max=kryterium(kandydant, dane);

                if(kandydant_c_max<current_c_max){
                    current_p=kandydant;
                    current_c_max=kandydant_c_max;
                    poprawiono=true;
                    break;
                }
            }
            if(poprawiono) break;;
        }
    }
    return current_p;
}
