
#include "characterchoice.h"

#include <qDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QPen>
#include <QBrush>

CharacterChoice::CharacterChoice(Model* model, QWidget *parent, int width, int height)
    : QWidget{parent, Qt::Window},
    scene(new CustomScene(this)),
    view(new QGraphicsView(this)),
    close(new QPushButton(this)),
    v_layout(new QVBoxLayout(this)),
    h_layout(new QHBoxLayout(this)),
    choice_pos(0),
    model(model)
//    rect_1(new QPainterPath)
{
    setFixedSize(width, height);
    view->setMouseTracking(true);
    view->setScene(scene);
    //    scene->setSceneRect(0, 0, width - 2, height - 2);
    scene->setSceneRect(0, 0, width, height);
    view->resize(width, height - 70);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene->addPixmap(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/background.jpg"));
    QPainterPath path;
    path.addRoundedRect(27, 30, 172, 148, 50, 50);
    items.push_back(scene->addPath(path, QPen(), choice_pos == 0 ?  QColor(211, 211, 211, 200) : QColor(255, 222, 173, 200)));
    images.push_back(scene->addPixmap(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/ninja_doodler.png")));
    images[0]->setOffset(50, 50);
    path.clear();

    path.addRoundedRect(229, 30, 172, 148, 50, 50);
    items.push_back(scene->addPath(path, QPen(), choice_pos == 1 ?  QColor(211, 211, 211, 200) : QColor(255, 222, 173, 200)));
    images.push_back(scene->addPixmap(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/bunny_doodler.png")));
    images[1]->setOffset(252, 50);
    path.clear();

    path.addRoundedRect(431, 30, 172, 148, 50, 50);
    items.push_back(scene->addPath(path, QPen(), choice_pos == 2 ?  QColor(211, 211, 211, 200) : QColor(255, 222, 173, 200)));
    images.push_back(scene->addPixmap(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/samurai_doodler.png")));
    images[2]->setOffset(458, 48);
    path.clear();

    setWindowTitle("Choice of character");
    h_layout->addStretch();
    h_layout->addWidget(close);
    h_layout->addStretch();

    v_layout->addStretch(height - 50);
    v_layout->addLayout(h_layout);
    //    v_layout->addStretch(5);
    setLayout(v_layout);

    close->setMinimumHeight(43);
    close->setMaximumWidth(180);
    close->setMinimumWidth(180);
    close->setText("&Close");

    connect(scene, &CustomScene::signalMoveCoordinate, this, &CharacterChoice::slotMouseMove);
    connect(scene, &CustomScene::signalPressCoordinate, this, &CharacterChoice::slotMousePress);
    connect(close, &QPushButton::clicked, this, &QWidget::close);
}

void CharacterChoice::slotMouseMove(QPointF pos)
{
    int size = items.size();
    for (int i = 0; i < size; ++i) {
        QRectF rect = QRectF(items[i]->boundingRect().x() + 0.5, items[i]->boundingRect().y() + 0.5,
                             items[i]->boundingRect().width(), items[i]->boundingRect().height());
        //        qDebug() << rect.x() << rect.y();
        if (pos.x() >= rect.x() && pos.x() <= rect.x() + rect.width() &&
            pos.y() >= rect.y() && pos.y() <= rect.y() + rect.height()) {
            scene->removeItem(images[i]);
            scene->removeItem(items[i]);
            delete items[i];
            QPainterPath path;
            path.addRoundedRect(rect.x(), rect.y(), rect.width() - 1, rect.height() - 1, 50, 50);
            items[i] = scene->addPath(path , QPen(), QBrush(i == choice_pos ?  QColor(211, 211, 211) : QColor(255, 222, 173)));
            scene->addItem(images[i]);
        } else {
            scene->removeItem(images[i]);
            scene->removeItem(items[i]);
            delete items[i];
            QPainterPath path;
            path.addRoundedRect(rect.x(), rect.y(), rect.width() - 1, rect.height() - 1, 50, 50);
            items[i] = scene->addPath(path , QPen(), QBrush(i == choice_pos ? QColor(211, 211, 211, 200) : QColor(255, 222, 173, 200)));

            scene->addItem(images[i]);
        }
    }
}

void CharacterChoice::slotMousePress(QPointF pos)
{
    int size = items.size();
    for (int i = 0; i < size; ++i) {
        QRectF rect = QRectF(items[i]->boundingRect().x() + 0.5, items[i]->boundingRect().y() + 0.5,
                             items[i]->boundingRect().width(), items[i]->boundingRect().height());
        if (pos.x() >= rect.x() && pos.x() <= rect.x() + rect.width() &&
            pos.y() >= rect.y() && pos.y() <= rect.y() + rect.height()) {
            choice_pos = i;
            changeImages();
            drawChoice();
        }
    }
}

void CharacterChoice::drawChoice()
{
    int size = items.size();
    for (int i = 0; i < size; ++i) {
        QRectF rect = QRectF(items[i]->boundingRect().x() + 0.5, items[i]->boundingRect().y() + 0.5,
                             items[i]->boundingRect().width(), items[i]->boundingRect().height());
        scene->removeItem(images[i]);
        scene->removeItem(items[i]);
        delete items[i];
        QPainterPath path;
        path.addRoundedRect(rect.x(), rect.y(), rect.width() - 1, rect.height() - 1, 50, 50);
        items[i] = scene->addPath(path , QPen(), QBrush(i == choice_pos ?  QColor(211, 211, 211) : QColor(255, 222, 173)));
        scene->addItem(images[i]);
    }
}

void CharacterChoice::changeImages()
{
    qDebug() << "changeImage";
    switch(choice_pos) {
    case 0:
        model->setImage(new QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/ninja_doodler.png"));
        model->setReverseImage(new QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/ninja_doodler_to_left.png"));
        model->setLeftEdgeImage(26);
        model->setRightEdgeImage(86);
        model->setLeftEdgeReverseImage(35);
        model->setRightEdgeReverseImage(106);
        qDebug() << "image 1";
        break;
    case 1:
        model->setImage(new QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/bunny_doodler.png"));
        model->setReverseImage(new QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/bunny_doodler_to_left.png"));
        model->setLeftEdgeImage(23);
        model->setRightEdgeImage(88);
        model->setLeftEdgeReverseImage(37);
        model->setRightEdgeReverseImage(101);
        qDebug() << "image 2";
        break;
    case 2:
        model->setImage(new QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/samurai_doodler.png"));
        model->setReverseImage(new QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/samurai_doodler_to_left.png"));
        model->setLeftEdgeImage(14);
        model->setRightEdgeImage(85);
        model->setLeftEdgeReverseImage(37);
        model->setRightEdgeReverseImage(104);
        qDebug() << "image 3";
        break;
    default:
        model->setImage(new QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/ninja_doodler.png"));
        model->setReverseImage(new QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/ninja_doodler_to_left.png"));
        model->setLeftEdgeImage(26);
        model->setRightEdgeImage(86);
        model->setLeftEdgeReverseImage(35);
        model->setRightEdgeReverseImage(106);
        qDebug() << "image 1";
    }
    emit changeImage();
}
