#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    g.constructGraph();
    pathway.resize(0);
}
void MainWindow::paintEvent(QPaintEvent*)
{   
    //int height1 = height();
    int height1=790;
    //int width1 = width();
    int width1=800;
    QPainter p(this);
    std::vector<Edge> ways=g.getEdges();
    std::vector<Node> nodes=g.getNodes();
    for(Node& n:nodes)
    {
        n.transformCoord(g.getMinLat(), g.getMaxLat(), g.getMinLong(), g.getMaxLong(), height1, width1);

    }
    g.setNodes(nodes);
    for(Edge& e:ways)
    {
        QPen pen;
        p.setPen(pen);
        p.drawLine(nodes[e.getFirstNode()->getId()].getCoordinates(), nodes[e.getLastNode()->getId()].getCoordinates());
    }
    if(source.getId()!=-1)
    {
        QRect r(source.getCoordinates().x(), source.getCoordinates().y(), 8, 8);
        QPainter p(this);
        QPen pen;
        pen.setColor(Qt::red);
        p.setPen(pen);
        p.setBrush(QBrush(Qt::red));
        p.drawEllipse(r);
    }
    if(destination.getId()!=-1)
    {
        QRect r(destination.getCoordinates().x(), destination.getCoordinates().y(), 8, 8);
        QPainter p(this);
        QPen pen;
        pen.setColor(Qt::darkGreen);
        p.setPen(pen);
        p.setBrush(QBrush(Qt::darkGreen));
        p.drawEllipse(r);
    }
    if(pathway.size()>0)
    {
        QPainter p(this);
        QPen pen;
        pen.setColor(Qt::green);
        p.setPen(pen);
        int y=destination.getId();
        int x=pathway[destination.getId()];
        while(x!=-1)
        {
            p.drawLine(nodes[y].getCoordinates(),nodes[x].getCoordinates());
            y=x;
            x=pathway[y];
        }
    }
    update();
}
void MainWindow:: mouseReleaseEvent(QMouseEvent *ev)
{
    QPointF pos=ev->position();
    std::vector<Node> nodes=g.getNodes();
    for(Node& n:nodes)
    {
        if(QLineF(n.getCoordinates(),pos).length()<2)
        {
            if(source.getId()==-1)
            {
                source=n;
                update();
            }
            else if(destination.getId()==-1)
            {
                destination=n;
                update();
                pathway.resize(nodes.size());
                pathway=g.dijkstra(source,destination);
                update();

            }
            break;
        }
    }
}
MainWindow::~MainWindow()
  {
    delete ui;
}

