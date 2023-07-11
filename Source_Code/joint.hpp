#pragma once

#include <vector>
#include <QGraphicsItem>

using namespace std;

class TrussWidget;
class Edge;

class Joint : public QGraphicsItem
{

    public:
        Joint(int plocator, double px, double py, double psupport);

        //Qt-Graphicsitem-Funktionen überschreiben
        QRectF boundingRect() const override;   //Wie groß ist der Knoten?
        QPainterPath shape() const override;    //Welche Hitbox hat der Knoten
        void paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; //Wie soll der Knoten gemalt werden

        virtual int type() const override {
            return m_type;
        }

        //Konsolenausgabe mit allen Knoteninformationen für Tests
        void print();

        //get' and  set's
        double get_support();
        void set_support(double psupport);
        int get_locator();
        void set_locator(int plocator);        
        void set_edges(Edge* add_edge);
        vector<Edge*>& get_edges();
        void remove_edge(Edge* edge);


    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);//override

    private:
        int m_type = 700;

        int locator;
        const int default_reserved_adjacent_edges = 5;
        vector<Edge* > attached_edges;
        double support;
};
// FUNKTIONEN ZUM ÄNDERN DER POSITION SIND SCHON VORHANDEN
