
#include "view.h"
#include <QDebug>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QBrush>

View::View(AbstractController* ctr):
    scene(ctr->getScene()),
    view(new QGraphicsView(ctr)),
    ctr(ctr),
    model(ctr->getModel())
{
    view->setScene(scene);
    scene->setSceneRect(0, 0, ctr->getWidth() - 2, ctr->getHeight() - 2);
    view->resize(ctr->getWidth(), ctr->getHeight());
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void View::show_menu(QPainterPath path, QColor light)
{
    Player* player = model->getPlayer();
    Platform* platform = model->getMenuPlatform();
    Menu_UFO* ufo = model->getMenuUFO();

    scene->removeItem(player->getGraphic());
    player->setGraphic(scene->addPixmap(player->getImage()));
    scene->removeItem(platform->getGraphic());
    platform->setGraphic(scene->addPixmap(platform->getImage()));
    player->getGraphic()->setOffset(player->getPos().x(), player->getPos().y());
    platform->getGraphic()->setOffset(platform->getPos().x(), platform->getPos().y());

    scene->removeItem(model->getRay());
    model->setRay(scene->addPath(path, Qt::NoPen, QBrush(light)));
    scene->removeItem(ufo->getGraphic());
    ufo->setGraphic(scene->addPixmap(ufo->getImage()));
    ufo->getGraphic()->setOffset(ufo->getPos());
}

void View::show_game() {
    auto platforms = model->getPlatforms();
    int size = platforms.size();
    for (int i = 0; i < size; ++i) {
        scene->removeItem(platforms[i]->getGraphic());
        platforms[i]->setGraphic(scene->addPixmap(platforms[i]->getImage()));
        platforms[i]->getGraphic()->setOffset(platforms[i]->getPos());
    }
    Player* player = model->getGamePlayer();
    scene->removeItem(player->getGraphic());
    player->setGraphic(scene->addPixmap(player->getImage()));
    player->getGraphic()->setOffset(player->getPos());
    scene->removeItem(model->getPauseBar());
    scene->addItem(model->getPauseBar());
    scene->removeItem(model->getScoreBoard());
    scene->addItem(model->getScoreBoard());
}

void View::load_menu()
{
    scene->addItem(model->getBackground());

    scene->addItem(model->getGameName());

    if (model->getOptions()) {
        scene->addItem(model->getOptions());
    } else {
        model->setOptions(scene->addPixmap(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/settings.png")));
        model->setOptionsPos(QPointF(630, 840));
        model->getOptions()->setOffset(model->getOptionsPos());
    }
    scene->addItem(model->getCustomeIcon());
    scene->addItem(model->getCustomeText());

    scene->addItem(model->getText());

    if (model->getPlayEllipse()) {
        scene->addItem(model->getPlayEllipse());
    } else {
        model->setPlayEllipse(scene->addEllipse(285, 253, 200, 100, QPen(Qt::black, 2), QBrush(QColor(238, 232, 170))));
        scene->addItem(model->getPlayEllipse());
    }

    scene->addItem(model->getPlayText());

    if (model->getBug_1()) {
        scene->addItem(model->getBug_1());
    } else {
        model->setBug_1(scene->addPixmap(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/bug_1.png")));
    }
    model->getBug_1()->setOffset(100, 50);

    if (model->getBug_2()) {
        scene->addItem(model->getBug_2());
    } else {
        model->setBug_2(scene->addPixmap(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/bug_2.png")));
    }
    model->getBug_2()->setOffset(200, 800);

    if (model->getBug_3()) {
        scene->addItem(model->getBug_3());
    } else {
        model->setBug_3(scene->addPixmap(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/bug_3.png")));
    }
    model->getBug_3()->setOffset(50, 350);

    if (model->getBug_4()) {
        scene->addItem(model->getBug_4());
    } else {
        model->setBug_4(scene->addPixmap(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/bug_4.png")));
    }
    model->getBug_4()->setOffset(500, 200);

    if (model->getBug_5()) {
        scene->addItem(model->getBug_5());
    } else {
        model->setBug_5(scene->addPixmap(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/bug_5.png")));
    }
    model->getBug_5()->setOffset(300, 600);

    ctr->getMenuTimer()->setInterval(6);
    ctr->getMenuTimer()->start();
}

void View::delete_menu() {
    scene->removeItem(model->getPlayer()->getGraphic());
    scene->removeItem(model->getMenuPlatform()->getGraphic());
    scene->removeItem(model->getMenuUFO()->getGraphic());
    scene->removeItem(model->getBackground());
    scene->removeItem(model->getGameName());
    scene->removeItem(model->getOptions());
    scene->removeItem(model->getText());
    scene->removeItem(model->getPlayEllipse());
    scene->removeItem(model->getPlayText());
    scene->removeItem(model->getBug_1());
    scene->removeItem(model->getBug_2());
    scene->removeItem(model->getBug_3());
    scene->removeItem(model->getBug_4());
    scene->removeItem(model->getBug_5());
    scene->removeItem(model->getRay());
    scene->removeItem(model->getCustomeIcon());
    scene->removeItem(model->getCustomeText());
    ctr->getMenuTimer()->stop();
}


void View::delete_options()
{
    scene->removeItem(model->getBackground());
    scene->removeItem(model->getMenuEllipse());
    scene->removeItem(model->getMenuText());
    scene->removeItem(model->getSoundText());
    scene->removeItem(model->getSoundON());
    scene->removeItem(model->getSoundOFF());
}

void View::load_options()
{

    scene->addItem(model->getBackground());

    scene->addItem(model->getSoundText());
    scene->addItem(model->getSoundON());
    scene->addItem(model->getSoundOFF());

    if (model->getMenuEllipse()) {
        scene->addItem(model->getMenuEllipse());
    } else {
        model->setMenuEllipse(scene->addEllipse(520, 800, 200, 100, QPen(Qt::black, 2), QBrush(QColor(238, 232, 170))));
    }

    scene->addItem(model->getMenuText());
    ctr->setIsMenuOn(true);
}

void View::load_game() {
    qDebug() << "Load game";
    if (model->getBackground()) {
        scene->addItem(model->getBackground());
    } else {
        model->setBackdround(scene->addPixmap(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/background.jpg")));
    }
    scene->addItem(model->getScoreBoard());
    scene->addItem(model->getPauseBar());
    scene->addItem(model->getPauseIcon());
    //    Player* player = model->getGamePlayer();
//    model->setPlatforms(std::vector<Platform*>{
//        new Platform(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/green_platform.png"), QPointF(320, 730), 0, platformType::Whole),
//        new Platform(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/green_platform.png"), QPointF(320, 670), 0, platformType::Whole),
//        new Platform(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/green_platform.png"), QPointF(50, 500), 0, platformType::Whole),
//        new Platform(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/green_platform.png"), QPointF(500, 500), 0, platformType::Whole),
//        new Platform(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/green_platform.png"), QPointF(410, 200), 0, platformType::Whole)
//    });
    ctr->generateStartPlatforms();
    Platform* platform;
    auto platforms = model->getPlatforms();
    int size = platforms.size();
    for (int i = 0; i < size; ++i) {
        platform = platforms[i];
        platform->setGraphic(scene->addPixmap(platform->getImage()));
        platform->getGraphic()->setOffset(platform->getPos().x(), platform->getPos().y());
        platform->getGraphic()->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
    }
    ctr->setIsMenuOn(false);

    ctr->getPlayTimer()->setInterval(5);
    ctr->getPlayTimer()->start();
    ctr->getHorizontalTimer()->setInterval(10);
    ctr->getHorizontalTimer()->start();
}

void View::pause()
{
    ctr->getPlayTimer()->stop();
    ctr->getScoreTimer()->stop();
    ctr->getMoveTimer()->stop();
    ctr->getHorizontalTimer()->stop();
    scene->addItem(model->getPauseBackground());
    scene->addItem(model->getBug_2());
    model->getBug_2()->setOffset(100, 200);
    scene->addItem(model->getBug_4());
    model->getBug_4()->setOffset(600, 550);
    scene->addItem(model->getBug_5());
    model->getBug_5()->setOffset(230, 280);
    scene->addItem(model->getPauseRay());
    model->getPauseRay()->setPos(107, -11);
    scene->addItem(model->getMenuUFO()->getGraphic());
    model->getMenuUFO()->getGraphic()->setOffset(550, 50);
    scene->addItem(model->getPauseGameName());
    scene->addItem(model->getPauseText());
    scene->addItem(model->getPauseResumeEllipse());
    scene->addItem(model->getPauseResume());
}

void View::end_of_pause()
{
    scene->removeItem(model->getPauseBackground());
    scene->removeItem(model->getMenuUFO()->getGraphic());
    scene->removeItem(model->getBug_2());
    scene->removeItem(model->getBug_4());
    scene->removeItem(model->getBug_5());
    scene->removeItem(model->getPauseRay());
    scene->removeItem(model->getPauseGameName());
    scene->removeItem(model->getPauseText());
    scene->removeItem(model->getPauseResume());
    scene->removeItem(model->getPauseResumeEllipse());
    ctr->getPlayTimer()->start();
    ctr->getScoreTimer()->start();
    ctr->getMoveTimer()->start();
    ctr->getHorizontalTimer()->start();
}

void View::delete_game()
{
    qDebug() << "Delete game";
    scene->removeItem(model->getBackground());
    scene->removeItem(model->getGamePlayer()->getGraphic());
    scene->removeItem(model->getScoreBoard());
    scene->removeItem(model->getPauseBar());
    scene->removeItem(model->getPauseIcon());
    auto& platforms = model->getPlatforms();
    int size = platforms.size();
    for(int i = 0; i < size; ++i) {
        scene->removeItem(platforms[i]->getGraphic());
        delete platforms[i];
    }
    platforms.clear();
    ctr->getPlayTimer()->stop();
    ctr->getHorizontalTimer()->stop();
    ctr->getScoreTimer()->stop();
}

