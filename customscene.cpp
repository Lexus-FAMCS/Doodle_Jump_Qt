
#include "customscene.h"

#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>


CustomScene::CustomScene(QObject *parent)
    : QGraphicsScene{parent}
{

}

CustomScene::~CustomScene()
{

}

void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalMoveCoordinate(event->scenePos());
}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    emit signalPressCoordinate(event->scenePos());
}

void CustomScene::keyPressEvent(QKeyEvent *event)
{
    emit signalPressKey(event);
}

void CustomScene::keyReleaseEvent(QKeyEvent *event)
{
    emit signalReleaseEvent(event);
}
