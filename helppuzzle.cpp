#include "helppuzzle.h"
#include "ui_helppuzzle.h"

HelpPuzzle::HelpPuzzle(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HelpPuzzle)
{
    ui->setupUi(this);

    scene = new GraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setMouseTracking(true);  // Включаем отслеживание мыши

    // Инициализируем QTimer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &HelpPuzzle::swapImageParts);
    // Запускаем таймер с интервалом 5 секунд
    timer->start(5000);
}

// Функция для загрузки изображения из файла и разбиения его на 6 равных кусочков
QList<QImage> HelpPuzzle::splitImage(const QString& filename) {
    QList<QImage> imageParts;

    // Загрузка изображения из файла
    QImage originalImage(filename);
    QSize targetSize(300, 200);
    originalImage = originalImage.scaled(targetSize, Qt::KeepAspectRatio);

    if(originalImage.isNull()) {
        qDebug() << "Ошибка: Не удалось загрузить изображение";
        return imageParts;
    }

    // Определение размеров каждой части
    int partWidth = originalImage.width() / 3;
    int partHeight = originalImage.height() / 2;

    // Разбиение изображения на 6 равных частей
    for(int y = 0; y < 2; ++y) {
        for(int x = 0; x < 3; ++x) {
            QRect rect(x * partWidth, y * partHeight, partWidth, partHeight);
            QImage part = originalImage.copy(rect);
            imageParts.append(part);
        }
    }

    for (int i = 0; i < imageParts.size(); ++i) {
        int xPos = (i % 3) * imageParts[i].width();
        int yPos = (i / 3) * imageParts[i].height();
        partPositions.insert(i, QPointF(xPos, yPos));
    }

    return imageParts;
}

HelpPuzzle::~HelpPuzzle()
{
    delete ui;
}

void HelpPuzzle::on_pushButton_clicked()
{
    // Загрузка и разделение изображения
    QString filename = "/home/nastya/Загрузки/fon1.jpg";
    QList<QImage> imageParts = splitImage(filename);

    // Отображение всех частей изображения на графической сцене
    for (int i = 0; i < imageParts.size(); ++i) {
        // Создание элемента QGraphicsPixmapItem для текущей части изображения
        QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(imageParts[i]));

        pixmapItem->setFlag(QGraphicsItem::ItemIsMovable, true);

        // Расположение текущей части на сцене (расположение может быть настроено по вашему выбору)
        int xPos = (i % 3) * imageParts[i].width(); // Размещение частей по горизонтали (в этом примере 3 части в ряд)
        int yPos = (i / 3) * imageParts[i].height(); // Размещение частей по вертикали

        pixmapItem->setPos(xPos, yPos); // Установка позиции элемента на сцене

        // Добавление элемента на графическую сцену
        scene->addItem(pixmapItem);

        QGraphicsRectItem *outlineRect = new QGraphicsRectItem(xPos, yPos, imageParts[i].width(), imageParts[i].height());
        outlineRect->setPen(QPen(Qt::black)); // Установка цвета контура
        scene->addItem(outlineRect);
    }
}

void HelpPuzzle::swapImageParts() {
    // Получаем список индексов частей
    QList<int> partIndexes = partPositions.keys();

    // Перемешиваем индексы
    std::shuffle(partIndexes.begin(), partIndexes.end(), std::mt19937(std::random_device()()));

    // Меняем позиции между собой
    for (int i = 0; i < partIndexes.size(); ++i) {
        QGraphicsPixmapItem *item = qgraphicsitem_cast<QGraphicsPixmapItem *>(scene->items().at(partIndexes[i]));
        if (item) {
            // Выбираем новую позицию для текущей части, чтобы она не перекрывалась с другими частями
            QPointF newPos;
            do {
                newPos = partPositions.value(partIndexes[i]);
            } while (newPos == item->pos()); // Проверяем, не равна ли новая позиция текущей позиции
            item->setPos(newPos);
            //partPositions[partIndexes[i]] = newPos;
        }
    }

    // Остановка таймера после первой смены позиций
    timer->stop();
}

void HelpPuzzle::mouseReleaseEvent(QMouseEvent *event) {
    // Проверяем, выбран ли какой-либо элемент для перемещения
    if (selectedItem) {
        // Получаем индекс элемента в графической сцене
        int index = scene->items().indexOf(selectedItem);

        // Получаем координаты выбранной части пазла из partPositions
        QPointF partCoordinates = partPositions.value(index);
        qreal xCoord1 = partCoordinates.x(); // Получаем координату x
        qreal yCoord1 = partCoordinates.y(); // Получаем координату y

        // Получаем текущие координаты позиции пазлинки после отпускания мыши
        QPointF releasedPosition = selectedItem->pos();
        qreal xCoord2 = releasedPosition.x(); // Получаем координату x
        qreal yCoord2 = releasedPosition.y(); // Получаем координату y

        if (qAbs(xCoord2 - xCoord1) < 30 && qAbs(yCoord2 - yCoord1) < 30)
        {
            // Получаем новые координаты для перемещения пазлинки
            QPointF newPosition(xCoord1, yCoord1); // Предположим, что xCoord и yCoord - новые координаты

            // Перемещаем пазлинку на новые координаты
            selectedItem->setPos(newPosition);
        }
    }
}
