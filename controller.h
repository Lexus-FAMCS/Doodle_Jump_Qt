#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "abstractcontroller.h"
#include "view.h"
#include "updater.h"
#include "characterchoice.h"

#include <stdlib.h>
#include <QTimer>
#include <optional>
#include <QMediaPlayer>
#include <QMediaPlaylist>

//enum class sounds {
//    Jump,
//    Platform_broke
//};

//enum class platformsForLevels {
//    Zero = 100, // ~non-limited
//    First = 11,
//    Second = 8,
//    Third = 5,
//    Fourth = 3,
//    Fifth = 2
//};


//span of 1 screen
enum class pointsForLevels {
    Zero =  200,
    First = 400,
    Second = 600,
    Third = 800,
    Fourth = 1000,
    Fifth = 1200
};

enum class densityForLevels{
    Zero =  280,
    First = 230,
    Second = 190,
    Third = 150,
    Fourth = 120,
    Fifth = 100
};

int convertLevelToPoints(int);
int convertLevelToNumPlatforms(int);
int convertLevelToDensity(int);
double convertLevelToSpeedOfPlatform(int);

class Controller : public AbstractController
{
    Q_OBJECT

public:
    Controller(QWidget *parent = nullptr);
    ~Controller();
    CustomScene* getScene() override;
    Model* getModel() override;

protected:
    void connect_timers();

    void launch_game() override;
    void finish_game() override;

    void setIsMenuOn(bool) override;

    QTimer* getMenuTimer() const override;
    QTimer* getPlayTimer() const override;
    QTimer* getHorizontalTimer() const override;
    QTimer* getScoreTimer() const override;
    QTimer* getMoveTimer() const override;

    double calculateSpeed(QPointF, double);
    void checkRaiseLevel();
    bool isPlatformMovable();
    int numberOfBrokenPlatforms(int);
    void generateBrokenPlatforms(int, int);
    void generatePlatforms(int);
    void generateStartPlatforms() override;
    void deletePlatforms();

    std::optional<int> collidesWithPlatforms();

signals:
    void customize();

private slots:
    void slotMove(QPointF);
    void slotPress(QPointF);
    void slotKeyPress(QKeyEvent*);
    void slotKeyRelease(QKeyEvent*);
    void hrzDirectionTimerTick();
    void menuTimerTick();
    void playTimerTick();
    void scoreTimerTick();
    void moveTimerTick();
    void slotChangeImage();

private:
    View* view;
    Model* model;
    Updater* updater;
    CustomScene* scene;
    QTimer* menu_timer;
    QTimer* play_timer;
    QTimer* hrz_direction_timer;
    QTimer* move_timer;
    QTimer* score_timer;
    QMediaPlayer* m_player_1;
    QMediaPlayer* m_player_2;
//    QMediaPlaylist* m_playlist;

    CharacterChoice* chr_change_window;

    int space;
    int level;
    int curr_score;
    int aim_score;
    bool isSoundOn;
    bool isMenuOn;
};

#endif // CONTROLLER_H
