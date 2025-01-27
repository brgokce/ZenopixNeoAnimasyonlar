#ifndef SMOOTHLINESANIMATIONTHREAD_H
#define SMOOTHLINESANIMATIONTHREAD_H

#include <QObject>
#include <QWidget>
#include <QThread>
#include "core.h"
#include <QMutexLocker>

class SmoothLinesAnimationThread: public QThread
{
    Q_OBJECT
public:
    explicit SmoothLinesAnimationThread(Core* c, QObject *parent = nullptr);
    ~SmoothLinesAnimationThread();
    void run();
    void stop();
    void updateColors();
    double gaussian(double x, double mu, double sigma);
    cv::Scalar applyGaussianColor(double position, double lineThickness, cv::Scalar baseColor, double sigma);

signals:
    void processFinished(cv::Mat img);
    void colorsUpdated();

private:
    Core* core;
    bool running;
    QMutex mutex;
    double speed=1.0;

    void SmoothLineAnimationDraws(cv::Mat& img);
    cv::Mat histImg;
};

#endif // SMOOTHLINESANIMATIONTHREAD_H
