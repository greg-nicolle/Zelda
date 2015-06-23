#include "item.h"

Item::Item()
{
}
Item::~Item(){
}

void Item::set_image(QPixmap tmp){
    image = tmp;
}
QRectF Item::boundingRect() const {
    return QRectF(-15, -20, 30, 30);
}

void Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
}
