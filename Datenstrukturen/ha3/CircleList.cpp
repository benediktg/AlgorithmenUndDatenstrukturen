#include <stdio.h>
#include "include/Circle.hpp"
#include "include/CircleList.hpp"
#include "include/DominoList.hpp"

void CircleList::addCircle(DominoList *dominolist)
{
    Circle *tmp;
    tmp = new Circle(dominolist);
    if (head) {  // einfügen an Listenende
        tail->next = tmp;
        tail = tail->next;
    } else {  // Liste leer, erstellen der Liste
        head = tmp;
        tail = head;
        tail->next = 0;
    }
}

CircleList::CircleList(DominoList *dominolist)
{
    head = new Circle(dominolist);
    head->next = 0;
    tail = head;
    while (!(dominolist->isEmpty())) {
        addCircle(dominolist);
    }
}

CircleList::~CircleList()
{
    Circle *tmp;
    while (head) {
        tmp = head->next;
        delete head;
        head = tmp;
    }
}

void CircleList::printList()
{
    Circle *tmp = head;
    printf("Kreise:\n");
    while (tmp != tail) {
        tmp->printCircle();
        tmp = tmp->next;
    }
    tmp->printCircle();
}
