#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QKeyEvent>

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
    static const int B_WIDTH = 300;
    static const int B_HEIGHT = 300;

    static const int DOT_SIZE = 10;//размер яблока и тела змеи
    static const int ALL_DOTS = 900;//максимальное количество возможных точек на доске размером 10х10 пикселей((300*300)/(10*10))
    static const int RAND_POS = 29;//используется для вычисления случайной позиции яблока
    static const int DELAY = 140;//скорость игры

    int timerId;
    int dots;
    int apple_x;
    int apple_y;
//координаты (x;y) всех «частей» тела змеи
    int x[ALL_DOTS];
    int y[ALL_DOTS];

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
