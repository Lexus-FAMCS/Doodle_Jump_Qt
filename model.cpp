
#include "model.h"

Model::Model():
    options(nullptr),
    text(nullptr),
    game_name(nullptr),
    background(nullptr),
    bug_1(nullptr),
    bug_2(nullptr),
    bug_3(nullptr),
    bug_4(nullptr),
    bug_5(nullptr),
    menu_ellipse(nullptr),
    menu_text(nullptr),
    play_ellipse(nullptr),
    play_text(nullptr),
    ray(nullptr),
    sound_text(nullptr),
    sound_on(nullptr),
    sound_off(nullptr),
    image(nullptr),
    reverse_image(nullptr),
    scoreboard(new QGraphicsTextItem),
    custome_text(nullptr),
    custome_icon(nullptr),
    pause_ray(nullptr),
    pause_background(nullptr),
    pause_bar(nullptr),
    pause_icon(nullptr),
    pause_game_name(nullptr),
    pause_text(nullptr),
    pause_resume(nullptr),
    pause_resume_ellipse(nullptr)
{
}

Player* Model::getPlayer() const
{
    return player;
}

void Model::setPlayer(Player* player) {
    this->player = player;
}

void Model::setPlatforms(const std::vector<Platform*>& platforms) {
    if (&this->platforms != &platforms) {
        int size = this->platforms.size();
        for (int i = 0; i < size; ++i) {
            delete this->platforms[i];
        }
    }
    this->platforms =  platforms;
}

void Model::setEnemies(const std::vector<Enemy*>& enemies)
{
    this->enemies = enemies;
}

void Model::setMenuPlatform(Platform* menu_platform)
{
    this->menu_platform = menu_platform;
}

Platform *Model::getMenuPlatform() const
{
    return menu_platform;
}

std::vector<Platform*>& Model::getPlatforms() {
    return platforms;
}

const std::vector<Enemy *> &Model::getEnemies() const
{
    return enemies;
}

Player* Model::getGamePlayer() const {
    return game_player;
}

void Model::setGamePlayer(Player* game_player) {
    this->game_player = game_player;
}

void Model::setMenuUFO(Menu_UFO* menu_ufo) {
    this->menu_ufo = menu_ufo;
}
Menu_UFO* Model::getMenuUFO() const {
    return menu_ufo;
}

void Model::setOptions(QGraphicsPixmapItem *options)
{
    if (this->options != options) {
        delete this->options;
        this->options = options;
    }
}

QGraphicsPixmapItem* Model::getOptions() const {
    return options;
}

void Model::setOptionsPos(QPointF options_pos) {
    this->options_pos = options_pos;
}

QPointF Model::getOptionsPos() const {
    return options_pos;
}

void Model::setText(QGraphicsTextItem* text) {
    if (this->text != text) {
        delete this->text;
        this->text = text;
    }
}

QGraphicsTextItem* Model::getText() const {
    return text;
}

void Model::setGameName(QGraphicsTextItem* game_name) {
    if (this->game_name != game_name) {
        delete this->game_name;
        this->game_name = game_name;
    }
}

QGraphicsTextItem* Model::getGameName() const {
    return game_name;
}

void Model::setBackdround(QGraphicsPixmapItem* background) {
    if (this->background != background) {
        delete this->background;
        this->background = background;
    }
}

QGraphicsPixmapItem* Model::getBackground() const {
    return background;
}

void Model::setBug_1(QGraphicsPixmapItem* bug_1) {
    if (this->bug_1 != bug_1) {
        delete this->bug_1;
        this->bug_1 = bug_1;
    }
}

QGraphicsPixmapItem* Model::getBug_1() const {
    return bug_1;
}

void Model::setBug_2(QGraphicsPixmapItem* bug_2) {
    if (this->bug_2 != bug_2) {
        delete this->bug_2;
        this->bug_2 = bug_2;
    }
}

QGraphicsPixmapItem* Model::getBug_2() const {
    return bug_2;
}

void Model::setBug_3(QGraphicsPixmapItem* bug_3) {
    if (this->bug_3 != bug_3) {
        delete this->bug_3;
        this->bug_3 = bug_3;
    }
}

QGraphicsPixmapItem* Model::getBug_3() const {
    return bug_3;
}

void Model::setBug_4(QGraphicsPixmapItem* bug_4) {
    if (this->bug_4 != bug_4) {
        delete this->bug_4;
        this->bug_4 = bug_4;
    }
}

QGraphicsPixmapItem* Model::getBug_4() const {
    return bug_4;
}
void Model::setBug_5(QGraphicsPixmapItem* bug_5) {
    if (this->bug_5 != bug_5) {
        delete this->bug_5;
        this->bug_5 = bug_5;
    }
}
QGraphicsPixmapItem* Model::getBug_5() const {
    return bug_5;
}
void Model::setMenuEllipse(QGraphicsEllipseItem* menu_ellipse) {
    if (this->menu_ellipse != menu_ellipse) {
        delete this->menu_ellipse;
        this->menu_ellipse = menu_ellipse;
    }
}
QGraphicsEllipseItem* Model::getMenuEllipse() const {
    return this->menu_ellipse;
}
void Model::setMenuText(QGraphicsTextItem* menu_text) {
    if (this->menu_text != menu_text) {
        delete this->menu_text;
        this->menu_text = menu_text;
    }
}
QGraphicsTextItem* Model::getMenuText() {
    return menu_text;
}
void Model::setPlayEllipse(QGraphicsEllipseItem* play_ellipse) {
    if (this->play_ellipse != play_ellipse) {
        delete this->play_ellipse;
        this->play_ellipse = play_ellipse;
    }
}
QGraphicsEllipseItem* Model::getPlayEllipse() const {
    return play_ellipse;
}
void Model::setPlayText(QGraphicsTextItem* play_text) {
    if (this->play_text != play_text) {
        delete this->play_text;
        this->play_text = play_text;
    }
}

QGraphicsTextItem* Model::getPlayText() {
    return play_text;
}

void Model::setRay(QGraphicsPathItem* ray) {
    if (this->ray != ray) {
        delete this->ray;
        this->ray = ray;
    }
}

QGraphicsPathItem* Model::getRay() const {
    return ray;
}

double Model::getSpeed() const {
    return speed;
}

void Model::setSpeed(double speed) {
    this->speed = speed;
}

void Model::setSoundText(QGraphicsTextItem* sound_text) {
    if (sound_text != this->sound_text) {
        delete this->sound_text;
        this->sound_text = sound_text;
    }
}

QGraphicsTextItem* Model::getSoundText() {
    return sound_text;
}

void Model::setSoundON(QGraphicsTextItem* sound_on) {
    if (sound_on != this->sound_on) {
        delete this->sound_on;
        this->sound_on = sound_on;
    }
}

QGraphicsTextItem* Model::getSoundON() {
    return sound_on;
}

void Model::setSoundOFF(QGraphicsTextItem* sound_off) {
    if (sound_off != this->sound_off) {
        delete this->sound_off;
        this->sound_off = sound_off;
    }
}

QGraphicsTextItem* Model::getSoundOFF() {
    return sound_off;
}

QPixmap* Model::getImage() const {
    return image;
}

void Model::setImage(QPixmap* image) {
    if (this->image != image) {
        delete this->image;
        this->image = image;
    }
}

QPixmap* Model::getReverseImage() const {
    return reverse_image;
}

void Model::setReverseImage(QPixmap* reverse_image) {
    if (this->reverse_image != reverse_image) {
        delete this->reverse_image;
        this->reverse_image = reverse_image;
    }
}

int Model::getLeftEdgeImage() const {
    return left_edge_image;
}

int Model::getRightEdgeImage() const {
    return right_edge_image;
}

int Model::getLeftEdgeReverseImage() const {
    return left_edge_reverse_image;
}

int Model::getRightEdgeReverseImage() const {
    return right_edge_reverse_image;
}

void Model::setLeftEdgeImage(int edge) {
    left_edge_image = edge;
}

void Model::setRightEdgeImage(int edge) {
    right_edge_image = edge;
}

void Model::setLeftEdgeReverseImage(int edge) {
    left_edge_reverse_image = edge;
}

void Model::setRightEdgeReverseImage(int edge) {
    right_edge_reverse_image = edge;
}

QGraphicsPixmapItem* Model::getCustomeIcon() const {
    return custome_icon;
}

void Model::setCustomeIcon(QGraphicsPixmapItem* custome_icon) {
    if (this->custome_icon != custome_icon) {
        delete this->custome_icon;
        this->custome_icon = custome_icon;
    }
}

void Model::setCustomeText(QGraphicsTextItem* custome_text) {
    if (this->custome_text != custome_text) {
        delete this->custome_text;
        this->custome_text = custome_text;
    }
}

QGraphicsTextItem* Model::getCustomeText() const {
    return custome_text;
}

void Model::setScoreBoard(int score) {
    scoreboard->setPlainText(QString::number(score));
}

QGraphicsTextItem* Model::getScoreBoard() const {
    return scoreboard;
}

void Model::setPauseBar(QGraphicsPolygonItem* pause_bar) {
    if (this->pause_bar != pause_bar) {
        delete this->pause_bar;
        this->pause_bar = pause_bar;
    }
}

QGraphicsPolygonItem* Model::getPauseBar() const {
    return pause_bar;
}

void Model::setPauseIcon(QGraphicsPixmapItem* pause_icon) {
    if (pause_icon != this->pause_icon) {
        delete this->pause_icon;
        this->pause_icon = pause_icon;
    }
}

QGraphicsPixmapItem* Model::getPauseIcon() const {
    return pause_icon;
}

void Model::setPauseRay(QGraphicsPathItem* pause_ray) {
    if (pause_ray != this->pause_ray) {
        delete this->pause_ray;
        this->pause_ray = pause_ray;
    }
}

QGraphicsPathItem* Model::getPauseRay() const {
    return pause_ray;
}

void Model::setPauseBackdround(QGraphicsPixmapItem* pause_background) {
    if (pause_background != this->pause_background) {
        delete this->pause_background;
        this->pause_background = pause_background;
    }
}

QGraphicsPixmapItem* Model::getPauseBackground() const {
    return pause_background;
}

void Model::setPauseGameName(QGraphicsTextItem* pause_game_name) {
    if (pause_game_name != this->pause_game_name) {
        delete this->pause_game_name;
        this->pause_game_name = pause_game_name;
    }
}

QGraphicsTextItem* Model::getPauseGameName() const {
    return pause_game_name;
}

void Model::setPauseText(QGraphicsTextItem* pause_text) {
    if (pause_text != this->pause_text) {
        delete this->pause_text;
        this->pause_text = pause_text;
    }
}

QGraphicsTextItem* Model::getPauseText() const {
    return pause_text;
}

void Model::setPauseResume(QGraphicsTextItem* pause_resume) {
    if (pause_resume != this->pause_resume) {
        delete this->pause_resume;
        this->pause_resume = pause_resume;
    }
}

QGraphicsTextItem* Model::getPauseResume() const {
    return pause_resume;
}

QGraphicsEllipseItem* Model::getPauseResumeEllipse() const {
    return pause_resume_ellipse;
}

void Model::setPauseResumeEllipse(QGraphicsEllipseItem* pause_resume_ellipse) {
    if (pause_resume_ellipse != this->pause_resume_ellipse) {
        delete this->pause_resume_ellipse;
        this->pause_resume_ellipse = pause_resume_ellipse;
    }
}
