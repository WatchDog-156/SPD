class Zadanie {
public:
    int pj; //czas wykonania
    int cj; //czas zakonczenia zadania
    int dj; //porzadany termin zakonczenia
    int lj; //lj = cj - dj nieterminowosc
    int rj; //czas dostepnosci

    Zadanie(int r, int p, int d) : rj(r), pj(p), dj(d) {}
    void wyswietl() const;
};