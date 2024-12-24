#ifndef SNOWFLAKEANIMATIONTHREAD_H
#define SNOWFLAKEANIMATIONTHREAD_H

#include "core.h"
#include <QObject>
#include <QWidget>
#include <QThread>
#include <QMutexLocker>

class SnowFlakeAnimationThread: public QThread
{
    Q_OBJECT
public:
    explicit SnowFlakeAnimationThread(Core* c, QObject *parent= nullptr);
    ~SnowFlakeAnimationThread();
    void run();
    void updateColors();
    void stop();

signals:
    void processFinished(cv::Mat img);
    void colorsUpdated();

private:
    Core* core;
    bool running;
    QMutex mutex;

};

#endif // SNOWFLAKEANIMATIONTHREAD_H
