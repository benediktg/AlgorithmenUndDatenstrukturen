#ifndef CHARLIST_H
#define CHARLIST_H

struct LNode {
    char *info;
    char type;
    /* Typen:
     * o: Operand
     * n: negativer Operand
     * p: Punktrechnungsoperator: *
     * s: Strichrechnungsoperator: +, -
     * a: Klammer auf
     * z: Klammer zu
     * 0: unbestimmt
     */
    LNode *next;
    LNode(const char *string, char c);
    ~LNode();
};

class CharList
{
public:
    CharList();
    CharList(const char *string);
    ~CharList();
    /* enqueue */
    void enqu(const char *string, char c);
    /* dequeue */
    LNode *dequ();
    void push(const char *string, char c);
    LNode *pop();
    char getStackTopType();
    bool isEmpty();
    CharList convert_to_postfix();
    char *bracket();
    void print();
    void concatenate();

private:
    LNode *head;
    LNode *tail;
    void swap(int i, int j);
};

#endif
