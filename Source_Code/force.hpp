#pragma once
#include <QGraphicsItem>

class Joint;

class Force : public QGraphicsItem

{
    public :
        Force(Joint* pjoint_ptr, double pxforce, double pyforce);

        QRectF boundingRect() const override;
        QPainterPath shape() const override;
        void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget*) override;
        virtual int type() const override {
            return m_type;
        }

        Joint* get_joint_ptr();
        double get_xforce();
        double get_yforce();
        void set_xforce(double Fx);
        void set_yforce(double Fy);
    private :

    Joint* joint_ptr;
    double xforce,yforce;
    int m_type = 900;

};
