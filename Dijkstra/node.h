#ifndef NODE_H
#define NODE_H
#include <QPointF>

class Node
{
private:
    int id;
    int longitude,latitude;
    QPointF screenCoordinates;
public:
    Node();
    Node(int id);
    Node(int id, int longitude, int latitude);
    int getId();
    int getLongitude();
    int getLatitude();
    void setId(int id);
    void setLatitude(int latitude);
    void setLongitude(int longitude);
    void transformCoord(int minLat, int maxLat, int minLong, int maxLong, int height, int width);
    QPointF getCoordinates() {return screenCoordinates;}
};

#endif // NODE_H
