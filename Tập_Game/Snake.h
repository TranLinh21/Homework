#ifndef SNAKE_H
#define SNAKE_H
#include "box.h"
#include "SDL2.h"


struct Node
{
    Box node;
    Node* next;
    Node(Box _node, Node* _n): node(_node), next(_n) {}
};


#endif // SNAKE_H
