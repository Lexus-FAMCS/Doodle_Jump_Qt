
#ifndef ENEMY_H
#define ENEMY_H

#include "creature.h"



class Enemy : public Creature
{
public:
    Enemy(QPixmap, QPointF, double);
    void setGraphic(QGraphicsPixmapItem*) override;
};

#endif // ENEMY_H
