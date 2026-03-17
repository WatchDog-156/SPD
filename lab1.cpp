#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>


class Zadanie {
public:
    int pj; //czas wykonania
    int cj; //czas zakonczenia zadania
    int dj; //porzadany termin zakonczenia
    int lj; //lj = cj - dj nieterminowosc
    int rj; //czas dostepnosci

    Zadanie(int r, int p, int d) : rj(r), pj(p), dj(d) {}
    void wyswietl() const {
        std::cout << rj <<"- Czas dostepnosci " <<
                     pj <<"- Czas wykoania " << 
                     dj <<"- Porzadany termin zakonczenia "<< std::endl;
    }
};





int main() {

    std::vector<Zadanie> Zadania;
    std::ifstream plik("dane.txt");

    if (!plik.is_open()) {
        std::cerr << "Nie mozna otworzyc pliku!" << std::endl;
        return 1;
    }

    int rj;
    int pj;
    int dj;

    std::string linia;
   
    while (std::getline(plik, linia)) {
        std::istringstream iss(linia);
        

        if (iss >> rj >> pj >> dj) {
          
            Zadania.emplace_back(rj, pj, dj);
        }
    }

    plik.close();
    std::sort(Zadania.begin(), Zadania.end(), [](int a, int b)
                                  {
                                      return a > b;
                                  });
   
   for (const auto& s : Zadania) {
        s.wyswietl();
    }
    return 0;
}
