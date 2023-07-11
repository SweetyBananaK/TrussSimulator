#include "displacement_arrow.hpp"
#include "trusswidget.hpp"
#include <math.h>

Displacement_arrow::Displacement_arrow(double px1, double py1, double px2, double py2){

  x1 = px1;
  y1 = py1;
  x2 = px2;
  y2 = py2;
  setZValue(2.0);
}

    //Ueberladen des Renderrechtecks
QRectF Displacement_arrow::boundingRect() const{

    double min_x = std::min(x1,x2) - Utils::displacement_arrow_head_length;
    double min_y = std::min(y1,y2) - Utils::displacement_arrow_head_length;
    double dist_x = fabs(x1-x2) + 2*Utils::displacement_arrow_head_length;
    double dist_y = fabs(x1-x2) + 2*Utils::displacement_arrow_head_length;

    return QRectF(min_x,min_y,dist_x,dist_y);
}

    //Ueberladen der Hitbox
QPainterPath Displacement_arrow::shape() const{

    QPainterPath hitbox;
    hitbox.moveTo(x1,y1);
    hitbox.lineTo(x2,y2);
    // ToDo: richtige Hitbox einbauen (im Moment nur die Linie, noch nicht der Pfeilkopf)
    return hitbox;
}

    //Ueberladung des Aussehens
void Displacement_arrow::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget *){

    double dx,dy,new_x1,new_x2,new_y1,new_y2,angle;
    dx = x2-x1;
    dy = y2-y1;

    //keine sinnlosen Pfeile malen
    if(dx == 0 && dy == 0){ return;}

    painter->setPen(Qt::DotLine);
    painter->setPen(Qt::blue);
    painter->setBrush(Qt::blue);

    angle = atan2(dy,dx); //rad

    new_x1 = x1 + cos(angle)*Utils::JointR;
    new_y1 = y1 + sin(angle)*Utils::JointR;
    new_x2 = x2 - cos(angle)*Utils::JointR,
    new_y2 = y2 - sin(angle)*Utils::JointR;


    //Hauptlinie
    painter->drawLine( new_x1, new_y1, new_x2, new_y2);

    //Pfeilspitzen
    QPointF tip(new_x2,new_y2);
    double dis = sqrt(dx*dx+dy*dy);
//    QPointF larrow;
//    QPointF rarrow;
    if(dis < 70) {
        QPointF larrow(new_x2 - cos(angle - Utils::arrow_head_angle) * dis*0.2,
                       new_y2 - sin(angle - Utils::arrow_head_angle)*dis*0.2);

        QPointF rarrow(new_x2 - cos(angle + Utils::arrow_head_angle) * dis*0.2,
                       new_y2 - sin(angle + Utils::arrow_head_angle)*dis*0.2);
        QPointF arrow_points[3] = {tip,larrow,rarrow};
        painter->drawPolygon(arrow_points,3);
    }
    else {
        QPointF larrow(new_x2 - cos(angle - Utils::arrow_head_angle) * Utils::displacement_arrow_head_length,
                       new_y2 - sin(angle - Utils::arrow_head_angle)*Utils::displacement_arrow_head_length);

        QPointF rarrow(new_x2 - cos(angle + Utils::arrow_head_angle) * Utils::displacement_arrow_head_length,
                       new_y2 - sin(angle + Utils::arrow_head_angle)*Utils::force_arrow_head_length);
        QPointF arrow_points[3] = {tip,larrow,rarrow};
        painter->drawPolygon(arrow_points,3);
    }

//    QPointF arrow_points[3] = {tip,larrow,rarrow};
//    painter->drawPolygon(arrow_points,3);
}

