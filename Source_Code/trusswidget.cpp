#include "trusswidget.hpp"
#include "truss.hpp"
#include "utils.hpp"
#include <math.h>
#include <iostream>
#include <Eigen/Dense>
#include <QWheelEvent>
#include <QScrollBar>
#include <QList>
#include <QDebug>
#include <QTransform>
#include<QGraphicsSceneMouseEvent>

TrussWidget::TrussWidget(QWidget *parent)
:   QGraphicsView(parent)
{
    setMouseTracking(true);
    setDragMode(NoDrag);

    scene = new myScene(this);
    scale_m = 1;
    scene->setSceneRect(0,0,this->width(),this->height());     // x,y , width, height
    scene->setItemIndexMethod(QGraphicsScene::BspTreeIndex);   // Alternativ ::NoIndex <- ist eher für dynamische Grafiken
    setScene(scene);                                           // connected View mit der Szene
    setRenderHint(QPainter::Antialiasing);                     // Bessere Bildqualität des gezeichneten
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);

    scale(qreal(1.2),qreal(1.2));
    setMinimumSize(500,500);
    setWindowTitle("Truss Simulator");
    current_truss = new Truss();

    O.setPen(QColor(Qt::white));
    O.setBrush(QBrush(QColor(Qt::red)));
    O.setFlags(QGraphicsItem::ItemIsSelectable);
    O.setSelected(true);

    connect(scene->menu->actions()[0],SIGNAL(triggered()),this, SLOT(zoomIn()) );
    connect(scene->menu->actions()[1],SIGNAL(triggered()),this, SLOT(zoomOut()) );
}


void TrussWidget::wheelEvent(QWheelEvent* event){
    QPoint prev_viewPos = event->pos();
    QPointF prev_scenePos = this->mapToScene(prev_viewPos);

    if((event->delta() > 0)&&(scale_m >= 10)){
        return;
    }
    else if((event->delta() < 0)&&(scale_m <= 0.5)){
        return;
     }
     else{
        qreal scaleFactor = this->matrix().m11();
        scale_m = scaleFactor;
        int wheelDeltaValue = event->delta();
        if (wheelDeltaValue > 0){
             this->scale(1.2,1.2);
        }
        else{
            this->scale(1.0 / 1.2,1.0 / 1.2);
        }
        this->scene->setSceneRect(this->mapToScene(this->rect()).boundingRect());

        QPointF scenePos = this->mapToScene(prev_viewPos);
        QPointF disPointF = scenePos - prev_scenePos;
        this->scene->setSceneRect(this->scene->sceneRect().x()-disPointF.x(),this->scene->sceneRect().y()-disPointF.y(),
                                        this->scene->sceneRect().width(),this->scene->sceneRect().height());
        update();
        }
}


void TrussWidget::mouseMoveEvent(QMouseEvent *event) {
    mousePos = mapToScene(event->pos());
    emit sendMoveSignals();

    if(event->buttons() == Qt::MidButton){
        QPointF disPointF = m_startPos - event->pos();
        this->scene->setSceneRect(this->scene->sceneRect().x()+1/scale_m*disPointF.x(),this->scene->sceneRect().y()+1/scale_m*disPointF.y(),
                                  this->scene->sceneRect().width(),this->scene->sceneRect().height());
        m_startPos = event->pos();
    }
    if(mouse_press == true) setDragMode(ScrollHandDrag);
    else setDragMode(NoDrag);
}

void TrussWidget::mousePressEvent(QMouseEvent *event) {    
    m_startPos = event->pos();
    QGraphicsEllipseItem* o=&O;
    int Number_of_selected=0;
    QList<QGraphicsItem*>::iterator iter_1;
    QGraphicsItem* poniter_Joint =nullptr;
    //item O
    scene->set_Point(this->mapToScene(event->pos()));

    if(event->buttons() == Qt::MidButton) mouse_press=true; //draw

    if(event->button() == Qt::LeftButton) {
        if(event->modifiers() != Qt::ShiftModifier) {
            itemList = scene->selectedItems();
            O.setRect(scene->get_Point().x()-3,scene->get_Point().y()-3,6,6);

                for(QList<QGraphicsItem *>::iterator iter = itemList.begin();iter < itemList.end();iter++){
                    if((*iter)->type() == O.type()) {
                        scene->removeItem(*iter);
                        itemList.erase(iter);
                    }
                }
                O.setSelected(true);
                scene->addItem(o);

                emit scene->sendSignals();
        }

        else if(event->modifiers() == Qt::ShiftModifier) { //auswahlen
            O.setSelected(true);
            //Knoten loschen
            if(current_truss->v_joint_ptr.empty() == false) {
                itemList = scene->selectedItems();
                for(QList<QGraphicsItem *>::iterator iter2 = itemList.begin();iter2 < itemList.end();iter2++){
                    if((*iter2)->type() == 700) {
                        Number_of_selected++;
                        if(Number_of_selected == 1) {
                            poniter_Joint=*iter2; //Speichert erste Obeject
                            iter_1=iter2;
                        }
                        if(Number_of_selected == 2) {
                            (*iter_1)->setSelected(false);
                            itemList.erase(iter_1);
                            (*iter2)->setSelected(false);
                            itemList.erase(iter2);
                        }
                    }
                }

            }
            //Kanten loschen
            if(current_truss->v_edge_ptr.empty() == false) {
                itemList = scene->selectedItems();
                for(QList<QGraphicsItem *>::iterator iter_kanten = itemList.begin();iter_kanten < itemList.end();iter_kanten++){
                    if((*iter_kanten)->type() == 800) {
                        (*iter_kanten)->setSelected(false);
                        itemList.erase(iter_kanten);
                    }
                }
            }
            //Krafte loschen
            if(current_truss->v_force_ptr.empty() == false) {
                itemList = scene->selectedItems();
                for(QList<QGraphicsItem *>::iterator iter_kraft = itemList.begin();iter_kraft < itemList.end();iter_kraft++){
                    if((*iter_kraft)->type() == 900) {
                        (*iter_kraft)->setSelected(false);
                        itemList.erase(iter_kraft);
                    }
                }
            }

            itemList = scene->selectedItems();
            QTransform transform;
            QPoint p = event->pos();
            QPointF p_scene = mapToScene(p);
            QGraphicsItem *item_s = scene->itemAt(p_scene,transform);
            Joint_selected=0;
            Edge_selected=0;
            Force_selected=0;

            if(item_s != 0 && item_s->type() == O.type())
                item_s = 0;

            if(item_s != 0 && item_s->isSelected() == true) {
                item_s->setSelected(false);
                for(QList<QGraphicsItem *>::iterator iter_clickedItem = itemList.begin();iter_clickedItem < itemList.end();iter_clickedItem++) {
                    if((*iter_clickedItem) == item_s)
                        itemList.erase(iter_clickedItem);
                }
                emit sendClearSignals();
            }
            else if(item_s != 0 && item_s->isSelected() == false) {
                item_s->setSelected(true);

                if(item_s->type() == 700)
                    Joint_selected=item_s;

                else if(item_s->type() == 800) {
                    Edge_selected=item_s;
                    if(Number_of_selected == 1){
                        poniter_Joint->setSelected(false);
                        itemList.removeOne(poniter_Joint);
                    }
                }
                else if(item_s->type() == 900) {
                    Force_selected=item_s;
                    if(Number_of_selected == 1){
                        poniter_Joint->setSelected(false);
                        itemList.removeOne(poniter_Joint);
                    }
                }
            }

            if(item_s == 0) {
                emit sendClearSignals();
                for(QList<QGraphicsItem *>::iterator iter_for_all = itemList.begin();iter_for_all < itemList.end();iter_for_all++) {
                    (*iter_for_all)->setSelected(false);
                    itemList.erase(iter_for_all);
                    if((*iter_for_all)->type() == O.type())
                        scene->removeItem(*iter_for_all);
                }
            }

            itemList = scene->selectedItems();
            emit sendSelectSignals();

        }
    }

    else if(event->button() == Qt::RightButton){
        right_click=true;
        QTransform transform;
        QPoint p = event->pos();
        QPointF p_scene = mapToScene(p);
        QGraphicsItem *item_s = scene->itemAt(p_scene,transform);
        itemList = scene->selectedItems();
        QList<QAction*> Actions=scene->menu->actions();
        for(int i=0;i<scene->menu->actions().size();i++){ //zoomIn,zoomOut,Knoten hinzufugen kann benutzen
            if(i < 4)
                Actions[i]->setEnabled(true);
            else
                Actions[i]->setEnabled(false);
        }
        Actions[15]->setEnabled(true);

        //Überprüft, ob es ein o-Objekt schon gibt, wenn nicht, erstellt eines mit der Maus
        bool isO = false;
        int J_temp=0;
        if(itemList.empty() == false) {
            //fur zwei Knoten
            for(QList<QGraphicsItem *>::iterator iter2 = itemList.begin();iter2 < itemList.end();iter2++){
                if((*iter2)->type() == 700) {
                    J_temp++;
                }
            }

            for(int i=0;i<itemList.size();i++) {
                if(itemList[i]->type() == O.type())
                    isO = true;
            }
            //Auswahl abbrechen
            if(J_temp != 2) {
                for(QList<QGraphicsItem* >::iterator iter=itemList.begin();iter < itemList.end();iter++ ) {
                        (*iter)->setSelected(false);
                        itemList.erase(iter);
                }
                if(isO) {
                    scene->removeItem(o);
                    isO=false;
                }
            }
            else if(J_temp == 2 && item_s != 0) {
                for(QList<QGraphicsItem* >::iterator iter=itemList.begin();iter < itemList.end();iter++ ) {
                        (*iter)->setSelected(false);
                        itemList.erase(iter);
                }
                if(isO) {
                    scene->removeItem(o);
                    isO=false;
                }
            }
            else if(J_temp == 2 && item_s == 0) {
                for(QList<QGraphicsItem* >::iterator iter=itemList.begin();iter < itemList.end();iter++ ) {
                    if((*iter)->type() != 700) {
                        (*iter)->setSelected(false);
                        itemList.erase(iter);
                    }
                }
                if(isO) {
                    scene->removeItem(o);
                    isO=false;
                }
            }
        }

        itemList = scene->selectedItems();


        if(item_s == 0 && J_temp != 2) {
            if(isO == false) {
                O.setSelected(true);
                scene->addItem(o);
            }
            O.setRect(scene->get_Point().x()-3,scene->get_Point().y()-3,6,6);
            emit scene->sendSignals();
        }
        else if(item_s == 0 && J_temp == 2) {
            if(isO == false) {
                O.setSelected(true);
                scene->addItem(o);
            }
            O.setRect(scene->get_Point().x()-3,scene->get_Point().y()-3,6,6);
            emit scene->sendSignals();
            Actions[6]->setEnabled(true);//Kanten hinzufugen
        }


        itemList = scene->selectedItems();
        //Wenn der Knoten ausgewahlt ist, aktiviert Funktionen fur der Knoten:hinzufugen,loschen,kraft hinzufugen
        if(current_truss->v_joint_ptr.empty() == false && item_s !=0){
            if(item_s->type() == 700) {
                //Knoten auswahlen
                item_s->setSelected(true);
                Joint_selected=item_s;
                Edge_selected=0;
                Force_selected=0;
                emit sendSelectSignals();
                //aktivieren
                Actions[3]->setEnabled(false);//Knoten hinzufugen "unverfügbar"   gibt es dieses Wort?
                Actions[4]->setEnabled(true); //loschen
                Actions[9]->setEnabled(true); //kraft hinzufugen
                Actions[12]->setEnabled(true);//Lager hinzufugen
                Actions[13]->setEnabled(true);//Lager loschen
            }
        }
        //Wenn die Kante ausgewählt ist,aktiviert Funktionen fur die Kante:loschen
        if(current_truss->v_edge_ptr.empty() == false && item_s !=0){
            if(item_s->type() == 800) {
                //Kante auswahlen
                item_s->setSelected(true);
                Edge_selected=item_s;
                Force_selected=0;
                Joint_selected=0;
                emit sendSelectSignals();
                Actions[3]->setEnabled(false);//Knoten hinzufugen "unverfügbar"
                Actions[7]->setEnabled(true); //loschen
            }
        }
        //Krafte,loschen
        if(current_truss->v_force_ptr.empty() == false && item_s !=0){
            if(item_s->type() == 900) {
                item_s->setSelected(true);
                Force_selected=item_s;
                Edge_selected=0;
                Joint_selected=0;
                emit sendSelectSignals();
                Actions[3]->setEnabled(false);//Knoten hinzufugen "unverfügbar"
                Actions[10]->setEnabled(true); //loschen
            }
        }
    }//rechtkcken
    right_click=false;
}

void TrussWidget::mouseReleaseEvent(QMouseEvent *event) {
    mouse_press=false;
    setDragMode(NoDrag);
}

void TrussWidget::show_truss(Truss* selected_truss){

    int n_joints = selected_truss->v_joint_ptr.size();
    int n_edges = selected_truss->v_edge_ptr.size();
    int n_forces = selected_truss->v_force_ptr.size();

    for(int i=0; i < n_joints; i++){
        scene->addItem(selected_truss->v_joint_ptr[i]);
    }
    for(int i=0; i < n_edges; i++){
        scene->addItem(selected_truss->v_edge_ptr[i]);
    }
    for(int i=0; i < n_forces; i++){
        scene->addItem(selected_truss->v_force_ptr[i]);
    }
}


void TrussWidget::delete_truss(Truss* selected_truss){

    int n_joints = selected_truss->v_joint_ptr.size();
    int n_edges = selected_truss->v_edge_ptr.size();
    int n_forces = selected_truss->v_force_ptr.size();

    for(int i=0; i < n_joints; i++){
        scene->removeItem(selected_truss->v_joint_ptr[i]);
    }
    for(int i=0; i < n_edges; i++){
        scene->removeItem(selected_truss->v_edge_ptr[i]);
    }
    for(int i=0; i < n_forces; i++){
        scene->removeItem(selected_truss->v_force_ptr[i]);
    }
    delete selected_truss;
}

    void TrussWidget::toggle_truss_visibility(Truss* selected_truss, bool visibility){

        int n_joints = selected_truss->v_joint_ptr.size();
        int n_edges = selected_truss->v_edge_ptr.size();
        int n_forces = selected_truss->v_force_ptr.size();

        for(int i=0; i < n_joints; i++){
            selected_truss->v_joint_ptr[i]->setVisible(visibility);
        }
        for(int i=0; i < n_edges; i++){
            selected_truss->v_edge_ptr[i]->setVisible(visibility);
        }
        for(int i=0; i < n_forces; i++){
          selected_truss->v_force_ptr[i]->setVisible(visibility);
        }
    }

    void TrussWidget::create_displacement_arrows(){
      int n_joints =current_truss->v_joint_ptr.size();
      v_displacement_ptr.reserve(n_joints);
      for(int i=0;i<n_joints;i++){
          double x1,x2,y1,y2;
          x1 = current_truss->v_joint_ptr[i]->x();
          x2 = deformed_truss->v_joint_ptr[i]->x();

          y1 = current_truss->v_joint_ptr[i]->y();
          y2 = deformed_truss->v_joint_ptr[i]->y();

          Displacement_arrow* new_arrow = new Displacement_arrow(x1,y1,x2,y2);
          v_displacement_ptr.push_back(new_arrow);
          scene->addItem(v_displacement_ptr[i]);
        }
    }

    void TrussWidget::delete_displacement_arrows(){

      int n_arrows = v_displacement_ptr.size();

        for(int i=0; i < n_arrows; i++){
            scene->removeItem(v_displacement_ptr[i]);
            delete v_displacement_ptr[i];
          }
        v_displacement_ptr.clear();
    }


   void TrussWidget::toggle_displacement_arrow_visibility(bool visibility){

      int n_arrows = v_displacement_ptr.size();
        for(int i=0; i < n_arrows; i++){
            v_displacement_ptr[i]->setVisible(visibility);
          }
    }


void TrussWidget::Simulate(bool is_nonlinear){
  Eigen::Matrix<double,Utils::Dynamic,1> u = current_truss->calc_u(is_nonlinear);
  deformed_truss = new Truss(current_truss,u);
  show_truss(deformed_truss);
  create_displacement_arrows();
}

void TrussWidget::zoomIn() {
    if(scale_m >= 10)
        return;

    qreal scaleFactor = this->matrix().m11();
    scale_m = scaleFactor;
    this->scale(1.5,1.5);
    this->scene->setSceneRect(this->mapToScene(this->rect()).boundingRect());
}

void TrussWidget::zoomOut() {
    if(scale_m <= 0.5)
        return;

    qreal scaleFactor = this->matrix().m11();
    scale_m = scaleFactor;
    this->scale(0.5,0.5);
    this->scene->setSceneRect(this->mapToScene(this->rect()).boundingRect());
}


