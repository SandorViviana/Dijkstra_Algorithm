#ifndef GRAPH_H
#define GRAPH_H
#include "edge.h"
#include<vector>
#include <iterator>
#include<list>
#include <QFile>
#include <QtXml>
#include <QMessageBox>
#include <queue>



class Graph
{
private:
    std::vector<Node>nodes;
    std::vector<Edge>edges;
    std::vector<std::list<std::pair<int,int>>>adiacencyList;
    int minLat=-1, maxLat=-1,minLong=-1, maxLong=-1; //pentru scalare

public:
    Graph();
    std::vector<Node> getNodes();
    std::vector<Edge> getEdges();
    std::vector<std::list<std::pair<int,int>>> getAdiacencyList();
    void addNode(Node n);
    void addEdge(Edge e);   
    std::vector<int> dijkstra(Node source, Node destination);
    std::vector<Edge> road(std::vector<Node*> predecesor);
    void constructGraph();
    int getMinLat() {return minLat;}
    int getMaxLat() {return maxLat;}
    int getMinLong() {return minLong;}
    int getMaxLong() {return maxLong;}
    void setNodes(std::vector<Node> nodes){this->nodes=nodes;}
};

#endif // GRAPH_H
