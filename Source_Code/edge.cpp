#include "edge.hpp"
#include "joint.hpp"
#include "trusswidget.hpp"

#include<math.h>


Edge::Edge(Joint* pjoint_ptr1, Joint* pjoint_ptr2, double pthickness){
    joint_ptr1 = pjoint_ptr1;
    joint_ptr2 = pjoint_ptr2;
    thickness = pthickness;
    (joint_ptr1)->set_edges(this);
    (joint_ptr2)->set_edges(this);
    setFlags(QGraphicsItem::ItemIsSelectable);
}

    //Ueberladen des Renderrechtecks
QRectF Edge::boundingRect() const{

    double min_x = std::min(joint_ptr1->x(),joint_ptr2->x());
    double min_y = std::min(joint_ptr1->y(),joint_ptr2->y());
    double dist_x = fabs(joint_ptr1->x() - joint_ptr2->x());
    double dist_y = fabs(joint_ptr1->y() - joint_ptr2->y());

    return QRectF(min_x,min_y,dist_x,dist_y);

}

    //Ueberladen der Hitbox
QPainterPath Edge::shape() const{

    QPainterPath hitbox;
//  hitbox.moveTo(joint_ptr1->x(),joint_ptr1->y());
//  hitbox.lineTo(joint_ptr2->x(),joint_ptr2->y());
    double x1=joint_ptr1->x();
    double x2=joint_ptr2->x();
    double y1=joint_ptr1->y();
    double y2=joint_ptr2->y();
    double angle;
    if(x1-x2 != 0)
        angle=atan((y1-y2)/(x1-x2));
    else
        angle=M_PI_2;


    if(-0.3 <= angle && angle <= 0.3) {
        hitbox.moveTo(x1,y1-6);
        hitbox.lineTo(x1,y1+6);
        hitbox.lineTo(x2,y2+6);
        hitbox.lineTo(x2,y2-6);
        hitbox.closeSubpath();
    }
    else if(M_PI_2-0.3 <= angle && angle <= M_PI_2+0.3) {
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

    //Ueberladung des Aussehens
void Edge::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*){

    painter->setPen(Qt::SolidLine);

    QPen pen;
    pen.setBrush(Qt::red);

    if(this->isSelected() == true)
        painter->setPen(pen);
    else
        painter->setPen(Qt::SolidLine);

    painter->drawLine(joint_ptr1->x(),joint_ptr1->y(),joint_ptr2->x(),joint_ptr2->y());
}

Joint* Edge::get_joint_ptr1(){

    return joint_ptr1;
}

Joint* Edge::get_joint_ptr2(){

    return joint_ptr2;
}
double Edge::get_thickness(){

    return thickness;
}
