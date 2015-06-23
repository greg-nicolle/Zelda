#include <QApplication>
#include <QGraphicsView>
#include "mapview.h"
#include <iostream>
#include "widget.h"

#define LMAX 500
#define HMAX 500


int main(int argc, char *argv[]) {
    QApplication game(argc, argv);

    Widget w;

    w.show();

    return game.exec();
}

