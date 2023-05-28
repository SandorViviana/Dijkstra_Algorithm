#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.h"
#include <QLineF>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QGuiApplication>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void paintEvent(QPaintEvent *);
    MainWindow(QWidget *parent = nullptr);
    void mouseReleaseEvent(QMouseEvent *ev);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Graph g;
    Node source=Node(-1),destination=Node(-1);
    std::vector<int>pathway;
};
#endif // MAINWINDOW_H
