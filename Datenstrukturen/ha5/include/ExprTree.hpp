#ifndef EXPRTREE_H
#define EXPRTREE_H

#include "CharList.hpp"

struct TNode {
    char *info;
    /* gibt an, wie viele Nachfolger noch besetzt werden */
    int freePlace;
    bool isOperator;
    TNode *left;
    TNode *right;
    TNode(const char *string, int count);
    ~TNode();
    bool isNumber();
    bool isNumber(int value);
};

class ExprTree
{
public:
    ExprTree(const char *expr);
    ~ExprTree();
    bool isEmpty();
    void simplify();
    void preTraverse();
    void postTraverse();
    void print();

private:
    TNode *root;
    void insertAtFarrightestPos(TNode *root, char *info, int count);
    int updateCounts(TNode *root);
    TNode *simplifyRec(TNode *root);
    void preTraverseRec(TNode *root);
    void postTraverseRec(TNode *root);
    void printRec(TNode *root);
};

#endif
