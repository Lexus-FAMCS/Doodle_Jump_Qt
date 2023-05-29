
#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H

#include "model.h"
#include "customscene.h"

#include <QWidget>
#include <QTimer>

class AbstractController : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractController(QWidget *parent = nullptr, int width = 770, int height = 982);
    int getWidth();
    int getHeight();
    virtual CustomScene* getScene() = 0;
    virtual Model* getModel() = 0;
    virtual QTimer* getMenuTimer() const = 0;
    virtual QTimer* getMoveTimer() const = 0;
    virtual QTimer* getPlayTimer() const = 0;
    virtual QTimer* getHorizontalTimer() const = 0;
    virtual QTimer* getScoreTimer() const = 0;

    virtual void setIsMenuOn(bool) = 0;

    virtual void generateStartPlatforms() = 0;

protected:
    virtual void launch_game() = 0;
    virtual void finish_game() = 0;
    int width;
    int height;

signals:

};

#endif // ABSTRACTCONTROLLER_H
