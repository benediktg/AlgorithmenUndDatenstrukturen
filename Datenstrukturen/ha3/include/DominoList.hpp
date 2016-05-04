#ifndef DOMINOLIST_H
#define DOMINOLIST_H

#include "Domino.hpp"

typedef FILE FILE;

struct DominoList {
    Domino *head;
    Domino *tail;
    int count;
    void addDomino(int n, int m);
public:
    DominoList(char *filename);
    ~DominoList();
    void printList();
    bool isEmpty();
    void removeDomino(int n, int m);
};

#endif
