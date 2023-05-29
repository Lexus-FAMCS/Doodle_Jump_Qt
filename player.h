
#ifndef PLAYER_H
#define PLAYER_H

#include "creature.h"

#include <utility>

extern double eps;

enum class vertical_direction {
    UP,
    DOWN
};

enum class horizontal_direction {
    LEFT,
    RIGHT,
    NONE
};

class Player : public Creature
{
public:
    Player(QPixmap, QPointF, double, double = 0, double = 0, double = 0);
    void setGraphic(QGraphicsPixmapItem*) override;
    void changeSpeed();
    vertical_direction getVDirection() const;
    void setVDirection(vertical_direction);
    horizontal_direction getHDirection() const;
    void setHDirection(horizontal_direction);
//    void setMaxHeight(double);
//    double getMaxHeight() const;
    double getLeftEdge() const;
    void setLeftEdge(double);
    double getRightEdge() const;
    void setRightEdge(double);
    void setBoost(double);
    double getBoost() const;
    void calculateHeightOfFly();
    double getHeightOfFly();
//    horizontal_direction getPrevHDirection() const;
//    void setPrevHDirection(horizontal_direction);
//    void setMoveBtnPressed(std::pair<bool>&);
//    std::pair<bool> getMoveBtnPressed() const;
    std::pair<bool, bool> moveBtnPressed;

private:
    vertical_direction v_dir;
    horizontal_direction h_dir;
//    double max_height;

    double boost;
    double left_edge;
    double right_edge;
    double height_of_fly;
//    horizontal_direction prev_h_dir;
};

#endif // PLAYER_H
