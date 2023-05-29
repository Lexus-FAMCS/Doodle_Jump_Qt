
#include "abstractcontroller.h"

AbstractController::AbstractController(QWidget *parent, int width, int height)
    : QWidget{parent},
    width(width),
    height(height)
{

}

int AbstractController::getWidth() {
    return width;
}

int AbstractController::getHeight() {
    return height;
}

