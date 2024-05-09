#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit GraphicsScene(QObject *parent = nullptr);
    virtual ~GraphicsScene();

private:
         // Дополнительные поля и методы могут быть добавлены по мере необходимости
};

#endif // EXAMPLE_H
