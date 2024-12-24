#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QWidget>
#include "opencv2/opencv.hpp"

class Core
{
public:
    Core();

struct SmoothDynamicSettings
{
    int position;
    cv::Scalar currColor;
    cv::Scalar startColor;
    cv::Scalar endColor;
};

struct SmoothLineAnimSettings
{
    int Delta= 20;
    int lineSize= 7;
    int offset=0;
    int currSmoothLineColorIndex=0;
    int dirAngle=0;

    cv::Scalar color= cv::Scalar(0,0,0);
    QColor background_color= QColor(0,0,0);
    QVector<QColor> SmoothLinesC= {QColor(255,0,0)};

    bool userChangeSpeed=false;
    bool randomColorEn= false;
    bool useRGB= false;
    bool useColorWheel=false;
    bool useHSB= false;
    bool inverse= false;

    double Speed= 1.0;
    std::vector<SmoothDynamicSettings> Sline;
};

struct RGBWidgetValues
{
    uint8_t RWidgetValue=0;
    uint8_t GWidgetValue=0;
    uint8_t BWidgetValue=0;

    QImage RImage= QImage(256,1, QImage::Format_RGB888);
    QImage GImage= QImage(256,1, QImage::Format_RGB888);
    QImage BImage= QImage(256,1, QImage::Format_RGB888);
};

RGBWidgetValues rgbWidgetValues;

SmoothLineAnimSettings StaticSmoothSet;

cv::Scalar RandomColor();
cv::Mat Image;

};

#endif // CORE_H
