#ifndef CIRCLE_H
#define CIRCLE_H

#include "Domino.hpp"
#include "DominoList.hpp"

struct Circle {
    Domino *head;
    Domino *tail;
    Circle *next;
    void addDomino(int n, int m);
    Circle(DominoList *dominolist);
    ~Circle();
    void printCircle();
};

#endif
