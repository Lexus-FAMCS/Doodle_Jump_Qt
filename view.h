
#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>

#include "abstractcontroller.h"

class View
{
public:
    View(AbstractController*);
    void load_menu();
    void load_options();
    void load_game();
    void pause();

    void delete_menu();
    void delete_options();
    void delete_game();
    void end_of_pause();

    void show_menu(QPainterPath = QPainterPath(), QColor = QColor(240, 0, 0, 50));
    void show_game();

private:
    CustomScene* scene;
    AbstractController* ctr;
    Model* model;
    QGraphicsView* view;

};

#endif // VIEW_H
