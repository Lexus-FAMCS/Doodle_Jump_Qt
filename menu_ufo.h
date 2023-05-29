
#ifndef MENU_UFO_H
#define MENU_UFO_H

#include "ufo.h"

enum class ufo_location {
    AboveCenter,
    UnderCenter
};

class Menu_UFO : public UFO
{
public:
    Menu_UFO(QPixmap, QPointF, double, ufo_location = ufo_location::AboveCenter, double = 0);

    void setLoc(ufo_location);
    void setCenter(QPointF);
    void setRadius(double);

    ufo_location getLoc() const;
    QPointF getCenter() const;
    double getRadius() const;

private:
    //for menu ufo
    ufo_location loc;
    QPointF center;
    double radius;
};

#endif // MENU_UFO_H
