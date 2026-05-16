#ifndef ZADANIA_H
#define ZADANIA_H

class Zadanie {
public:
    int time;   

    Zadanie(int t) : time(t) {}
    void wyswietl() const;
};

#endif