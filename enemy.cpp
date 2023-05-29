
#include "enemy.h"

Enemy::Enemy(QPixmap image, QPointF position, double speed):
    Creature(image, position, speed)
{

}

void Enemy::setGraphic(QGraphicsPixmapItem* graphic) {
    Creature::setGraphic(graphic);
}

