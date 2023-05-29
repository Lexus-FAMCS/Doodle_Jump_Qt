
#ifndef CREATURE_H
#define CREATURE_H

#include <QPointF>
#include <QPixmap>
#include <QGraphicsPixmapItem>

class Creature
{
public:
    Creature(QPixmap, QPointF, double);
    virtual ~Creature();
    virtual void setGraphic(QGraphicsPixmapItem*) = 0;
    QGraphicsPixmapItem* getGraphic() const;
    double getHeight() const;
    double getSpeed() const;
    void setSpeed(double);
    QPointF getPos() const;
    QPixmap getImage() const;
    void setImage(QPixmap);
    void setPos(QPointF);

protected:
    double height;
    double speed;
    QPointF position;
    QPixmap image;
    QGraphicsPixmapItem* graphic;
};

#endif // CREATURE_H
