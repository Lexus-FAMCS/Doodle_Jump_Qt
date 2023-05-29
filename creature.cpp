
#include "creature.h"
#include <QDebug>

Creature::Creature(QPixmap image, QPointF position, double speed) :
    image(image),
    position(position),
    speed(speed),
    graphic(nullptr)
{

}

Creature::~Creature()
{
    delete graphic;
}

QGraphicsPixmapItem *Creature::getGraphic() const
{
    return graphic;
}

void Creature::setGraphic(QGraphicsPixmapItem* graphic) {
    delete this->graphic;
    this->graphic = graphic;
}

double Creature::getHeight() const {
    return height;
}

double Creature::getSpeed() const {
    return speed;
}

QPointF Creature::getPos() const {
    return position;
}

void Creature::setSpeed(double speed) {
    this->speed = speed;
}

QPixmap Creature::getImage() const {
    return image;
}

void Creature::setImage(QPixmap image)
{
    this->image = image;
}

void Creature::setPos(QPointF position)
{
    this->position = position;
}


