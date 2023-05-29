
#ifndef BULLET_H
#define BULLET_H

#include "creature.h"

#include <QPixmap>
#include <QPointF>

class Bullet : public Creature
{
public:
    Bullet(QPixmap, QPointF, double);
    void setGraphic(QGraphicsPixmapItem *graphic);

};

#endif // BULLET_H
