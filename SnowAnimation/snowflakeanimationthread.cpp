#include "snowflakeanimationthread.h"
#include "core.h"

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
    core->Image= cv::Mat(291,461,CV_8UC3,cv::Scalar(0,0,0));
}
