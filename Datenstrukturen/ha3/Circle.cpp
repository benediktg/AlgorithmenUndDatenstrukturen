#include <stdio.h>
#include "include/Circle.hpp"
#include "include/DominoList.hpp"
#include "include/Domino.hpp"

void Circle::addDomino(int n, int m)
{
    Domino *tmp = new Domino;
    tmp->a = n;
    tmp->b = m;
    tmp->next = head;
    tail->next = tmp;
    tail = tmp;
}

Circle::Circle(DominoList *dominolist)
{
    Domino *tmp = dominolist->head;
    Domino *rd = new Domino;
    rd->a = tmp->a;
    rd->b = tmp->b;
    rd->next = head;
    head = rd;
    tail = head;
    tmp = tmp->next;
    dominolist->removeDomino(dominolist->head->a, dominolist->head->b);
    /* Kreis noch nicht komplett */
    while (!(head->a == tail->b)) {
        rd = tmp;
        tmp = tmp->next;
        if (rd->a == tail->b) {  // betrachtetes Teil passt ohne Drehen
            addDomino(rd->a, rd->b);
            dominolist->removeDomino(rd->a, rd->b);
        } else if (rd->b == tail->b) {  // passt mit Drehen
            addDomino(rd->b, rd->a);
            dominolist->removeDomino(rd->a, rd->b);
        }
        if (tmp == 0)
            tmp = dominolist->head;
    }
}

Circle::~Circle()
{
    Domino *tmp;
    while (head->next != head) {
        tmp = head->next;
        tail->next = tmp;
        delete head;
        head = tmp;
    }
    delete head;
    head = 0;
}

void Circle::printCircle()
{
    Domino *tmp = head;
    do {
        printf("[%d:%d]", tmp->a, tmp->b);
        tmp = tmp->next;
    } while (tmp != head);
    printf("\n");
}

