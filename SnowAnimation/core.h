#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QWidget>
#include "opencv2/opencv.hpp"

class Core
{
public:
    Core();

    struct SnowFlakeAnimationDynamicParameters
    {
        int Angle;
        int dir;

        cv::Point startPoint;
        cv::Point endPoint;

        QPoint position;

        cv::Scalar currColor;

    };

    struct SnowFlakeAnimationParameters
    {
        int AnimSpeed=1;
        int NumberOfSnowFlake=1;

        double ExtentSnowFlake=5;

        cv::Scalar color= cv::Scalar(0,0,0);

        bool useRGB=false;
        bool userChangSpeed=false;
        bool randomColorEnable= false;
        bool brightnessChanged= false;
        bool SteadyColorEnable=false;

        int brightness=0;

        QVector<SnowFlakeAnimationDynamicParameters> snowFlakeVector;
    };

    SnowFlakeAnimationParameters snowFlakeStaticParameters;

    cv::Scalar RandomColor();
    cv::Mat Image;

};

#endif // CORE_H
