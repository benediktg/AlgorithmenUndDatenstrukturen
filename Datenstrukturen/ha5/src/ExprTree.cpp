#include <stdio.h>
#include "../include/ExprTree.hpp"
#include "../include/hilfsfunktionen.hpp"

ExprTree::ExprTree(const char *expr)
{
    CharList tokens1(expr);
    CharList tokens2 = tokens1.convert_to_postfix();

    /* tokens2 wird nun als Stapel betrachtet */
    LNode *token = tokens2.pop();
    TNode *tmp = new TNode(token->info, 2);
    root = tmp;

    int count;

    while (!tokens2.isEmpty()) {
        delete token;
        token = tokens2.pop();
        count = (token->type == 'p' || token->type == 's') ? 2 : 0;
        insertAtFarrightestPos(root, token->info, count);
        updateCounts(root);

    }
    delete token;
}

ExprTree::~ExprTree()
{
    delete root;
    root = 0;
}

void ExprTree::simplify()
{
    simplifyRec(root);
}

void ExprTree::postTraverse()
{
    postTraverseRec(root);
    printf("\n\n");
}

void ExprTree::preTraverse()
{
    preTraverseRec(root);
    printf("\n\n");
}

void ExprTree::print()
{
    printRec(root);
    printf("\n\n");
}

bool ExprTree::isEmpty()
{
    return (!root);
}

/* private Methoden */

void ExprTree::insertAtFarrightestPos(TNode *root, char *info, int count)
{
    if (root->freePlace == 2 && !root->right) {
        TNode *tmp = new TNode(info, count);
        root->right = tmp;
    } else if (root->freePlace == 1 && !root->left) {
        TNode *tmp = new TNode(info, count);
        root->left = tmp;
    } else if (root->freePlace >= 2 && root->right->freePlace) {
        insertAtFarrightestPos(root->right, info, count);
    } else {
        insertAtFarrightestPos(root->left, info, count);
    }
}

int ExprTree::updateCounts(TNode *root)
{
    if (root && !root->isOperator) {
        root->freePlace = 0;
    } else if (root && root->isOperator && !root->left && root->right && !root->right->isOperator) {
        root->freePlace = 1;
    } else if (root && root->isOperator && !root->left && !root->right) {
        root->freePlace = 2;
    } else {
        int l = (root->left) ? updateCounts(root->left) : 1;
        int r = (root->right) ? updateCounts(root->right) : 1;
        root->freePlace = l + r;
    }
    return root->freePlace;
}

TNode *ExprTree::simplifyRec(TNode *root)
{
    int number;
    char *string = 0;
    bool optimized = !(  // entspricht quasi dem "else" ganz unten
                         (root->left->isNumber() && root->right->isNumber())
                         || ((root->right->isNumber(0) || root->left->isNumber(0)) && root->info[0] == '*')
                         || (root->right->isNumber(0) && (root->info[0] == '+' || root->info[0] == '-'))
                         || ((root->right->isNumber(1) || root->left->isNumber(1)) && root->info[0] == '*')
                         || (root->left->isNumber(0) && (root->info[0] == '-' || root->info[0] == '+'))
                         || ((root->left->isNumber(-1) || root->right->isNumber(-1)) && root->info[0] == '*')
                         || (root->info[0] == '-' && isEqual(root->left->info, root->right->info))
                     );

    if (optimized) {
        if (root->left->isOperator)
            root->left = simplifyRec(root->left);
        if (root->right->isOperator)
            root->right = simplifyRec(root->right);
    } else if (root->left->isNumber() && root->right->isNumber()) {  // direkte numerische Berechnung
        if (root->info[0] == '+')
            number = str2int(root->left->info) + str2int(root->right->info);
        else if (root->info[0] == '-')
            number = str2int(root->left->info) - str2int(root->right->info);
        else if (root->info[0] == '*')
            number = str2int(root->left->info) * str2int(root->right->info);
        delete root->left;
        root->left = 0;
        delete root->right;
        root->right = 0;
        string = int2str(number);
        delete [] root->info;
        root->info = string;
        root->isOperator = false;
        return root;
    } else if ((root->right->isNumber(0) || root->left->isNumber(0)) && root->info[0] == '*') {  // X*0=0, 0*X=0
        delete root->left;
        root->left = 0;
        delete root->right;
        root->right = 0;
        delete [] root->info;
        root->info = int2str(0);
        root->isOperator = false;
        return root;
    } else if ((root->right->isNumber(0) && (root->info[0] == '+' || root->info[0] == '-'))
               || (root->right->isNumber(1) && root->info[0] == '*')) {  // X+0=X, X-0=X, X*1=X
        delete root->right;
        root->right = 0;
        delete [] root->info;
        root->info = 0;
        root = root->left;
        return root;
    } else if ((root->left->isNumber(0) && root->info[0] == '-')
               || (root->left->isNumber(-1) && root->info[0] == '*')) {  // 0-X=-X, (-1)*X=-X
        string = negateReprStr(root->right->info);
        delete root->left;
        root->left = 0;
        delete [] root->info;
        root->info = 0;
        delete [] root->right->info;
        root->right->info = string;
        root = root->right;
        return root;
    } else if ((root->left->isNumber(1) && root->info[0] == '*')
               || (root->left->isNumber(0) && root->info[0] == '+')) {  // 1*X=X, 0+X=X
        delete root->left;
        root->left = 0;
        delete [] root->info;
        root->info = 0;
        root = root->right;
        return root;
    } else if (root->right->isNumber(-1) && root->info[0] == '*') {  // X*(-1)=-X
        string = negateReprStr(root->left->info);
        delete root->right;
        root->right = 0;
        delete [] root->info;
        root->info = 0;
        delete [] root->left->info;
        root->left->info = string;
        root = root->left;
        return root;
    } else if (root->info[0] == '-' && isEqual(root->left->info, root->right->info)) {  // X-X=0
        delete root->left;
        root->left = 0;
        delete root->right;
        root->right = 0;
        delete [] root->info;
        root->info = int2str(0);
        root->isOperator = false;
        return root;
    } else if (root->info[0] == '+' && root->left->isOperator && root->right->isOperator) {
        string = negateReprStr(root->left->info);
        if (isEqual(string, root->right->info)) {  // X+(-X)=0
            delete [] string;
            string = 0;
            delete root->left;
            root->left = 0;
            delete root->right;
            root->right = 0;
            delete [] root->info;
            root->info = int2str(0);
            root->isOperator = false;
            return root;
        } else {
            delete [] string;
            string = negateReprStr(root->right->info);
            if (isEqual(string, root->left->info)) {  // (-X)+X=0
                delete [] string;
                string = 0;
                delete root->left;
                root->left = 0;
                delete root->right;
                root->right = 0;
                delete [] root->info;
                root->info = int2str(0);
                root->isOperator = false;
                return root;
            } else {
                delete [] string;
                string = 0;
            }
        }
    }
    if (root->left->isOperator)
        root->left = simplifyRec(root->left);
    if (root->right->isOperator)
        root->right = simplifyRec(root->right);
    return root;
}

void ExprTree::postTraverseRec(TNode *root)
{
    if (!root->left && !root->right) {
        printf("%s ", root->info);
    } else {
        postTraverseRec(root->left);
        postTraverseRec(root->right);
        printf("%s ", root->info);
    }
}

void ExprTree::preTraverseRec(TNode *root)
{
    if (!root->left && !root->right) {
        printf("%s ", root->info);
    } else {
        printf("%s ", root->info);
        postTraverseRec(root->left);
        postTraverseRec(root->right);
    }
}

void ExprTree::printRec(TNode *root)
{
    if (!root->left && !root->right) {
        if (root->info[0] == '-') {
            printf("(%s)", root->info);
        } else {
            printf("%s", root->info);
        }
    } else {
        printf("(");
        printRec(root->left);
        printf("%s", root->info);
        printRec(root->right);
        printf(")");
    }
}

/*
 * TNode-Methoden
 */

TNode::TNode(const char *string, int count)
{
    freePlace = count;
    isOperator = (count);
    int len = length(string);
    info = new char[len + 1];
    for (int i = 0; i < len; ++i)
        info[i] = string[i];
    info[len] = '\0';
    left = 0;
    right = 0;
}

TNode::~TNode()
{
    delete left;
    left = 0;
    delete right;
    right = 0;
    delete [] info;
    info = 0;
}

bool TNode::isNumber()
{
    int i = 0;
    if (info[i] == '-')
        ++i;
    return (info[i] >= '0' && info[i] <= '9');
}

bool TNode::isNumber(int value)
{
    if (!isNumber())
        return false;
    int number = str2int(info);
    return (number == value);
}


