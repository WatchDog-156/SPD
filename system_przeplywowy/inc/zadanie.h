#ifndef ZADANIA_H
#define ZADANIA_H

class Zadanie {
public:
    int rj; //termin dostepnosci
    int pj; //czas wykonania
    int dj; //porzadany termin zakonczenia    

    Zadanie(int r, int p, int d) : rj(r), pj(p), dj(d) {}
    void wyswietl() const;
};

#endif