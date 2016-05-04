#ifndef CIRCLELIST_H
#define CIRCLELIST_H

#include "Circle.hpp"
#include "DominoList.hpp"

struct CircleList {
    Circle *head;
    Circle *tail;
    void addCircle(DominoList *dominolist);
public:
    CircleList(DominoList *dominolist);
    ~CircleList();
    void printList();
};

#endif
