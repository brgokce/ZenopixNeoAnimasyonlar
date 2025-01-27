#include "snowflakeanimationthread.h"
#include "core.h"
#include "qtimer.h"
#include <QRandomGenerator>
#include <QtMath>
#include <thread>
#include <QElapsedTimer>

SnowFlakeAnimationThread::SnowFlakeAnimationThread(Core*c, QObject *parent): QThread(parent), core(c), running(true)
{
}

SnowFlakeAnimationThread:: ~SnowFlakeAnimationThread()
{
    stop();
    wait();
}

void SnowFlakeAnimationThread::stop()
{
    QMutexLocker locker(&mutex);
    running= false;
}

void SnowFlakeAnimationThread::updateColors()
{
    emit colorsUpdated();
}

void SnowFlakeAnimationThread::run()
{
    core->Image= cv::Mat(290,460, CV_8UC3, cv::Scalar(0,0,0));
    Core::NightSkyStar animation;

    while(true){
    switch (core->currMode) {
    case Core::None:
        break;
    case Core::CircleMode:
        circleAnimation(core->Image);
        break;
    case Core::StarMode:
        starAnimation(core->Image);
        break;
    case Core::SquareMode:
        squareAnimation(core->Image);
        break;
    case Core::SnowFlakeMode:
        snowflakeAnimation(core->Image);
        break;
    default:
        break;
    }
  }
}

void SnowFlakeAnimationThread::time()
{
    qDebug()<<"timer slot activated";
}

void SnowFlakeAnimationThread::circleAnimation(cv::Mat& img)
{
    core->nightSkyStars.clear();
}

void SnowFlakeAnimationThread::starAnimation(cv::Mat& img)
{

}


void SnowFlakeAnimationThread::squareAnimation(cv::Mat& img)
{

}

void SnowFlakeAnimationThread::snowflakeAnimation(cv::Mat& img)
{

}
