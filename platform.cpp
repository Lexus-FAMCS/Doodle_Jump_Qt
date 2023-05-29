#include "platform.h"

Platform::Platform(QPixmap image, QPointF position, double speed, platformType type):
    Creature(image, position, speed),
    type(type)
{

}

void Platform::setGraphic(QGraphicsPixmapItem* graphic) {
    Creature::setGraphic(graphic);
}

platformType Platform::getType() const
{
    return type;
}

