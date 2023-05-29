
#ifndef CHARACTERCHOICE_H
#define CHARACTERCHOICE_H

#include "customscene.h"
#include "model.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QGraphicsView>
#include <QPushButton>
#include <QPainterPath>

class CharacterChoice : public QWidget
{
    Q_OBJECT
public:
    CharacterChoice(Model*, QWidget *parent = nullptr, int = 630, int = 280);
    void drawChoice();
    void changeImages();

signals:
    void changeImage();
private slots:
    void slotMouseMove(QPointF);
    void slotMousePress(QPointF);

private:
    CustomScene* scene;
    QGraphicsView* view;
    Model* model;
    QVBoxLayout* v_layout;
    QHBoxLayout* h_layout;
    QPushButton* close;
    QVector<QGraphicsPathItem*> items;
    QVector<QGraphicsPixmapItem*> images;
    int choice_pos;
//    QPainterPath* rect_1;
};

#endif // CHARACTERCHOICE_H
