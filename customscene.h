
#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QGraphicsScene>
#include <QObject>

class CustomScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CustomScene(QObject *parent = nullptr);
    ~CustomScene();

signals:
    // Сигнал для передачи координат положения курсора мыши
    void signalMoveCoordinate(QPointF);
    void signalPressCoordinate(QPointF);
    void signalPressKey(QKeyEvent*);
    void signalReleaseEvent(QKeyEvent*);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent*) override;
    void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    void keyReleaseEvent(QKeyEvent *) override;
};

#endif // CUSTOMSCENE_H
