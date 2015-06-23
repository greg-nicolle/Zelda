#ifndef PERSONNAGE_H
#define PERSONNAGE_H


#include "QGraphicsPixmapItem"
#include <qmutex.h>
#include <qpainter.h>
#include "item.h"

class personnage:public Item
{
protected:
    int speed;
    QMutex mutex;
    int deplacement_x;
    int deplacement_y;
    QPixmap img_deplacement[4][11];
    QPixmap img_attaque[4][11];
    QPixmap img_mort[7];
    bool isfighting;
    int nb_attaque;
    int tmp_attaque;
    int curentimage;
    int curentattaque;
    int curentmort;
    int direction;
    int pv;

    bool alive;
    void init_images(QString fichier);
    void init_images_attaque(QString fichier);
    void init_images_mort(QString fichier);
    void changement_deplacement();
    void changement_attaque();

public:
    personnage();
    ~personnage();
    QPixmap get_image();
    QPointF get_position();
    void set_position(qreal x, qreal y);
    void degat(int d);
    void set_pv(int d);
    void move_back();

    int get_pv();

    void collision(QRectF vilain_bords, QPointF vilain_pos, qreal value);

    bool get_fighting();
    void set_fighting(bool value);

    void move();
    void set_deplacement_x(int dep);
    void set_deplacement_y(int dep);
//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    QRectF boundingRect() const;

    void set_attaque(bool atta);
    void attaque();
    bool get_alive();
    void set_alive(bool ali);
};


#endif // PERSONNAGE_H
