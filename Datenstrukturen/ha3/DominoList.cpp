#include <stdio.h>
#include "include/DominoList.hpp"
#include "include/readInt.hpp"
#include "include/Domino.hpp"

void DominoList::addDomino(int n, int m)
{
    Domino *tmp = new Domino;
    tmp->a = m;
    tmp->b = n;
    tmp->next = 0;
    if (head) {  // einfügen an Listenende
        tail->next = tmp;
        tail = tail->next;
    } else {  // Liste leer, erstellen der Liste
        head = tmp;
        tail = head;
    }
}

DominoList::DominoList(char *filename)
{
    head = 0;
    tail = 0;
    FILE *fp = fopen(filename, "r");
    count = readInt(fp);
    for (int i = 0; i < count; i++) {
        addDomino(readInt(fp), readInt(fp));
    }
    fclose(fp);
}

DominoList::~DominoList()
{
    Domino *tmp;
    while (head) {
        tmp = head->next;
        delete head;
        head = tmp;
    }
}

void DominoList::printList()
{
    Domino *tmp = head;
    printf("Liste:\n");
    while (tmp != tail) {
        printf("[%d:%d]", tmp->a, tmp->b);
        tmp = tmp->next;
    }
    printf("[%d:%d]\n", tmp->a, tmp->b);
}

bool DominoList::isEmpty()
{
    if (head)
        return false;
    else
        return true;
}

void DominoList::removeDomino(int n, int m)
{
    Domino *tmp = head;
    Domino *del;
    if (head->a == n && head->b == m) {  // Löschen am Anfang
        tmp = head->next;
        delete head;
        head = tmp;
    } else if (tail->a == n && tail->b == m) { // Löschen am Ende
        while (tmp->next != tail)
            tmp = tmp->next;
        tmp->next = 0;  // = tail->next
        delete tail;
        tail = tmp;
    } else {  // Löschen in der Mitte
        while (tmp->next->a != n || tmp->next->b != m)
            tmp = tmp->next;
        del = tmp->next;
        tmp->next = del->next;
        delete del;
        del = 0;
    }
    count--;
}
