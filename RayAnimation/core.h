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
        cv::Scalar color= cv::Scalar(255,255,255);
        int Ray_bore =1;
        bool randomColorEnable= false;
        bool userChangedSpeed = false;
        bool useColorWheel = false;
        bool useHSB=false;
        int brightness=0;

        int lastHue = -1;
        int lastSaturation = -1;
        int lastBrightness = -1;

        QVector<DynamicRayAnimSet> Ray_Lines;

    };
    RayAnimationSettings rayanimset;
    cv::Mat Img;
    QSpinBox* spinbox;
    cv::Scalar currentRayColor;
    cv::Scalar HSBcolor;


    cv::Scalar RandomColor();
};

#endif // CORE_H
