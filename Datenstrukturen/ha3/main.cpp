#include <stdio.h>
#include "include/DominoList.hpp"
#include "include/CircleList.hpp"

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("genau ein Argument angeben\n");
        return 0;
    }
    char *dominofile = argv[1];
    DominoList *dominolist;
    dominolist = new DominoList(dominofile);
    dominolist->printList();

    CircleList *circlelist;
    circlelist = new CircleList(dominolist);
    circlelist->printList();

    delete dominolist;
    dominolist = 0;
    delete circlelist;
    circlelist = 0;
    return 0;
}
