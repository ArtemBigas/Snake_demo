#include <QPainter>
#include <QTime>
#include "snake.h"

Snake::Snake(QWidget *parent) : QWidget(parent) {

    setStyleSheet("background-color:black;");
    leftDirection = false;
    rightDirection = true;
    upDirection = false;
    downDirection = false;
    inGame = true;

    resize(B_WIDTH, B_HEIGHT);
    loadImages();
    initGame();
}

void Snake::loadImages() {//тело змеи
//Если вставлять как картинки
   /* dot.load("green.jpg");
    head.load("red.png");
    apple.load("apple.png");*/

    //Если заполнить как квадрат
    dot = QImage(DOT_SIZE, DOT_SIZE, QImage::Format_ARGB32);
    dot.fill(Qt::yellow);
    head = QImage(DOT_SIZE, DOT_SIZE, QImage::Format_ARGB32);
    head.fill(Qt::red);
    apple = QImage(DOT_SIZE, DOT_SIZE, QImage::Format_ARGB32);
    apple.fill(Qt::green);
}

void Snake::initGame() {
     //создание змеи
    dots = 3;

    for (int z = 0; z < dots; z++) {
        x[z] = 50 - z * 10;
        y[z] = 50;
    }

    locateApple();//определяем позицию яблока

    timerId = startTimer(DELAY);//запускаем таймер, с скоростью DELAY
}

void Snake::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);

    doDrawing();
}

void Snake::doDrawing() {

    QPainter qp(this);

    if (inGame) {

        qp.drawImage(apple_x, apple_y, apple);

        for (int z = 0; z < dots; z++) {
            if (z == 0) {
                qp.drawImage(x[z], y[z], head);
                qp.setPen(Qt::black);//цвет линии
                qp.drawRect(x[z], y[z], dot.width(), dot.height());//рисуем линию(координаты ячейки, ширина и высота её)
            } else {
                qp.drawImage(x[z], y[z], dot);
                qp.setPen(Qt::black);
                qp.drawRect(x[z], y[z], dot.width(), dot.height());
            }
        }

    } else {

        gameOver(qp);
    }
}

void Snake::gameOver(QPainter &qp) {

    QString message = "Game over";
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width(message);

    qp.setPen(QColor(Qt::white));
    qp.setFont(font);
    int h = height();
    int w = width();

    qp.translate(QPoint(w/2, h/2));
    qp.drawText(-textWidth/2, 0, message);
}

void Snake::checkApple() {//проверяем столкновение с яблоком

    if ((x[0] == apple_x) && (y[0] == apple_y)) {//Если голова сталкивается с яблоком,

        dots++;//о мы увеличиваем количество «частей» тела змеи.
        locateApple();//случайным образом позиционируем новое яблоко
    }
}

void Snake::move() {
//определяет, что вторая «часть» движется туда, где была первая, третья — туда, где была вторая и т.д
    for (int z = dots; z > 0; z--) {//изменение начинается с хвоста
        x[z] = x[(z - 1)];//координата x части 3, становится равна координате x части 2
        y[z] = y[(z - 1)];
    }

    if (leftDirection) {
        x[0] -= DOT_SIZE;//координата по шкале х становится меньше на размер тела
    }

    if (rightDirection) {
        x[0] += DOT_SIZE;
    }

    if (upDirection) {
        y[0] -= DOT_SIZE;
    }

    if (downDirection) {
        y[0] += DOT_SIZE;
    }
}

void Snake::checkCollision() {//столкновения

    for (int z = dots; z > 0; z--) {//с своей частью

        if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {//если координата совпадет с координатой любой её части
            inGame = false;
        }
    }
//если змея столкнется с стенкой,в комментариях вариант без стен
    if (y[0] >= B_HEIGHT) {
        inGame = false;
        //y[0] = 1;
    }

    if (y[0] < 0) {
        inGame = false;
        //y[0]= B_HEIGHT-1;
    }

    if (x[0] >= B_WIDTH) {
        inGame = false;
        //x[0] = 1;
    }

    if (x[0] < 0) {
        inGame = false;
        //x[0]= B_WIDTH-1;
    }

    if(!inGame) {//если inGame==false, таймер заканчивается
        killTimer(timerId);
    }
}

void Snake::locateApple() {//прописать чтобы яблоко не появлялось на месте змеи

    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    int r = qrand() % RAND_POS;
    apple_x = (r * DOT_SIZE);

    r = qrand() % RAND_POS;
    apple_y = (r * DOT_SIZE);
}

void Snake::timerEvent(QTimerEvent *e) {//игровой цикл

    Q_UNUSED(e);

    if (inGame) {//если inGame==true

        checkApple();//проверяем столкновение с яблоком
        checkCollision();//проверяем столкновение с стеной или с телом
        move();//двигаемся
    }

    repaint();
}

void Snake::keyPressEvent(QKeyEvent *e) {

    int key = e->key();//извлекаем числовое значение int key из ивента e

    if ((key == Qt::Key_Left) && (!rightDirection)) {//если есть ивент Key_Left, и rightDirection == false(чтобы нельзя было повернуть на 180 градусов)
        leftDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((key == Qt::Key_Right) && (!leftDirection)) {
        rightDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((key == Qt::Key_Up) && (!downDirection)) {
        upDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    if ((key == Qt::Key_Down) && (!upDirection)) {
        downDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    QWidget::keyPressEvent(e);
}
