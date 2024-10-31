#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QWidget>
#include "hsbcolorwheel.h"
#include "opencv2/opencv.hpp"
#include "qslider.h"
#include "qspinbox.h"

class Core
{
public:
    Core();


    struct DynamicRayAnimSet
    {
        int Angle;
        QPoint Position;
        cv::Scalar dColor;
        int dir;
        int radian;
        int startAngle;
        cv::Point EndPoint;
        cv::Point SecondPoint;
        int ray_in;
        int Long;
        int deltah1;
        int deltaw1; int deltaw2;

    };

    struct RayAnimationSettings
    {
        int NumberOfRay=1;
        int Speed=1;
        int tickness=1;
        cv::Scalar color= cv::Scalar(0,0,0);
        int Ray_bore =1;
        bool randomColorEnable= false;
        bool userChangedSpeed = false;
        bool useColorWheel = false;
        bool useHSB=false;
        bool useRGB= false;
        bool usePalette= false;
        int brightness=0;

        int lastHue = -1;
        int lastSaturation = -1;
        int lastBrightness = -1;
        int selectedIndex=0;

        QVector<DynamicRayAnimSet> Ray_Lines;

    };

    struct RGBWidgetValues
    {
        uint8_t RWidgetValue=0;
        uint8_t GWidgetValue=0;
        uint8_t BWidgetValue=0;


        QImage Rimage = QImage(256,1, QImage::Format_RGB888);
        QImage GImage = QImage(256,1,QImage::Format_RGB888);
        QImage BImage = QImage(256,1,QImage::Format_RGB888);

    };

    RGBWidgetValues rgbWidgetValues;

    RayAnimationSettings rayanimset;
    cv::Mat Img;
    QSpinBox* spinbox;
    cv::Scalar currentRayColor;
    cv::Scalar HSBcolor;
    cv::Scalar RGBcolor;
    std::vector<cv::Scalar> PaletteColor;
    cv::Scalar RandomColor();
    QColor PColor;
};

#endif // CORE_H
