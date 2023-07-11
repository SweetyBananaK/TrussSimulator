#include "joint.hpp"
#include "trusswidget.hpp"
#include "utils.hpp"

#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>



Joint::Joint(int plocator, double x, double y, double psupport)
{
    locator = plocator;
    support = psupport;
    attached_edges.reserve(default_reserved_adjacent_edges);
    setZValue(1.0);
    setPos(x,y);
    setFlags(QGraphicsItem::ItemIsSelectable);
}

    //Ueberladen des Renderrechtecks
QRectF Joint::boundingRect() const
{
    if(support == -2.0){
        return QRectF(-Utils::support_width, -Utils::support_height, 2*Utils::support_width, 2*Utils::support_height);
    }
    return QRectF(-Utils::JointR, -Utils::JointR, 2*Utils::JointR, 2*Utils::JointR);
}

    //Ueberladen der Hitbox
QPainterPath Joint::shape() const
{
    QPainterPath hitbox;
    hitbox.addEllipse(-Utils::JointR, -Utils::JointR, 2*Utils::JointR, 2*Utils::JointR);

    return hitbox;
}

    //Ueberladung des Aussehens
void Joint::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*){ // TODO warum das letzte Argument komisch ist

    painter->setPen(Qt::SolidLine);
    painter->setBrush(Qt::white);

    QPen pen;
    pen.setStyle(Qt::DashDotDotLine);
    pen.setBrush(Qt::red);

    if(this->isSelected() == true)
        painter->setPen(pen);
    else
        painter->setPen(Qt::SolidLine);

    if(support == -2){
        const QPointF points[3] = {
            QPointF(0.0, 0.0),
            QPointF(Utils::support_width, Utils::support_height),
            QPointF(-Utils::support_width, Utils::support_height)};
          painter->drawConvexPolygon(points, 3);
      }

    painter->drawEllipse(-Utils::JointR, -Utils::JointR, 2*Utils::JointR, 2*Utils::JointR);

    QFont font;
    font.setPointSize(7);
    int z_locator = locator+1;
    if(z_locator < 10) {
    painter->setFont(font);
    painter->drawText(-2, +3,QString::number(locator+1));
    }
    else {
        font.setPointSize(5);
        painter->setFont(font);
        painter->drawText(-3, +3,QString::number(locator+1));
    }
}

void Joint::mousePressEvent(QGraphicsSceneMouseEvent *event) {

    return;
}

void Joint::print(){

    std::cout << "X: " << this->x() << ",    Y: " << this->y() << std::endl;
    std::cout << "Locator: " << this->get_locator() << " " << "Support: " << this->get_support() << std::endl;
}

int Joint::get_locator(){

    return locator;
}

void Joint::set_locator(int plocator) {

    locator = plocator;
}

double Joint::get_support(){

    return support;
}

void Joint::set_support(double psupport){

    support = psupport;
}

void Joint::set_edges(Edge* edge){

    attached_edges.push_back(edge);
}

vector<Edge*>& Joint::get_edges(){

    return attached_edges;
}

void Joint::remove_edge(Edge *edge){

  for(int i =0; i < attached_edges.size(); i++  ){
        if(edge == attached_edges[i]){
            attached_edges.erase(attached_edges.begin()+i);
            break;
          }
    }
}











