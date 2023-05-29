#include "controller.h"
#include "platform.h"
#include <ctime>

#include <QDebug>
#include <QTimerEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QPainter>
#include <cmath>
#include <Windows.h>

Controller::Controller(QWidget *parent)
    : AbstractController(parent),
    menu_timer(new QTimer(this)),
    play_timer(new QTimer(this)),
    hrz_direction_timer(new QTimer(this)),
    move_timer(new QTimer(this)),
    score_timer(new QTimer(this)),
    scene(new CustomScene(this)),
    m_player_2(new QMediaPlayer(this)),
    m_player_1(new QMediaPlayer(this)),
//    m_playlist(new QMediaPlaylist(m_player)),
    space(0),
    isSoundOn(false),
    level(0),
    aim_score(0),
    curr_score(0),
    isMenuOn(false)
{
    setFixedSize(getWidth(), getHeight());

    score_timer->setInterval(2);

    /*m_player->setPlaylist(m_playlist);
    m_playlist->addMedia(QUrl("qrc:/sounds/C:/Users/lesha/Desktop/Doodle Jump/Sounds/jump.wav"));
    m_playlist->addMedia(QUrl("qrc:/sounds/C:/Users/lesha/Desktop/Doodle Jump/Sounds/platform_broke.mp3"));
    m_playlist->setCurrentIndex(0);
    m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    m_player->setVolume(90);*/
    //    m_player->play();

        m_player_1->setMedia(QUrl::fromLocalFile("C:/Users/lesha/Desktop/Doodle Jump/Sounds/jump.wav"));
        m_player_1->setVolume(80);
        m_player_2->setMedia(QUrl::fromLocalFile("C:/Users/lesha/Desktop/Doodle Jump/Sounds/platform_broke.mp3"));
        m_player_2->setVolume(80);
//        player->play();

    model = new Model();
    view = new View(this);
    model->setPlayer(new Player(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/ninja_doodler.png"), QPointF(100, 580), 6.5, 0.0596));
    model->setMenuPlatform(new Platform(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/green_platform.png"), QPointF(100, 700), 0, platformType::Whole));
    model->setGamePlayer(new Player(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/ninja_doodler.png"), QPointF(rand() % width - 131 + 1, 910), 6.5, 0.0596, 26, 86));
    model->setMenuUFO(new Menu_UFO(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/UFO.png"), QPointF(440, 70), 0.56, ufo_location::UnderCenter, 100));
    model->setImage(new QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/ninja_doodler.png"));
    model->setReverseImage(new QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/ninja_doodler_to_left.png"));
    model->setLeftEdgeImage(26);
    model->setRightEdgeImage(86);
    model->setLeftEdgeReverseImage(35);
    model->setRightEdgeReverseImage(106);
    chr_change_window = new CharacterChoice(model, this);
    //    model->setEnemies(std::vector<Enemy*>{
    //        new UFO(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/UFO.png"), QPointF(440, 70), 0)
    //    });
    model->setBackdround(scene->addPixmap(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/background.jpg")));
    model->setPauseBackdround(new QGraphicsPixmapItem(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/transparent_background.png")));

    model->setPauseBar(scene->addPolygon(QPolygon(QVector<QPoint>{QPoint(0, 0), QPoint(width, 0), QPoint(width, 100), QPoint(0, 100)}), QPen(), QBrush(QColor(127, 255, 212, 120))));
    scene->removeItem(model->getPauseBar());

    model->setPauseGameName(new QGraphicsTextItem);
    QGraphicsTextItem* pause_game_name = model->getPauseGameName();
    pause_game_name->setPos(120, 350);
    pause_game_name->setFont(QFont("", 50, 5));
    pause_game_name->setHtml("<style>font-family:monaco</style>"
                             "<div style='color:#FF6347;'>doodle jump</div>");

    model->setPauseText(new QGraphicsTextItem);
    QGraphicsTextItem* pause_text = model->getPauseText();
    pause_text->setPos(290, 420);
    pause_text->setFont(QFont("", 50, 5));
    pause_text->setHtml("<style>font-family:monaco</style>"
                             "<div>paused</div>");

    model->setPauseResumeEllipse(new QGraphicsEllipseItem(430, 680, 270, 120));
    model->getPauseResumeEllipse()->setBrush(QBrush(QColor(238, 232, 170)));

    model->setPauseResume(new QGraphicsTextItem);
    QGraphicsTextItem* pause_resume = model->getPauseResume();
    pause_resume->setPos(461, 696);
    pause_resume->setFont(QFont("", 37, 4));
    pause_resume->setHtml("<style>font-family:monaco</style>"
                        "<div>resume</div>");

    model->setGameName(new QGraphicsTextItem);
    QGraphicsTextItem* game_name = model->getGameName();
    game_name->setPos(100, 100);
    game_name->setFont(QFont("Arial", 50, -1, true));
    game_name->setHtml("<div style='color:crimson;'>Doodle Jump</div>");

    model->setText(new QGraphicsTextItem);
    QGraphicsTextItem* text = model->getText();
    text->setPos(618, 920);
    //    text->setFont(QFont("Arial", 20, 5));
    text->setHtml("<style> div { font-family:aqua; font-size:29px; text-align: center;} </style>"
                  "<div style='color:black;'>options</div>");

    model->setCustomeText(new QGraphicsTextItem);
    QGraphicsTextItem* custome_text = model->getCustomeText();
    custome_text->setPos(464, 920);
    custome_text->setHtml("<style> div { font-family:aqua; font-size:29px; text-align: center;} </style>"
                          "<div style='color:black;'>customize</div>");

    model->setPlayText(new QGraphicsTextItem);
    QGraphicsTextItem* play_text = model->getPlayText();
    play_text->setPos(339, 270);
    //    play_text->setFont(QFont("Arial", 30, 5));
    play_text->setHtml("<style> div { font-family:aqua; font-size:45px; text-align: center;} </style>"
                       "<div style='color:black;'>Play</div>");

    model->setScoreBoard(0);
    auto* scoreboard = model->getScoreBoard();
    scoreboard->setFont(QFont("Arial", 25, 3));
    scoreboard->setPos(10, 20);

    model->setMenuText(new QGraphicsTextItem);
    auto* menu_text = model->getMenuText();
    menu_text->setPos(574, 822);
    //    menu_text->setFont(QFont("Arial", 20, 5));
    menu_text->setHtml("<style> div { font-family:aqua; font-size:34px; text-align: center;} </style>"
                       "<div style='color:black'>Menu</div>");

    model->setSoundText(new QGraphicsTextItem);
    auto* sound_text = model->getSoundText();
    sound_text->setPos(310, 90);
    //    sound_text->setFont(QFont("Aroma", 20, 5));
    sound_text->setHtml("<style> div { font-family:aqua; font-size:42px; text-align: center;} </style>"
                        "<div style='color:black;'>Sound</div>");

    model->setSoundON(new QGraphicsTextItem);
    //    model->setSoundON(scene->addText("", QFont()));
    //    scene->removeItem(model->getSoundON());
    auto* sound_on = model->getSoundON();
    sound_on->setPos(270, 150);
    //    sound_text->setFont(QFont("Aroma", 20, 5));
    sound_on->setHtml("<style> div { font-family:aqua; font-size:36px; text-align: center;} </style>"
                      "<div style='color:DarkGrey;'>On</div>");
    model->setSoundOFF(new QGraphicsTextItem);
    auto* sound_off = model->getSoundOFF();
    sound_off->setPos(410, 150);
    //    sound_text->setFont(QFont("Aroma", 20, 5));
    sound_off->setHtml("<style> div { font-family:aqua; font-size:36px; text-align: center;} </style>"
                       "<div style='color:DeepSkyBlue;'>Off</div>");

    model->setCustomeIcon(scene->addPixmap(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/customize.png")));
    model->getCustomeIcon()->setOffset(490, 840);

    model->setPauseIcon(scene->addPixmap(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/pause_icon.png")));
    scene->removeItem(model->getPauseIcon());
    model->getPauseIcon()->setOffset(700, 25);

    QPainterPath path;
    QPointF ufo_pos = model->getMenuUFO()->getPos();
    path.moveTo(QPointF(52, 100) + ufo_pos);
    path.lineTo(QPointF(114, 100) + ufo_pos);
    path.lineTo(QPointF(160, 265) + ufo_pos);
    for (double i = 0; i < 154; i += 0.3) {
        path.lineTo(QPointF(160, 265) + ufo_pos + QPointF(-i, 3 * sin((i * 7 * M_PI) / 154)));
    }

    path.lineTo(ufo_pos + QPointF(6, 265));
    path.lineTo(ufo_pos + QPointF(52, 100));
    model->setPauseRay(new QGraphicsPathItem(path));
    model->getPauseRay()->setBrush(QBrush(QColor(240, 0, 0, 170)));

    view->load_menu();

    //    connect_timers();

    connect(scene, &CustomScene::signalMoveCoordinate, this, &Controller::slotMove);
    connect(scene, &CustomScene::signalPressCoordinate, this, &Controller::slotPress);
    connect(scene, &CustomScene::signalPressKey, this, &Controller::slotKeyPress);
    connect(scene, &CustomScene::signalReleaseEvent, this, &Controller::slotKeyRelease);
    connect(menu_timer, &QTimer::timeout, this, &Controller::menuTimerTick);
    connect(play_timer, &QTimer::timeout, this, &Controller::playTimerTick);
    connect(hrz_direction_timer, &QTimer::timeout, this, &Controller::hrzDirectionTimerTick);
    connect(score_timer, &QTimer::timeout, this, &Controller::scoreTimerTick);
    connect(move_timer, &QTimer::timeout, this, &Controller::moveTimerTick);
    connect(chr_change_window, &CharacterChoice::changeImage, this, &Controller::slotChangeImage);
    connect(this, &Controller::customize, chr_change_window, &CharacterChoice::show);
}

Controller::~Controller()
{
}

void Controller::slotPress(QPointF pos)
{
    QPointF options_pos = model->getOptionsPos();
    auto* options = model->getOptions();
    if (menu_timer->isActive()) {
        auto customize_rect = model->getCustomeIcon()->boundingRect();
        if (pos.x() >= options_pos.x() && pos.x() <= options_pos.x() + options->boundingRect().width() &&
            pos.y() >= options_pos.y() && pos.y() <= options_pos.y() + options->boundingRect().height()) {
            qDebug() << "Load options";
            view->delete_menu();
            view->load_options();
        } else if (pos.x() >= customize_rect.x() && pos.x() <= customize_rect.x() + customize_rect.width() &&
                   pos.y() >= customize_rect.y() && pos.y() <= customize_rect.y() + customize_rect.height()) {
            emit customize();
        } else if ((pos.x() - 385) * (pos.x() - 385) / 10000 + (303 - pos.y()) * (303 - pos.y()) / 2500 <= 1) {
            qDebug() << "Game started";
            model->setPlayEllipse(scene->addEllipse(285, 253, 200, 100, QPen(Qt::black, 2), QBrush(QColor(238, 232, 170))));
            scene->removeItem(model->getPlayEllipse());
            //        model->setPlayText(new QGraphicsTextItem);
            //        auto* play_text = model->getPlayText();
            //        play_text->setPos(330, 270);
            //        play_text->setFont(QFont("Arial", 30, 5));
            //        play_text->setHtml("<div style='color:black;'>Play</div>");
            launch_game();
        }
    } else if (isMenuOn) {
        auto* sound_on = model->getSoundON();
        auto* sound_off = model->getSoundOFF();
        QPointF corner = sound_on->mapToScene(0, 0);
        double width = sound_on->boundingRect().width();//sound_on->mapToScene(sound_on->boundingRect().x() + sound_on->boundingRect().width(), 0);
        double height = sound_on->boundingRect().height();//sound_on->mapToScene(0, sound_on->boundingRect().y() + sound_on->boundingRect().height());
        if (pos.x() >= corner.x() && pos.x() <= corner.x() + width &&
            pos.y() >= corner.y() && pos.y() <= corner.y() + height) {
            qDebug() << "Switch sound" << isSoundOn;
            isSoundOn = 1 - isSoundOn;
            if (isSoundOn) {
                sound_on->setHtml("<style> div { font-family:aqua; font-size:36px; text-align: center;} </style>"
                                  "<div style='color:DeepSkyBlue;'>On</div>");

                sound_off->setHtml("<style> div { font-family:aqua; font-size:36px; text-align: center;} </style>"
                                   "<div style='color:DarkGrey;'>Off</div>");
            } else {
                sound_on->setHtml("<style> div { font-family:aqua; font-size:36px; text-align: center;} </style>"
                                  "<div style='color:DarkGrey;'>On</div>");

                sound_off->setHtml("<style> div { font-family:aqua; font-size:36px; text-align: center;} </style>"
                                   "<div style='color:DeepSkyBlue;'>Off</div>");
            }
        }

        corner = sound_off->mapToScene(0, 0);
        width = sound_off->boundingRect().width();//sound_on->mapToScene(sound_on->boundingRect().x() + sound_on->boundingRect().width(), 0);
        height = sound_off->boundingRect().height();//sound_on->mapToScene(0, sound_on->boundingRect().y() + sound_on->boundingRect().height());
        if (pos.x() >= corner.x() && pos.x() <= corner.x() + width &&
            pos.y() >= corner.y() && pos.y() <= corner.y() + height) {
            qDebug() << "Switch sound" << isSoundOn;
            isSoundOn = 1 - isSoundOn;
            if (isSoundOn) {
                sound_on->setHtml("<style> div { font-family:aqua; font-size:36px; text-align: center;} </style>"
                                  "<div style='color:DeepSkyBlue;'>On</div>");

                sound_off->setHtml("<style> div { font-family:aqua; font-size:36px; text-align: center;} </style>"
                                   "<div style='color:DarkGrey;'>Off</div>");
            } else {
                sound_on->setHtml("<style> div { font-family:aqua; font-size:36px; text-align: center;} </style>"
                                  "<div style='color:DarkGrey;'>On</div>");

                sound_off->setHtml("<style> div { font-family:aqua; font-size:36px; text-align: center;} </style>"
                                   "<div style='color:DeepSkyBlue;'>Off</div>");
            }
        }

        if ((pos.x() - 620) * (pos.x() - 620) / 10000 + (850 - pos.y()) * (850 - pos.y()) / 2500 <= 1) {
            qDebug() << "Delete options";
            view->delete_options();
            view->load_menu();
            return;
        }
    }
    else if (play_timer->isActive()){
        QGraphicsPixmapItem* pause_icon = model->getPauseIcon();
        if ((pos.x() >= pause_icon->offset().x() && pos.x() <= pause_icon->offset().x() + pause_icon->boundingRect().width()) &&
            (pos.y() >= pause_icon->offset().y() && pos.y() <= pause_icon->offset().y() + pause_icon->boundingRect().height())) {
            qDebug() << "Pause";
            view->pause();
        }
    } else {
        auto* resume_ell = model->getPauseResumeEllipse();
        if (pow(pos.x() - resume_ell->boundingRect().x() - resume_ell->boundingRect().width() / 2, 2) / pow(resume_ell->boundingRect().width() / 2, 2) +
                pow(pos.y() - resume_ell->boundingRect().y() - resume_ell->boundingRect().height() / 2, 2) / pow(resume_ell->boundingRect().height() / 2, 2) <= 1) {
            view->end_of_pause();
        }
    }
}

void Controller::slotMove(QPointF pos)
{
    QPointF options_pos = model->getOptionsPos();
    auto* options = model->getOptions();
    if (menu_timer->isActive()) {
        if (pos.x() >= options_pos.x() && pos.x() <= options_pos.x() + options->boundingRect().width() &&
            pos.y() >= options_pos.y() && pos.y() <= options_pos.y() + options->boundingRect().height()) {
            model->getText()->setHtml("<style> div { font-family:aqua; font-size:29px; text-align: center;} </style>"
                                      "<div style='color:#D2691E;'>options</div>");
        } else {
            model->getText()->setHtml("<style> div { font-family:aqua; font-size:29px; text-align: center;} </style>"
                                      "<div style='color:black;'>options</div>");
        }
        auto customize_rect = model->getCustomeIcon()->boundingRect();
        if (pos.x() >= customize_rect.x() && pos.x() <= customize_rect.x() + customize_rect.width() &&
            pos.y() >= customize_rect.y() && pos.y() <= customize_rect.y() + customize_rect.height()) {
            model->getCustomeText()->setHtml("<style> div { font-family:aqua; font-size:29px; text-align: center;} </style>"
                                             "<div style='color:#D2691E;'>customize</div>");
        } else {
            model->getCustomeText()->setHtml("<style> div { font-family:aqua; font-size:29px; text-align: center;} </style>"
                                             "<div style='color:black;'>customize</div>");
        }

        scene->removeItem(model->getPlayEllipse());
        scene->removeItem(model->getPlayText());
        if ((pos.x() - 385) * (pos.x() - 385) / 10000 + (303 - pos.y()) * (303 - pos.y()) / 2500 <= 1) {
            model->setPlayEllipse(scene->addEllipse(275, 245, 220, 116, QPen(Qt::black, 2), QBrush(QColor(238, 232, 170))));
            model->setPlayText(new QGraphicsTextItem);
            auto* play_text  = model->getPlayText();
            play_text ->setPos(334, 263);
            //            play_text ->setFont(QFont("Arial", 40, 10));
            play_text ->setHtml("<style> div { font-family:aqua; font-size:55px; text-align: center;} </style>"
                               "<div style='color:black;'>Play</div>");
            scene->addItem(play_text);
        } else {
            model->setPlayEllipse(scene->addEllipse(285, 253, 200, 100, QPen(Qt::black, 2), QBrush(QColor(238, 232, 170))));
            model->setPlayText(new QGraphicsTextItem);
            auto* play_text = model->getPlayText();
            play_text->setPos(339, 270);
            //            play_text->setFont(QFont("Arial", 30, 5));
            play_text->setHtml("<style> div { font-family:aqua; font-size:45px; text-align: center;} </style>"
                               "<div style='color:black;'>Play</div>");
            scene->addItem(play_text);
        }
    } else if (isMenuOn) {
        scene->removeItem(model->getMenuEllipse());
        scene->removeItem(model->getMenuText());
        if ((pos.x() - 620) * (pos.x() - 620) / 10000 + (850 - pos.y()) * (850 - pos.y()) / 2500 <= 1) {
            model->setMenuEllipse(scene->addEllipse(510, 792, 220, 116, QPen(Qt::black, 2), QBrush(QColor(238, 232, 170))));
            model->setMenuText(new QGraphicsTextItem);
            auto* menu_text = model->getMenuText();
            menu_text->setPos(564, 814);
            //            menu_text->setFont(QFont("Arial", 30, 10));
            menu_text->setHtml("<style> div { font-family:aqua; font-size:44px; text-align: center;} </style>"
                               "<div style='color:black;'>Menu</div>");
            scene->addItem(model->getMenuText());
        } else {
            model->setMenuEllipse(scene->addEllipse(520, 800, 200, 100, QPen(Qt::black, 2), QBrush(QColor(238, 232, 170))));
            model->setMenuText(new QGraphicsTextItem);
            auto* menu_text  = model->getMenuText();
            menu_text ->setPos(574, 822);
            //            menu_text ->setFont(QFont("Arial", 20, 5));
            menu_text ->setHtml("<style> div { font-family:aqua; font-size:34px; text-align: center;} </style>"
                               "<div style='color:black;'>Menu</div>");
            scene->addItem(model->getMenuText());
        }
    } else if (!play_timer->isActive()) {
        auto* resume_ell = model->getPauseResumeEllipse();
        if (pow(pos.x() - resume_ell->boundingRect().x() - resume_ell->boundingRect().width() / 2, 2) / pow(resume_ell->boundingRect().width() / 2, 2) +
                pow(pos.y() - resume_ell->boundingRect().y() - resume_ell->boundingRect().height() / 2, 2) / pow(resume_ell->boundingRect().height() / 2, 2) <= 1) {
            scene->removeItem(model->getPauseResumeEllipse());
            scene->removeItem(model->getPauseResume());
            model->setPauseResumeEllipse(scene->addEllipse(420, 670, 290, 140));
            model->getPauseResumeEllipse()->setBrush(QBrush(QColor(238, 232, 170)));
            QGraphicsTextItem* pause_resume = model->getPauseResume();
            pause_resume->setPos(450, 686);
            pause_resume->setHtml("<style> div {  font-size:70px; font-family:monaco;} </style>"
                                  "<div>resume</div>");
            scene->addItem(pause_resume);
        } else {
            scene->removeItem(model->getPauseResumeEllipse());
            scene->removeItem(model->getPauseResume());
            model->setPauseResumeEllipse(scene->addEllipse(430, 680, 270, 120));
            model->getPauseResumeEllipse()->setBrush(QBrush(QColor(238, 232, 170)));
            QGraphicsTextItem* pause_resume = model->getPauseResume();
            pause_resume->setPos(461, 696);
            pause_resume->setHtml("<style>font-family:monaco;</style>"
                                  "<div style:'font-size:44px'>resume</div>");
            scene->addItem(pause_resume);
        }
    }
}

void Controller::launch_game() {
    qDebug() << "Launch game";
    view->delete_menu();
    view->load_game();
}

CustomScene* Controller::getScene()
{
    return scene;
}

Model *Controller::getModel()
{
    return model;
}

void Controller::finish_game()
{
    qDebug() << "Finish game";
    space = 0;
    curr_score = 0;
    aim_score = 0;
    level = 0;
    model->setScoreBoard(0);
    model->getGamePlayer()->setSpeed(6.5);
    model->getGamePlayer()->setVDirection(vertical_direction::UP);
    model->getGamePlayer()->setHDirection(horizontal_direction::NONE);
    view->delete_game();
}

void Controller::setIsMenuOn(bool isMenuOn)
{
    this->isMenuOn = isMenuOn;
}

void Controller::slotKeyPress(QKeyEvent* event) {
    if (play_timer->isActive()) {
        int key = event->key();
        Player* player = model->getGamePlayer();
        if (key == Qt::Key_A) {
            player->moveBtnPressed.first = true;
            player->setHDirection(horizontal_direction::LEFT);
            //            hrz_direction_timer->start(1);
        } else if (key == Qt::Key_D) {
            player->moveBtnPressed.second = true;
            player->setHDirection(horizontal_direction::RIGHT);
            //            hrz_direction_timer->start(1);
        }
    }
}

void Controller::slotKeyRelease(QKeyEvent *event)
{
    Player* player = model->getGamePlayer();
    if (event->key() == Qt::Key_A) {
        player->moveBtnPressed.first = false;
        if (player->moveBtnPressed.second == true) {
            player->setHDirection(horizontal_direction::RIGHT);
        } else {
            //                hrz_direction_timer->stop();
            player->setHDirection(horizontal_direction::NONE);
        }
        //        player->moveBtnPressed.second = true;
        //        player->setHDirection(horizontal_direction::RIGHT);
    } else if (event->key() == Qt::Key_D) {
        player->moveBtnPressed.second = false;
        if (player->moveBtnPressed.first == true) {
            player->setHDirection(horizontal_direction::LEFT);
        } else {
            //                hrz_direction_timer->stop();
            player->setHDirection(horizontal_direction::NONE);
        }
        //        player->moveBtnPressed.first = true;
        //        player->setHDirection(horizontal_direction::LEFT);
    } else {
        player->setHDirection(horizontal_direction::NONE);
    }
}

void Controller::hrzDirectionTimerTick()
{
    Player* player = model->getGamePlayer();
    if (player->getHDirection() != horizontal_direction::NONE) {
        if (player->getHDirection() == horizontal_direction::LEFT) {
            // 140 - width of player_picture
            scene->removeItem(player->getGraphic());
            player->setLeftEdge(model->getLeftEdgeReverseImage());
            player->setRightEdge(model->getRightEdgeReverseImage());
            player->setImage(*(model->getReverseImage()));
            player->setGraphic(scene->addPixmap(player->getImage()));
            player->getGraphic()->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
            player->getGraphic()->setOffset(player->getPos());
            player->setPos(model->getGamePlayer()->getPos() + QPointF(-4.4, 0));
            if (player->getPos().x() <= -70) {
                player->setPos(QPointF(getWidth() - 70, player->getPos().y()));
            }


        } else if (player->getHDirection() == horizontal_direction::RIGHT) {
            scene->removeItem(player->getGraphic());
            player->setLeftEdge(model->getLeftEdgeImage());
            player->setRightEdge(model->getRightEdgeImage());
            player->setImage(*(model->getImage()));
            player->setGraphic(scene->addPixmap(player->getImage()));
            player->getGraphic()->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
            player->setPos(model->getGamePlayer()->getPos() + QPointF(4.4, 0));
            player->getGraphic()->setOffset(player->getPos());
            if (player->getPos().x() >= getWidth() - 70) {
                player->setPos(QPointF(-70, player->getPos().y()));
            }
        }
    }
}

std::optional<int> Controller::collidesWithPlatforms() {
    Player* player = model->getGamePlayer();
    auto platforms = model->getPlatforms();
    QPointF curr_pos;
    //    std::optional<QPointF> res = std::nullopt;

    int size = platforms.size();
    for(int i = 0; i < size; ++i) {
        curr_pos = platforms[i]->getPos();
        if (player->getPos().x() + player->getLeftEdge() >= curr_pos.x() &&
                player->getPos().x() + player->getLeftEdge() <= platforms[i]->getImage().width() + curr_pos.x() ||
            player->getPos().x() + player->getRightEdge() >= curr_pos.x() &&
                player->getPos().x() + player->getRightEdge() <= curr_pos.x() + platforms[i]->getImage().width()) {
            if (player->getPos().y() + player->getImage().height() + player->getSpeed() >= curr_pos.y() &&
                player->getPos().y() + player->getImage().height() <= curr_pos.y()) {
                return std::optional<int>(i);
            }
        }
    }

    return std::nullopt;
}

void Controller::menuTimerTick() {
    static int offset = 0;
    static int count = 0;
    static double curr_x = 0;
    static double ufo_radius = model->getMenuUFO()->getRadius();

    //player animation
    Player* player = model->getPlayer();
    QPointF ufo_pos = model->getMenuUFO()->getCenter();
    QPointF start_pos = player->getPos();
    if (player->getSpeed() <= eps) {
        player->setVDirection(vertical_direction::DOWN);
    } else if (player->getPos().y() >= getHeight() - 380) {
        player->setVDirection(vertical_direction::UP);
        player->setSpeed(6.5);
    }
    if (player->getVDirection() == vertical_direction::UP) {
        player->setPos(QPointF(start_pos.x(), player->getPos().y() - player->getSpeed()));
        //            player->setCurrHeight(player->getCurrHeight() + player->getSpeed());
        player->changeSpeed();
    } else {
        player->setPos(QPointF(start_pos.x(), player->getPos().y() + player->getSpeed()));
        //            player->setCurrHeight(player->getCurrHeight() - player->getSpeed());
        player->changeSpeed();
    }
    //        player->setPos(QPointF(player->getPos().x(), getHeight() - player->getCurrHeight()));

    //ufo animation
    Menu_UFO* menu_ufo = model->getMenuUFO();
    double speed = menu_ufo->getSpeed();
    if (curr_x >= ufo_radius) {
        curr_x = ufo_radius;
        menu_ufo->setSpeed(speed * -1);
        speed *= -1;
    } else if (curr_x <= -ufo_radius) {
        curr_x = -ufo_radius;
        menu_ufo->setSpeed(speed * -1);
        speed *= -1;
    }

    //lemniskate
    double b = 2 * curr_x * curr_x + ufo_radius * ufo_radius;
    double y = sqrt((-b + sqrt(b * b - 4 * curr_x * curr_x * (curr_x * curr_x - ufo_radius * ufo_radius)))/2);
    if (y <= eps) {
        menu_ufo->setLoc(menu_ufo->getLoc() == ufo_location::UnderCenter ? ufo_location::AboveCenter : ufo_location::UnderCenter);
    }

    if (menu_ufo->getLoc() == ufo_location::UnderCenter) {
        menu_ufo->setPos(ufo_pos + QPointF(curr_x, -y));
    } else {
        menu_ufo->setPos(ufo_pos + QPointF(curr_x, y));
    }
    curr_x += speed;
    if (count >= 225 || count % 2 == 0) {
        QPainterPath path;
        QPointF ufo_pos = menu_ufo->getPos();
        path.moveTo(QPointF(52, 100) + ufo_pos);
        path.lineTo(QPointF(114, 100) + ufo_pos);
        path.lineTo(QPointF(160, 265) + ufo_pos);
        for (double i = 0; i < 154; i += 0.3) {
            path.lineTo(QPointF(160, 265) + ufo_pos + QPointF(-i, 3 * sin((i * 7 * M_PI + offset) / 154)));
        }

        path.lineTo(ufo_pos + QPointF(6, 265));
        path.lineTo(ufo_pos + QPointF(52, 100));
        if (count >= 225) {
            view->show_menu(path, QColor(0, 255, 0, 230));
        } else {
            view->show_menu(path);
        }
        offset += 10;
    } else {
        view->show_menu();
    }
    count = (count + 1) % 450;
}

void Controller::playTimerTick() {
    Player* player = model->getGamePlayer();
    std::optional<int> index = std::nullopt;
    if (player->getSpeed() <= eps) {
        player->setVDirection(vertical_direction::DOWN);
        deletePlatforms();
        if (move_timer->isActive()) {
            move_timer->stop();
        }
        //Рассматривать врагов?
    } else if (player->getVDirection() == vertical_direction::DOWN) {
        index = collidesWithPlatforms();
    }

    auto& platforms = model->getPlatforms();
    int size = platforms.size();
    int width_of_platform = platforms[0]->getImage().width();
    double speed;
    QPointF pos;
    for (int i = 0; i < size; ++i) {
        speed = platforms[i]->getSpeed();
        if (abs(speed) >= eps) {
            pos = platforms[i]->getPos();
            if (speed >= eps) {
                if (pos.x() + speed <= width - width_of_platform) {
                    platforms[i]->setPos(QPointF(pos.x() + speed, pos.y()));
                } else {
                    platforms[i]->setPos(QPointF(width - width_of_platform, pos.y()));
                    platforms[i]->setSpeed(-speed);
                }
            } else {
                if (pos.x() + speed >= 0) {
                    platforms[i]->setPos(QPointF(pos.x() + speed, pos.y()));
                } else {
                    platforms[i]->setPos(QPointF(0, pos.y()));
                    platforms[i]->setSpeed(-speed);
                }
            }
        }
    }

    if (index) {
//        qDebug() << "collide:" << (*collide).y();
        if (isSoundOn) {
            platforms[*index]->getType() == platformType::Whole ? m_player_1->play() : m_player_2->play();
        }
        if (platforms[*index]->getType() == platformType::Broken) {
            scene->removeItem(platforms[*index]->getGraphic());
            platforms.erase(platforms.begin() + *index);
            index = std::nullopt;
        } else {
        //        qDebug() << (*collide).y() + player->getImage().height();
        player->setVDirection(vertical_direction::UP);
        player->setSpeed(6.5);
        player->setPos(QPointF(player->getPos().x(), platforms[*index]->getPos().y() - player->getImage().height()));
        move_timer->setInterval(6);
        model->setSpeed(calculateSpeed(QPointF(player->getPos().x(), platforms[*index]->getPos().y()), 900));
        if (model->getSpeed() > 0) {
            int span = space;
            space -= int(900 - platforms[*index]->getPos().y());
//            qDebug() << "platformPosotion:" << 900 - (*collide).y() - player->getImage().height();
//            qDebug() << "space:" << (900 - (*collide).y() - player->getImage().height());
//            qDebug() << "koef:" << (900 - (*collide).y() - player->getImage().height()) / 121;
//            qDebug() << "points:" << (900 - (*collide).y() - player->getImage().height()) / 121 * convertLevelToPoints(level);
            aim_score += (900 - platforms[*index]->getPos().y()) / height * convertLevelToPoints(level);
            checkRaiseLevel();
            if (!score_timer->isActive()) {
                score_timer->start();
            }
            if (space < 0) {
                generatePlatforms(span);
            }
            move_timer->start();
        }
        }
    } else {
        if (player->getVDirection() == vertical_direction::UP) {
            player->setPos(player->getPos() - QPointF(0, player->getSpeed()));
            player->changeSpeed();
        } else {
            player->setPos(player->getPos() + QPointF(0, player->getSpeed()));
            player->changeSpeed();
            if (player->getPos().y() >= getHeight()) {
                finish_game();
                view->load_menu();
                return;
            }
        }
    }
    view->show_game();
    if (index) {
        Sleep(30);
    }
}

void Controller::scoreTimerTick()
{
    if (curr_score == aim_score) {
        score_timer->stop();
    } else {
        model->setScoreBoard(++curr_score);
    }
}

void Controller::moveTimerTick()
{
    double speed = model->getSpeed();
    Player* player = model->getGamePlayer();
    player->setPos(model->getGamePlayer()->getPos() + QPointF(0 , speed));
    auto platforms = model->getPlatforms();
    int size = platforms.size();
    for (int i = 0; i < size; ++i) {
        platforms[i]->setPos(platforms[i]->getPos() + QPointF(0, speed));
    }
}

void Controller::slotChangeImage()
{
    model->getPlayer()->setImage(*(model->getImage()));
    model->getGamePlayer()->setImage(model->getGamePlayer()->getHDirection() == horizontal_direction::RIGHT ? *(model->getImage()) : *(model->getReverseImage()));

}

QTimer* Controller::getMenuTimer() const {
    return menu_timer;
}

QTimer* Controller::getPlayTimer() const {
    return play_timer;
}

QTimer* Controller::getHorizontalTimer() const {
    return hrz_direction_timer;
}

QTimer *Controller::getScoreTimer() const
{
    return score_timer;
}

QTimer* Controller::getMoveTimer() const {
    return move_timer;
}

double Controller::calculateSpeed(QPointF collide, double border)
{
    return (border - collide.y()) / (int)(555 / move_timer->interval());
}

void Controller::checkRaiseLevel()
{
    if (aim_score >= 2000 && aim_score < 5000) {
        level = 1;
    } else if (aim_score >= 5000 && aim_score < 10'000) {
        level = 2;
    } else if (aim_score >= 10'000 && aim_score < 16'000) {
        level = 3;
    } else if (aim_score >= 16'000 && aim_score < 23'000) {
        level = 4;
    } else if (aim_score >= 23'000) {
        level = 5;
    }
}

bool Controller::isPlatformMovable()
{
    return rand() % 100 + 1 <= level * 7 ? true : false;
}

void Controller::generateBrokenPlatforms(int num_gen_plat, int num_broken_plat)
{
    if (num_broken_plat) {
    auto& platforms = model->getPlatforms();
    int size = platforms.size();
    int pos;
    qDebug() << "index:" << pos;
    std::optional<int> bottom_border = std::nullopt;
    std::optional<int> top_border = std::nullopt;
    for (int i = 0; i < num_broken_plat; ++i) {
            pos = rand() % (num_gen_plat - 1) + size - num_gen_plat + 1;
        for (int j = pos - 1; j >= size - num_gen_plat; --j) {
            if (platforms[j]->getType() == platformType::Whole) {
                bottom_border = platforms[j]->getPos().y();
                break;
            }
        }
        for (int j = pos + 1; j < size; ++j) {
            if (platforms[j]->getType() == platformType::Whole) {
                top_border = platforms[j]->getPos().y();
                break;
            }
        }

        if (!top_border) {
            top_border = platforms[size - num_gen_plat]->getPos().y() - 832;
        }
        qDebug() << "top border:" << *top_border;
        qDebug() << "bottom border:" << *bottom_border;
        if (*bottom_border - *top_border <= 200 && *bottom_border > *top_border) {
            qDebug() << "create";
            double speed = platforms[pos]->getSpeed();
            delete platforms[pos];
            platforms[pos] = new Platform(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/brown_platform.png"), platforms[pos]->getPos(), speed, platformType::Broken);
        }
        qDebug() << '\n';
    }
    }
}

int Controller::numberOfBrokenPlatforms(int platform)
{
        if (platform <= 5) {
            return 2;
        }
        if (platform <= 5) {
            return 3;
        }
//        if (platform <= 7) {
//            return 4;
//        }
        return 4;
}

void Controller::generatePlatforms(int span)
{
//    qDebug() << "Platform generation";
//    qDebug() << "Span:" << span;
    auto& platforms = model->getPlatforms();
    this->space = 800 + this->space;
    int space = 800;
    int x_pos = rand() % (width + 1 - 131);
    if (isPlatformMovable()) {
        platforms.push_back(new Platform(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/blue_platform.png"), QPointF(x_pos, -32 - span), convertLevelToSpeedOfPlatform(level), platformType::Whole));
    } else {
        platforms.push_back(new Platform(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/green_platform.png"), QPointF(x_pos, -32 - span), 0, platformType::Whole));
    }
    int y_pos;
    int prev_y_pos = 96;
    space -= 96;

//    int lim_plat = convertLevelToNumPlatforms(level);
//    qDebug() << "Limit of plaforms:" << lim_plat;
    qDebug() << "level:" << level;
    int num_gen_plat = 1;

    while (space > model->getGamePlayer()->getHeightOfFly() - 100) {
            qDebug() << "Iteration" << num_gen_plat;
            x_pos = rand() % (width + 1 - 131);
            qDebug() << "Height of Fly" << model->getGamePlayer()->getHeightOfFly();
            y_pos = rand() % (space + 1 - 32) % ((int)model->getGamePlayer()->getHeightOfFly() - convertLevelToDensity(level - 1)) - convertLevelToDensity(level) + convertLevelToDensity(level - 1) + prev_y_pos;
//        if (y_pos < 0) {
//            qDebug() << "Error" << "Positive y_pos";
//            qDebug() << "x:" << x_pos << "y:" << y_pos;
//            qDebug() << '\n';
//        }
        if (isPlatformMovable()) {
            platforms.push_back(new Platform(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/blue_platform.png"), QPointF(x_pos,- y_pos - span), convertLevelToSpeedOfPlatform(level), platformType::Whole));
        } else {
            platforms.push_back(new Platform(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/green_platform.png"), QPointF(x_pos,- y_pos - span), 0, platformType::Whole));
        }
        prev_y_pos = y_pos + 64;
        space = 800 - prev_y_pos;
        ++num_gen_plat;
    }

    qDebug() << "Number of generated platforms:" << num_gen_plat;
    int num_broken_plat = numberOfBrokenPlatforms(num_gen_plat);
//    if (num_broken_plat >= 1) {
//        num_broken_plat = rand() % (num_broken_plat + 1);
//    }
    qDebug() << "Number of broken platforms:" << num_broken_plat;
    generateBrokenPlatforms(num_gen_plat, num_broken_plat);

    //    auto platforms = model->getPlatforms();
    //    for (auto* platform : platforms) {
    //        qDebug() << "Pos(x, y):" << platform->getPos();
    //    }
    //    qDebug() << '\n';
}

void Controller::generateStartPlatforms()
{
    //    int height = getHeight();
    int tmp = rand() % (getWidth() - 131 + 1);
    model->getGamePlayer()->setPos(QPointF(tmp, 910));
    tmp += rand() % 300 - 150;
    if (tmp > width - 131 + 1) {
        tmp = width - 131 + 1;
    } else if (tmp < 0) {
        tmp = 0;
    }
    model->getPlatforms().push_back(new Platform(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/green_platform.png"), QPointF(tmp, height - 32), 0, platformType::Whole));
    //    int count = 0;
    int x_pos;
    int y_pos;
    int prev_y_pos = height - 84;
    while (prev_y_pos > 132) {
        x_pos = rand() % (width - 131 + 1);
        y_pos = rand() % 100;
        model->getPlatforms().push_back(new Platform(QPixmap(":/images/C:/Users/lesha/Desktop/Doodle Jump/green_platform.png"), QPointF(x_pos, prev_y_pos - y_pos), 0, platformType::Whole));
        prev_y_pos -= (y_pos + 52);
    }
}

void Controller::deletePlatforms()
{
    auto& platforms = model->getPlatforms();
    for (auto iter = platforms.begin(); iter != platforms.end(); ++iter) {
        if ((*iter)->getPos().y() >= getHeight()) {
            delete *iter;
            platforms.erase(iter);
            --iter;
        }
    }
}

int convertLevelToPoints(int level) {

    switch (level) {
    case 0 :
        return static_cast<int>(pointsForLevels::Zero);
    case 1 :
        return static_cast<int>(pointsForLevels::First);
    case 2 :
        return static_cast<int>(pointsForLevels::Second);
    case 3 :
        return static_cast<int>(pointsForLevels::Third);
    case 4 :
        return static_cast<int>(pointsForLevels::Fourth);
    case 5:
        return static_cast<int>(pointsForLevels::Fifth);
    default:
        return static_cast<int>(pointsForLevels::Zero);
    }
}

//int convertLevelToNumPlatforms(int level) {
//    switch (level) {
//    case 0 :
//        qDebug() << "limit: " << static_cast<int>(platformsForLevels::Zero);
//        return static_cast<int>(platformsForLevels::Zero);
//    case 1 :
//        return static_cast<int>(platformsForLevels::First);
//    case 2 :
//        return static_cast<int>(platformsForLevels::Second);
//    case 3 :
//        return static_cast<int>(platformsForLevels::Third);
//    case 4 :
//        return static_cast<int>(platformsForLevels::Fourth);
//    case 5:
//        return static_cast<int>(platformsForLevels::Fifth);
//    default:
//        return static_cast<int>(platformsForLevels::Zero);
//    }
//}

int convertLevelToDensity(int level) {
    switch (level) {
    case 0 :
        return static_cast<int>(densityForLevels::Zero);
    case 1 :
        return static_cast<int>(densityForLevels::First);
    case 2 :
        return static_cast<int>(densityForLevels::Second);
    case 3 :
        return static_cast<int>(densityForLevels::Third);
    case 4 :
        return static_cast<int>(densityForLevels::Fourth);
    case 5:
        return static_cast<int>(densityForLevels::Fifth);
    default:
        return static_cast<int>(densityForLevels::Zero);
    }
}

double convertLevelToSpeedOfPlatform(int level) {
    switch (level) {
    case 0 :
        return 0;
    case 1 :
        return 0.9;
    case 2 :
        return 1.2;
    case 3 :
        return 1.5;
    case 4 :
        return 1.9;
    case 5:
        return 2.3;
    default:
        return 1.7;
    }
}
