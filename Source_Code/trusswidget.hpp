#pragma once

#include <QGraphicsView>
#include "joint.hpp"
#include "edge.hpp"
#include "force.hpp"
#include "truss.hpp"
#include "myscene.hpp"
#include "displacement_arrow.hpp"
#include <vector>

class Truss;

class TrussWidget : public QGraphicsView
{
    Q_OBJECT
protected:
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;



signals:
    void sendSelectSignals();
    void sendClearSignals();
    void sendMoveSignals();
    void sendEdgeGetLoacatorSignals();
    void sendAddJointSignals();

public slots:
    void zoomIn();
    void zoomOut();

public:
    TrussWidget(QWidget *parent);
//    ~TrussWidget();
    QGraphicsEllipseItem O;
    QGraphicsItem* Joint_selected=0;
    QGraphicsItem* Edge_selected=0;
    QGraphicsItem* Force_selected=0;
    QPointF m_startPos;
    QPointF mousePos;
    double scale_m;
    bool mouse_press;
    bool right_click=false;

    vector<Displacement_arrow* > v_displacement_ptr;
    Truss* deformed_truss;


    QList<QGraphicsItem *> itemList;
    Truss* current_truss;
    myScene* scene;


    void show_truss(Truss* selected_truss);
    void delete_truss(Truss* selected_truss);
    void toggle_truss_visibility(Truss* selected_truss, bool visibility);
    void create_displacement_arrows();
    void toggle_displacement_arrow_visibility(bool visibility);
    void delete_displacement_arrows();
    void Simulate(bool nonlinear);


};
