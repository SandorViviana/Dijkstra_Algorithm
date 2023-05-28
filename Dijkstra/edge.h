#ifndef EDGE_H
#define EDGE_H

#include "node.h"
class Edge
{
private:
    Node* firstNode;
    Node* lastNode;
    int lenght;
public:
    Edge();
    Edge(Node* firstNode, Node* lastNode, int lenght);
    Node* getFirstNode();
    Node* getLastNode();
    int getLenght();
};

#endif // EDGE_H
