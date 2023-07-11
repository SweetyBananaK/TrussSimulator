#ifndef MYSCENE_H
#define MYSCENE_H
#include <QGraphicsScene>
#include <QContextMenuEvent>
#include <QMenu>


class myScene : public QGraphicsScene
{
    Q_OBJECT

public:
    myScene(QObject *parent);
    ~myScene();
    void set_Point(QPointF P);
    void createActions();
    QPointF get_Point();
    QMenu* menu;

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

signals:
    void sendSignals();

private:
    QPointF Point;
};

#endif // MYSCENE_H
