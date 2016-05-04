#include <stdio.h>
#include "../include/CharList.hpp"
#include "../include/hilfsfunktionen.hpp"

CharList::CharList()
{
    head = 0;
    tail = head;
}

CharList::CharList(const char *string)
{
    head = 0;
    tail = head;
    int len = length(string);
    CharList queue;
    LNode *node = 0;
    char *tmp = 0;
    int i = 0;

    while (string[i] == '(') {
        tmp = char2str(string[i]);
        enqu(tmp, 'a');
        delete [] tmp;
        ++i;
    }
    if (string[i] == '-') {
        /* Lookahead wegen möglichem negativem Vorzeichen */
        tmp = char2str(string[i]);
        queue.enqu(tmp, 0);
        delete [] tmp;
        ++i;
        if (string[i] >= 'a' && string[i] <= 'z') {
            /* Lookahead für Buchstabe */
            tmp = char2str(string[i]);
            queue.enqu(tmp, 0);
            delete [] tmp;
            ++i;
        } else {
            while (string[i] >= '0' && string[i] <= '9') {
                /* Lookahead für mehrstellige Zahl*/
                tmp = char2str(string[i]);
                queue.enqu(tmp, 0);
                delete [] tmp;
                ++i;
            }
        }
        queue.concatenate();
        node = queue.dequ();
        enqu(node->info, 'n');
        delete node;
    }

    while (i < len) {
        if (string[i] >= 'a' && string[i] <= 'z') {
            /* Buchstabe */
            tmp = char2str(string[i]);
            enqu(tmp, 'o');
            delete [] tmp;
            ++i;
        } else if (string[i] == '+' || string[i] == '-' || string[i] == '*') {
            /* Operator */
            tmp = char2str(string[i]);
            if (string[i] == '*')
                enqu(tmp, 'p');
            else
                enqu(tmp, 's');
            delete [] tmp;
            ++i;
            while (string[i] == '(') {
                tmp = char2str(string[i]);
                enqu(tmp, 'a');
                delete [] tmp;
                ++i;
            }
            if (string[i] == '-') {
                /* Lookahead wegen möglichem negativem Vorzeichen */
                tmp = char2str(string[i]);
                queue.enqu(tmp, 0);
                delete [] tmp;
                ++i;
                if (string[i] >= 'a' && string[i] <= 'z') {
                    /* Lookahead für Buchstabe */
                    tmp = char2str(string[i]);
                    queue.enqu(tmp, 0);
                    delete [] tmp;
                    ++i;
                } else {
                    while (string[i] >= '0' && string[i] <= '9') {
                        /* Lookahead für mehrstellige Zahl*/
                        tmp = char2str(string[i]);
                        queue.enqu(tmp, 0);
                        delete [] tmp;
                        ++i;
                    }
                }
                queue.concatenate();
                node = queue.dequ();
                enqu(node->info, 'n');
                delete node;
            }
        } else if (string[i] >= '0' && string[i] <= '9') {
            /* Zahl */
            while (string[i] >= '0' && string[i] <= '9') {
                /* Lookahead wegen mehrstelliger Zahl */
                tmp = char2str(string[i]);
                queue.enqu(tmp, 0);
                delete [] tmp;
                ++i;
            }
            queue.concatenate();
            node = queue.dequ();
            enqu(node->info, 'o');
            delete node;
        } else if (string[i] == ')') {
            tmp = char2str(string[i]);
            enqu(tmp, 'z');
            delete [] tmp;
            ++i;
        }
    }
}

CharList::~CharList()
{
    LNode *tmp = 0;
    while (head) {
        tmp = head->next;
        delete head;
        head = tmp;
    }
}

void CharList::enqu(const char *string, char c)
{
    LNode *tmp = new LNode(string, c);
    if (isEmpty())
        head = tmp;
    else
        tail->next = tmp;
    tail = tmp;
}

LNode *CharList::dequ()
{
    if (!isEmpty()) {
        LNode *result = new LNode(head->info, head->type);
        LNode *tmp = head->next;
        delete head;
        head = tmp;
        return result;
    } else {
        return 0;
    }
}

void CharList::push(const char *string, char c)
{
    enqu(string, c);
}

LNode *CharList::pop()
{
    if (!isEmpty()) {
        LNode *result = new LNode(tail->info, tail->type);
        if (head != tail) {
            LNode *tmp = head;
            while (tmp->next != tail)
                tmp = tmp->next;
            delete tail;
            tail = tmp;
        } else {
            delete tail;
            tail = 0;
            head = 0;
        }
        return result;
    } else {
        return 0;
    }
}

bool CharList::isEmpty()
{
    return (!head);
}

char CharList::getStackTopType()
{
    return (tail) ? tail->type : 0;
}

void CharList::concatenate()
{
    if (!head) {
        return;
    } else {
        LNode *tmp = 0;
        int i;
        char *string_new;
        while (head->next) {
            int len1 = length(head->info);
            int len2 = length(head->next->info);
            string_new = new char[len1 + len2 + 1];
            for (i = 0; i < len1; ++i) {
                string_new[i] = head->info[i];
            }
            for (i = len1; i < len1 + len2; ++i) {
                string_new[i] = head->next->info[i - len1];
            }
            string_new[i] = '\0';
            tmp = new LNode(string_new, 0);
            tmp->next = head->next->next;
            delete head->next;
            delete head;
            delete [] string_new;
            string_new = 0;
            head = tmp;
        }
        tail = head;
    }
}

CharList CharList::convert_to_postfix()
{
    CharList queue;
    CharList stack;

    /* Shunting-Yard-Algorithmus */
    LNode *tmp = 0;
    LNode *token = head;
    while (token) {
        if (token->type == 'o' || token->type == 'n') {
            queue.enqu(token->info, token->type);
        } else if (token->type == 'p') {
            stack.push(token->info, token->type);
        } else if (token->type == 's') {
            if (!stack.isEmpty())
                while (stack.getStackTopType() == 'p') {
                    tmp = stack.pop();
                    queue.enqu(tmp->info, tmp->type);
                    delete tmp;
                    tmp = 0;
                }
            stack.push(token->info, token->type);
        } else if (token->type == 'a') {
            stack.push(token->info, token->type);
        } else if (token->type == 'z') {
            while (stack.getStackTopType() != 'a') {
                tmp = stack.pop();
                queue.enqu(tmp->info, tmp->type);
                delete tmp;
                tmp = 0;
            }
            if (stack.getStackTopType() == 'a') {
                tmp = stack.pop();
                delete tmp;
                tmp = 0;
            }
        }
        token = token->next;
    }
    while (!stack.isEmpty()) {
        tmp = stack.pop();
        queue.enqu(tmp->info, tmp->type);
        delete tmp;
        tmp = 0;
    }

    return queue;
}

char *CharList::bracket()
{
    CharList postfix = this->convert_to_postfix();
    CharList stack;
    CharList queue;
    LNode *token = 0;
    LNode *tmp = 0;
    while (!postfix.isEmpty()) {
        token = postfix.dequ();
        if (token->type == 'o') {
            stack.push(token->info, token->type);
        } else if (token->type == 'n') {
            /* öffnende Klammer für negative Zahl*/
            queue.enqu("(", 'a');
            /* negative Zahl einfügen */
            queue.enqu(token->info, token->type);
            /* schließende Klammer */
            queue.enqu(")", 'z');
            /* queue verschmelzen und verbleibendes Element zum Stack */
            queue.concatenate();
            tmp = queue.dequ();
            stack.push(tmp->info, 0);
            delete tmp;
            tmp = 0;
        } else {
            /* Klammer einfügen */
            queue.enqu("(", 'a');
            /* 2. Operanden einfügen */
            tmp = stack.pop();
            queue.enqu(tmp->info, tmp->type);
            delete tmp;
            tmp = 0;
            /* Operator einfügen */
            queue.enqu(token->info, token->type);
            /* 1. Operanden einfügen */
            tmp = stack.pop();
            queue.enqu(tmp->info, tmp->type);
            delete tmp;
            tmp = 0;
            /* schließende Klammer */
            queue.enqu(")", 'z');
            /* 2. und 1. Op. vertauschen */
            queue.swap(1, 3);
            /* queue verschmelzen und verbleibendes Element zum Stack */
            queue.concatenate();
            tmp = queue.dequ();
            stack.push(tmp->info, 0);
            delete tmp;
            tmp = 0;
        }
        delete token;
    }
    token = 0;
    tmp = stack.pop();
    int len = length(tmp->info);
    char *result = new char[len + 1];
    int j;
    for (j = 0; j < len; ++j) {
        result[j] = tmp->info[j];
    }
    result[j] = '\0';
    delete tmp;
    tmp = 0;
    return result;
}

void CharList::print()
{
    LNode *tmp = head;
    while (tmp) {
        printf("%s ", tmp->info);
        tmp = tmp->next;
    }
    printf("\n");
}

void CharList::swap(int i, int j)
{
    LNode *elem1 = head;
    LNode *elem2 = head;
    for (int k = 0; k < i; ++k) {
        if (elem1->next)
            elem1 = elem1->next;
    }
    for (int k = 0; k < j; ++k) {
        if (elem2->next)
            elem2 = elem2->next;
    }
    char *tmp = elem1->info;
    elem1->info = elem2->info;
    elem2->info = tmp;
}

/*
 * LNode-Methoden
 */

LNode::LNode(const char *string, char c)
{
    type = c;
    int len = length(string);
    info = new char[len + 1];
    for (int i = 0; i < len; ++i)
        info[i] = string[i];
    info[len] = '\0';
    next = 0;
}

LNode::~LNode()
{
    delete [] info;
    info = 0;
}
