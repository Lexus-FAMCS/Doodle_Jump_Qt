
#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "player.h"
#include "platform.h"
#include "menu_ufo.h"

class Model
{
public:
    Model();

    Player* getPlayer() const;
    std::vector<Platform*>& getPlatforms();
    const std::vector<Enemy*>& getEnemies() const;
    void setPlayer(Player*);
    void setPlatforms(const std::vector<Platform*>&);
    Player* getGamePlayer() const;
    void setGamePlayer(Player*);
    void setEnemies(const std::vector<Enemy*>&);
    void setMenuPlatform(Platform*);
    Platform* getMenuPlatform() const;
    void setMenuUFO(Menu_UFO*);
    Menu_UFO* getMenuUFO() const;

    void setOptions(QGraphicsPixmapItem*);
    QGraphicsPixmapItem* getOptions() const;
    void setOptionsPos(QPointF option_pos);
    QPointF getOptionsPos() const;
    void setText(QGraphicsTextItem*);
    QGraphicsTextItem* getText() const;
    void setGameName(QGraphicsTextItem*);
    QGraphicsTextItem* getGameName() const;
    void setBackdround(QGraphicsPixmapItem*);
    QGraphicsPixmapItem* getBackground() const;
    void setPauseBackdround(QGraphicsPixmapItem*);
    QGraphicsPixmapItem* getPauseBackground() const;
    void setBug_1(QGraphicsPixmapItem*);
    QGraphicsPixmapItem* getBug_1() const;
    void setBug_2(QGraphicsPixmapItem*);
    QGraphicsPixmapItem* getBug_2() const;
    void setBug_3(QGraphicsPixmapItem*);
    QGraphicsPixmapItem* getBug_3() const;
    void setBug_4(QGraphicsPixmapItem*);
    QGraphicsPixmapItem* getBug_4() const;
    void setBug_5(QGraphicsPixmapItem*);
    QGraphicsPixmapItem* getBug_5() const;
    void setMenuEllipse(QGraphicsEllipseItem*);
    QGraphicsEllipseItem* getMenuEllipse() const;
    void setMenuText(QGraphicsTextItem*);
    QGraphicsTextItem* getMenuText();
    void setPlayEllipse(QGraphicsEllipseItem*);
    QGraphicsEllipseItem* getPlayEllipse() const;
    void setPlayText(QGraphicsTextItem*);
    QGraphicsTextItem* getPlayText();
    void setSoundText(QGraphicsTextItem*);
    QGraphicsTextItem* getSoundText();
    void setSoundON(QGraphicsTextItem*);
    QGraphicsTextItem* getSoundON();
    void setSoundOFF(QGraphicsTextItem*);
    QGraphicsTextItem* getSoundOFF();
    void setRay(QGraphicsPathItem*);
    QGraphicsPathItem* getRay() const;
    double getSpeed() const;
    void setSpeed(double);
    QPixmap* getImage() const;
    void setImage(QPixmap*);
    QPixmap* getReverseImage() const;
    void setReverseImage(QPixmap*);
    QGraphicsPixmapItem* getCustomeIcon() const;
    void setCustomeIcon(QGraphicsPixmapItem*);
    void setCustomeText(QGraphicsTextItem*);
    QGraphicsTextItem* getCustomeText() const;
    void setScoreBoard(int);
    QGraphicsTextItem* getScoreBoard() const;
    void setPauseBar(QGraphicsPolygonItem*);
    QGraphicsPolygonItem* getPauseBar() const;
    void setPauseIcon(QGraphicsPixmapItem*);
    QGraphicsPixmapItem* getPauseIcon() const;
    void setPauseRay(QGraphicsPathItem*);
    QGraphicsPathItem* getPauseRay() const;
    void setPauseGameName(QGraphicsTextItem*);
    QGraphicsTextItem* getPauseGameName() const;
    void setPauseText(QGraphicsTextItem*);
    QGraphicsTextItem* getPauseText() const;
    void setPauseResume(QGraphicsTextItem*);
    QGraphicsTextItem* getPauseResume() const;
    QGraphicsEllipseItem* getPauseResumeEllipse() const;
    void setPauseResumeEllipse(QGraphicsEllipseItem*);

    int getLeftEdgeImage() const;
    int getRightEdgeImage() const;
    int getLeftEdgeReverseImage() const;
    int getRightEdgeReverseImage() const;

    void setLeftEdgeImage(int);
    void setRightEdgeImage(int);
    void setLeftEdgeReverseImage(int);
    void setRightEdgeReverseImage(int);

private:
    std::vector<Enemy*> enemies;
    Player* player;
    std::vector<Platform*> platforms;
    Platform* menu_platform;
    Player* game_player;
    Menu_UFO* menu_ufo;

    QGraphicsPixmapItem* options;
    QPointF options_pos;
    QGraphicsPixmapItem* custome_icon;
    QGraphicsTextItem* custome_text;
    QGraphicsTextItem* text;
    QGraphicsTextItem* game_name;
    QGraphicsPixmapItem* background;
    QGraphicsPixmapItem* pause_background;
    QGraphicsPixmapItem* bug_1;
    QGraphicsPixmapItem* bug_2;
    QGraphicsPixmapItem* bug_3;
    QGraphicsPixmapItem* bug_4;
    QGraphicsPixmapItem* bug_5;
    QGraphicsEllipseItem* menu_ellipse;
    QGraphicsTextItem* menu_text;
    QGraphicsEllipseItem* play_ellipse;
    QGraphicsTextItem* play_text;
    QGraphicsTextItem* sound_text;
    QGraphicsTextItem* sound_on;
    QGraphicsTextItem* sound_off;
    QGraphicsPathItem* ray;
    QGraphicsTextItem* scoreboard;
    QGraphicsPolygonItem* pause_bar;
    QGraphicsPixmapItem* pause_icon;
    QGraphicsPathItem* pause_ray;
    QGraphicsTextItem* pause_game_name;
    QGraphicsTextItem* pause_text;
    QGraphicsTextItem* pause_resume;
    QGraphicsEllipseItem* pause_resume_ellipse;

    QPixmap* image;
    QPixmap* reverse_image;
    int left_edge_image;
    int right_edge_image;
    int left_edge_reverse_image;
    int right_edge_reverse_image;

    double speed;

};

#endif // MODEL_H
