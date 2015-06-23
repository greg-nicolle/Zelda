#ifndef ITEM_H
#define ITEM_H

#include <QGraphicsItem>

class Item : public QGraphicsItem
{
public:
    Item();
    ~Item();
    void set_image(QPixmap tmp);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    QRectF boundingRect() const;

signals:

public slots:

protected:
    QPixmap image;
};

#endif // ITEM_H
