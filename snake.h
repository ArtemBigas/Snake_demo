#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QKeyEvent>
#include <QApplication>
#include <QScreen>//расчет разрешения экрана
class Snake : public QWidget {

public:
    Snake(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);

private:
    QImage dot;
    QImage head;
    QImage apple;

//размер игрового поля
     int B_WIDTH;
     int B_HEIGHT;

    int DOT_SIZE;//размер яблока и тела змеи
    int ALL_DOTS;//максимальное количество возможных точек на доске размером 10х10 пикселей((300*300)/(10*10))
     int RAND_POS;//используется для вычисления случайной позиции яблока
    static const int DELAY = 140;//скорость игры

    int timerId;
    int dots;
    int apple_x;
    int apple_y;
//координаты (x;y) всех «частей» тела змеи
    std::vector <int> x;
    std::vector <int> y;

    bool leftDirection;
    bool rightDirection;
    bool upDirection;
    bool downDirection;
    bool inGame;

    void loadImages();
    void initGame();
    void locateApple();
    void checkApple();
    void checkCollision();
    void move();
    void doDrawing();
    void gameOver(QPainter &);
};

#endif // SNAKE_H
