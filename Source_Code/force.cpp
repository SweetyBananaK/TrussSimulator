#include "joint.hpp"
#include "utils.hpp"
#include "force.hpp"
#include "trusswidget.hpp"
#include <math.h>

Force::Force(Joint* pjoint_ptr, double pxforce, double pyforce){

    xforce = pxforce;
    yforce = pyforce;
    joint_ptr = pjoint_ptr;
    setFlags(QGraphicsItem::ItemIsSelectable);
}

    //Ueberladen des Renderrechtecks
QRectF Force::boundingRect() const{

  double min_x = std::min(joint_ptr->x(),joint_ptr->x() - Utils::ForceArrowScaling * xforce) - Utils::force_arrow_head_length;
  double min_y = std::min(joint_ptr->y(),joint_ptr->y() - Utils::ForceArrowScaling * yforce) - Utils::force_arrow_head_length;
  double dist_x = fabs(Utils::ForceArrowScaling * xforce) + 2*Utils::force_arrow_head_length;
  double dist_y = fabs(Utils::ForceArrowScaling * yforce) + 2*Utils::force_arrow_head_length;

  return QRectF(min_x,min_y,dist_x,dist_y);
}

    //Ueberladen der Hitbox
QPainterPath Force::shape() const{

    QPainterPath hitbox;

    double x1=joint_ptr->x();
    double x2=joint_ptr->x() - Utils::ForceArrowScaling * xforce;
    double y1=joint_ptr->y();
    double y2=joint_ptr->y() - Utils::ForceArrowScaling * yforce;
    double angle;
    if(x1-x2 != 0)
        angle=atan((y1-y2)/(x1-x2));
    else
        angle=M_PI_2;

    if(-0.2 <= angle && angle < 0.2) {
        hitbox.moveTo(x1,y1+6);
        hitbox.lineTo(x1,y1-6);
        hitbox.lineTo(x2,y2-6);
        hitbox.lineTo(x2,y2+6);
        hitbox.closeSubpath();
    }
    else if( M_PI_2 - 0.3 <= angle && angle <= M_PI_2 + 0.3) {
        hitbox.moveTo(x1+6,y1);
        hitbox.lineTo(x1-6,y1);
        hitbox.lineTo(x2-6,y2);
        hitbox.lineTo(x2+6,y2);
        hitbox.closeSubpath();
    }
    else {
        hitbox.moveTo(x1+6/sin(angle),y1-6/cos(angle));
        hitbox.lineTo(x1-6/sin(angle),y1+6/cos(angle));
        hitbox.lineTo(x2-6/sin(angle),y2+6/cos(angle));
        hitbox.lineTo(x2+6/sin(angle),y2-6/cos(angle));
        hitbox.closeSubpath();
    }

    return hitbox;
}


void Force::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget *)
{
  if(this->isSelected() == false) {
      painter->setPen(Qt::SolidLine);
      painter->setPen(Qt::red);
      painter->setBrush(Qt::red);
  }
  else {
      painter->setPen(Qt::DashDotDotLine);
      painter->setPen(Qt::blue);
      painter->setBrush(Qt::red);
  }
  double x,y,dx,dy,new_x,new_y,angle;

    x = joint_ptr->x();
    y = joint_ptr->y();

    dx = -Utils::ForceArrowScaling * xforce;
    dy = -Utils::ForceArrowScaling * yforce;

    angle = atan2(dy,dx); //rad
    new_x = x + cos(angle)*Utils::JointR,
    new_y = y + sin(angle)*Utils::JointR;


    //Hauptlinie
    painter->drawLine( new_x, new_y, new_x + dx, new_y + dy);

    //Pfeilspitzen
    QPointF tip(new_x,new_y);
    QPointF larrow(new_x + cos(angle - Utils::arrow_head_angle) * Utils::force_arrow_head_length,
                   new_y + sin(angle -  Utils::arrow_head_angle)* Utils::force_arrow_head_length);
    QPointF rarrow(new_x + cos(angle +  Utils::arrow_head_angle) * Utils::force_arrow_head_length,
                 new_y + sin(angle +  Utils::arrow_head_angle)* Utils::force_arrow_head_length);

    QPointF arrow_points[3] = {tip,larrow,rarrow};
    painter->drawPolygon(arrow_points,3);

}

Joint* Force::get_joint_ptr(){

    return joint_ptr;
}

double Force::get_xforce(){

    return xforce;
}

double Force::get_yforce(){

    return yforce;
}

void Force::set_xforce(double Fx) {
    xforce=Fx;
}

void Force::set_yforce(double Fy) {
    yforce=Fy;
}
