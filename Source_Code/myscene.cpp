#include "myscene.hpp"
#include "ui_mainwindow.h"
#include "trusswidget.hpp"
#include <iostream>
#include <string>
#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneContextMenuEvent>

    //Konstruktor
myScene::myScene(QObject *parent) : QGraphicsScene(parent)
{
    //Netz background
    QPolygonF myPolygon1;
    myPolygon1 << QPointF(0,10) << QPointF(20,10);
    QPolygonF myPolygon2;
    myPolygon2 << QPointF(10,0) << QPointF(10,20);
    QPixmap pixmap(20, 20);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);

    QVector<qreal> dashes;          //line style ----
    qreal space = 2;
    dashes << 2 << space << 2 <<space;
    QPen pen(Qt::lightGray,1);
    pen.setDashPattern(dashes);
    pen.setWidth(1);

    painter.setPen(pen);
    painter.translate(0, 0);
    painter.drawPolyline(myPolygon1);
    painter.drawPolyline(myPolygon2);
    this->setBackgroundBrush(pixmap);

    createActions();

}
myScene::~myScene() {

    delete menu;
}

    //Menue wird erstellt
void myScene::createActions() {

    menu = new QMenu;

    //Funktionen
    QAction* zoomIn = menu->addAction("reinzoomen"); //0
    zoomIn->setIcon(QIcon(":/icon/zoomIn.png"));
    QAction* zoomOut = menu->addAction("rauszoomen"); //1
    zoomOut->setIcon(QIcon(":/icon/zoomOut.png"));
    menu->addSeparator();
    QAction* addJointAction = menu->addAction("Knoten hinzufügen"); //3
    QAction* deleteJointAction = menu->addAction("Knoten löschen"); //4
    menu->addSeparator();
    QAction* addEdgeAction = menu->addAction("Kanten hinzufügen"); //6
    QAction* deleteEdgeAction = menu->addAction("Kanten löschen"); //7
    menu->addSeparator();
    QAction* addForceAction = menu->addAction("Kräfte hinzufügen"); //9
    QAction* deleteForceAction = menu->addAction("Kräfte löschen"); //10
    menu->addSeparator();
    QAction* addSupport = menu->addAction("Lager hinzufügen");//12
    QAction* deleteSupport = menu->addAction("Lager löschen");//13
    menu->addSeparator();
    QAction* emodulAktiv = menu->addAction("E-Modul aktivieren");//15

}

    //Das Menü wird an der Maus angezeigt
void myScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {

        menu->exec(event->screenPos());
}

    //Koordinatenpunkt P
void myScene::set_Point(QPointF P){

    Point=P;
}

QPointF myScene::get_Point() {

    return Point;
}

