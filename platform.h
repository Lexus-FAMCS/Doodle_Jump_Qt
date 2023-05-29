
#ifndef PLATFORM_H
#define PLATFORM_H

#include "creature.h"

enum class platformType {
    Whole,
    Broken
};

class Platform : public Creature
{
public:
    Platform(QPixmap, QPointF, double, platformType);
    void setGraphic(QGraphicsPixmapItem*) override;
    platformType getType() const;

private:
    platformType type;
};

#endif // PLATFORM_H
