#ifndef WIDGET_H
#define WIDGET_H


#include <QWidget>


namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

protected:
    Ui::Widget *ui;

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void update_vie(int pv);
};


#endif // WIDGET_H
