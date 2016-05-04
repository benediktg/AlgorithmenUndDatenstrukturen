#include <stdio.h>
#include "../include/ExprTree.hpp"
#include "../include/CharList.hpp"
#include "../include/hilfsfunktionen.hpp"

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Bitte genau ein Argument angeben\n");
        return 0;
    }
    printf("Eingabe: %s\n\n", argv[1]);
    CharList expr(argv[1]);

    char *parenthesized = expr.bracket();
    printf("Ausgabe des geklammerten dyadischen Ausdrucks:\n"
           "%s\n\n", parenthesized);

    ExprTree tree(parenthesized);
    delete [] parenthesized;
    parenthesized = 0;

    printf("Ausgabe der Postorder-Traversierung des Baumes:\n");
    tree.postTraverse();

    printf("Vereinfache den Baum...\n\n");
    tree.simplify();

    printf("Ausgabe der Präorder-Traversierung des optimierten Baumes:\n");
    tree.preTraverse();

    printf("Ausgabe der geklammerten Inorder-Traversierung des optimierten Baumes:\n");
    tree.print();
    return 0;
}
