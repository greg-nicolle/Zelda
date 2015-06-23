#ifndef HANDLE_THREAD_H
#define HANDLE_THREAD_H


#include <QMutex>
#include <QSize>
#include <QThread>
#include <QWaitCondition>


class RenderThread : public QThread
 {
     Q_OBJECT

 public:
     RenderThread(QObject *parent = 0);
     ~RenderThread();

//     void render(double centerX, double centerY, double scaleFactor, QSize resultSize);

 signals:
//     void renderedImage(const QImage &image, double scaleFactor);

 protected:
     void run();

 private:
     QMutex mutex;
     QWaitCondition condition;
//     double centerX;
//     double centerY;
//     double scaleFactor;
     QSize resultSize;
     bool restart;
     bool abort;
 };


#endif // HANDLE_THREAD_H
