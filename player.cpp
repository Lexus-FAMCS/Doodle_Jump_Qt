
#include "player.h"
#include <QDebug>
double eps = 1e-6;

Player::Player(QPixmap image, QPointF position, double speed, double boost, double left_edge, double right_edge) :
    Creature(image, position, speed),
    v_dir(vertical_direction::UP),
    h_dir(horizontal_direction::NONE),
    left_edge(left_edge),
    right_edge(right_edge),
    boost(boost),
    height_of_fly(0)
//    prev_h_dir(horizontal_direction::NONE)
{
    calculateHeightOfFly();
}

void Player::setGraphic(QGraphicsPixmapItem* graphic) {
    Creature::setGraphic(graphic);
}

void Player::setVDirection(vertical_direction v_dir)
{
    this->v_dir = v_dir;
}

void Player::changeSpeed()
{
    if (v_dir == vertical_direction::UP) {
        speed -= boost;
    } else {
        speed += boost;
    }
}

horizontal_direction Player::getHDirection() const
{
    return h_dir;
}

void Player::setHDirection(horizontal_direction h_dir)
{
    this->h_dir = h_dir;
}

//void Player::setMaxHeight(double max_height)
//{
//    this->max_height = max_height;
//}

//double Player::getMaxHeight() const
//{
//    return max_height;
//}

double Player::getLeftEdge() const
{
    return left_edge;
}

void Player::setLeftEdge(double left_edge)
{
    this->left_edge = left_edge;
}

void Player::setRightEdge(double right_edge)
{
    this->right_edge = right_edge;
}

double Player::getRightEdge() const
{
    return right_edge;
}

vertical_direction Player::getVDirection() const {
    return v_dir;
}

void Player::setBoost(double boost) {
    this->boost = boost;
}

double Player::getBoost() const {
    return boost;
}

void Player::calculateHeightOfFly() {
    double speed = this->speed;
    while (speed > eps) {
        height_of_fly += speed;
        speed -= boost;
    }
}

double Player::getHeightOfFly() {
    return height_of_fly;
}
