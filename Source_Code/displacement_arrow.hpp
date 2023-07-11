#pragma once
#include <QGraphicsItem>

class Displacement_arrow : public QGraphicsItem
{
public:
  Displacement_arrow(double x1, double y1, double x2, double y2);
  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
  double x1,x2,y1,y2;
};
