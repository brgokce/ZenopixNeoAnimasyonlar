#include "core.h"
#include <QRandomGenerator>

Core::Core()
{

}

cv::Scalar Core::RandomColor()
{
    int red= QRandomGenerator::global()->bounded(256);
    int green= QRandomGenerator::global()->bounded(256);
    int blue= QRandomGenerator::global()->bounded(256);
    return cv::Scalar(blue,green,red);
}
