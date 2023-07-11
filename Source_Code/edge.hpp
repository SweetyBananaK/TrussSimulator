#pragma once

#include <QGraphicsItem>

class Joint;

class Edge : public QGraphicsItem
{
    public:
        Edge(Joint* joint_ptr1, Joint* joint_ptr2, double thickness);

        QRectF boundingRect() const override;
        QPainterPath shape() const override;
        void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        virtual int type() const override {
            return m_type;
        }

        Joint* get_joint_ptr1();
        Joint* get_joint_ptr2();
        double get_thickness();

    private:
        int m_type=800;
        double thickness;
        Joint* joint_ptr1;
        Joint* joint_ptr2;
};
