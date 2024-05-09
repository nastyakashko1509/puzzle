#ifndef HELPPUZZLE_H
#define HELPPUZZLE_H

#include <QDialog>
#include <QMainWindow>
#include <QImage>
#include <QRect>
#include <QGraphicsPixmapItem>
#include <QMap>
#include <QTimer>
#include <random>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QTransform>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <cmath>
#include <cstdlib>
#include <QDebug>

#include "graphicsscene.h"

namespace Ui {
class HelpPuzzle;
}

class HelpPuzzle : public QDialog
{
    Q_OBJECT

public:
    explicit HelpPuzzle(QWidget *parent = nullptr);
    ~HelpPuzzle();

private slots:
    void on_pushButton_clicked();

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::HelpPuzzle *ui;

    QList<QImage> splitImage(const QString& filename);
    void swapImageParts();
    void checkPositions();

    QGraphicsScene *scene = nullptr;
    QTimer *timer = nullptr;
    QMap<int, QPointF> partPositions;
    QGraphicsPixmapItem *selectedItem = nullptr;
};

#endif // HELPPUZZLE_H
