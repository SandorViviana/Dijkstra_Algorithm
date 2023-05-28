#include "node.h"

Node::Node()
{

}

Node::Node(int id)
{
    this->id=id;
}

Node::Node(int id, int longitude, int latitude)
{
    this->id=id;
    this->latitude=latitude;
    this->longitude=longitude;
}

int Node::getId() {return id;}

int Node::getLongitude() {return longitude;}

int Node::getLatitude() {return latitude;}

void Node::setId(int id) {this->id=id;}

void Node::setLatitude(int latitude) {this->latitude=latitude;}

void Node::setLongitude(int longitude){this->longitude=longitude;}

void Node::transformCoord(int minLat, int maxLat, int minLong, int maxLong, int height, int width)
{

    qreal x=(double)(longitude-minLong)/(maxLong-minLong)*(width-200)+200;
    qreal y=(double)(minLat-latitude)/(maxLat-minLat)*(height-1)+height;
    screenCoordinates.setX(x);
    screenCoordinates.setY(y);

}
