
#include "bullet.h"

Bullet::Bullet(QPixmap image, QPointF position, double speed):
    Creature(image, position, speed)
{

}

void Bullet::setGraphic(QGraphicsPixmapItem *graphic) {
    Creature::setGraphic(graphic);
}

