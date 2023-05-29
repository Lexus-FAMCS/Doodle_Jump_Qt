
#include "menu_ufo.h"

Menu_UFO::Menu_UFO(QPixmap image, QPointF position, double speed, ufo_location loc, double radius):
    UFO(image, position, speed),
    loc(loc),
    radius(radius),
    center(position)
{

}

void Menu_UFO::setLoc(ufo_location loc) {
    this->loc = loc;
}

void Menu_UFO::setCenter(QPointF center) {
    this->center = center;
}

void Menu_UFO::setRadius(double radius) {
    this->radius = radius;
}

ufo_location Menu_UFO::getLoc() const {
    return loc;
}

QPointF Menu_UFO::getCenter() const {
    return center;
}

double Menu_UFO::getRadius() const {
    return radius;
}

