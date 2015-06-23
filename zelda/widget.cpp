#include "widget.h"
#include "ui_widget.h"
#include <qgraphicsview.h>
#include "map.h"
#include <iostream>
#define LMAX 500
#define HMAX 500

/* Constructeur */
Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);
    map *scene = new map(ui->map_view);

    ui->map_view->setScene(scene);

    ui->map_view->centerOn(0,0);
    connect(scene, SIGNAL(update_pv(int)), this, SLOT(update_vie(int)));
}

/* Destructeur */
Widget::~Widget() {
    delete ui;
}
 void Widget::update_vie(int pv){
     ui->vie->setValue(pv);
 }
