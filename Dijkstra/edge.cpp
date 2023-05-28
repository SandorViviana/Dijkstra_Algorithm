#include "edge.h"

Edge::Edge()
{

}

Edge::Edge(Node *firstNode, Node *lastNode, int lenght){
    this->firstNode=firstNode;
    this->lastNode=lastNode;
    this->lenght=lenght;

}

Node *Edge::getFirstNode() {return firstNode;}

Node *Edge::getLastNode() {return lastNode;}

int Edge::getLenght()
{
    return lenght;
}
