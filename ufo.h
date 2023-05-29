
#ifndef UFO_H
#define UFO_H

#include "enemy.h"

class UFO : public Enemy
{
public:
    UFO(QPixmap, QPointF, double);
};

#endif // UFO_H
