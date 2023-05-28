#include "graph.h"

Graph::Graph()
{

}

std::vector<Node> Graph::getNodes() {return nodes;}

std::vector<Edge> Graph::getEdges() {return edges;}

std::vector<std::list<std::pair<int,int>> > Graph::getAdiacencyList() {return adiacencyList;}

void Graph::addNode(Node n)
{nodes.push_back(n);
    adiacencyList.resize(adiacencyList.size()+1);
    if(n.getLatitude()>maxLat)
        maxLat=n.getLatitude();
    if(n.getLongitude()>maxLong)
        maxLong=n.getLongitude();
    if(minLat==-1 || n.getLatitude()<minLat)
        minLat=n.getLatitude();
    if(minLong==-1 || n.getLongitude()<minLong)
        minLong=n.getLongitude();


}

void Graph::addEdge(Edge e)
{edges.push_back(e);
    std::pair<int,int>p1(e.getLastNode()->getId(),e.getLenght());
    std::pair<int,int> p2(e.getFirstNode()->getId(),e.getLenght());
    adiacencyList[e.getFirstNode()->getId()].insert(adiacencyList[e.getFirstNode()->getId()].end(),p1);
   //adiacencyList[e.getLastNode()->getId()].insert(adiacencyList[e.getLastNode()->getId()].end(),p2);
}



std::vector<int> Graph::dijkstra(Node source, Node destination)
{
    std::vector<int>distance;
    distance.resize(nodes.size(),-1);
    distance[source.getId()]=0;
    std::vector<int>predecesor;
    predecesor.resize(nodes.size(),-1);
    std::vector<bool> visited;
    visited.resize(nodes.size(),false);

    auto cmp=[&](std::pair<int,int> p1, std::pair<int,int> p2){return p1.second>p2.second;};
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, decltype(cmp)>order(cmp);   
    order.push(std::pair(source.getId(), distance[source.getId()]));
    while(!order.empty())
    {
        std::pair<int,int>point=order.top();
        while(!order.empty() && visited[point.first])
        {
            order.pop();
            point=order.top();
        }
        visited[point.first]=true;
        if(point.first==destination.getId())
            break;
        for(const auto& it:adiacencyList[point.first])
        {
            if(!visited[it.first])
            {
                if(distance[it.first]==-1 || distance[it.first]>distance[point.first]+it.second)
                {
                    distance[it.first]=distance[point.first]+it.second;
                    predecesor[it.first]=point.first;
                    std::pair<int,int>aux=std::make_pair(it.first, distance[it.first]);
                    order.push(aux);
                    //order.push(std::pair(it.first, distance[it.first]));
                }
            }
        }

    }

    return predecesor;


}
void Graph::constructGraph()
{
    QDomDocument xmlReader;
    QFile map("E:/Facultate/Anul II/Semestrul I/Algoritmica grafurilor/Laborator/Tema 5/Harta_Luxemburg.xml");
    if(!map.open(QIODevice::ReadOnly))
    {
        QMessageBox msg;
        msg.setText("Couldn't open xmlfile.xml to load settings for download");
        msg.exec();
        return;
    }
    xmlReader.setContent(&map);
    map.close();

    QDomElement root=xmlReader.documentElement();
    QDomElement component=root.firstChild().toElement();
    while(!component.isNull())
    {
        if(component.tagName()=="nodes")
        {
            QDomElement node=component.firstChild().toElement();
            while(!node.isNull())
            {
                int id=node.attribute("id").toInt();
                int latitude=node.attribute("longitude").toInt();
                int longitude=node.attribute("latitude").toInt();
                addNode(Node(id,longitude,latitude));
                node=node.nextSibling().toElement();
            }

        }
        if(component.tagName()=="arcs")
        {
            QDomElement edge=component.firstChild().toElement();
            while(!edge.isNull())
            {
                int first=edge.attribute("from").toInt();
                int last=edge.attribute("to").toInt();
                int lenght=edge.attribute("length").toInt();
                addEdge(Edge(&nodes[first], &nodes[last],lenght));
                edge=edge.nextSibling().toElement();
            }


        }
        component=component.nextSibling().toElement();
    }
}
