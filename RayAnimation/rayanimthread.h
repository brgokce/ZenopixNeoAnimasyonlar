#ifndef RAYANIMTHREAD_H
#define RAYANIMTHREAD_H

#include <QObject>
#include <QWidget>
#include <QThread>
#include "core.h"
#include <QMutexLocker>

class RayAnimThread: public QThread
{
    Q_OBJECT
public:
    explicit RayAnimThread(Core* c, QObject *parent= nullptr);
    ~RayAnimThread();
    void run();
    void updateColors();
    void stop();

    void onHueChanged(int hue);
    void onSaturationChanged(int saturation);
    void onBrightnessChanged(int brightness);

signals:
    void processFinished(cv::Mat img);
    void colorsUpdated();

private:
    Core* core;
    bool running;
    QMutex mutex;
    HSBColorWheel* hsbcolorwheel;

};

#endif // RAYANIMTHREAD_H
