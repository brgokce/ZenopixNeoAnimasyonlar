#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QWidget>
#include "opencv2/opencv.hpp"

class Core
{
public:
    Core();

    enum Animation_Mode
    {
        None,
        CircleMode,
        StarMode,
        SquareMode,
        SnowFlakeMode
    };

    Animation_Mode currMode= None;

    enum CircleAnimDir
    {
        Plus,
        Minus
    };

    enum onColor_Mode
    {
        none,
        Random,
        Steady,
    };
    onColor_Mode currcolorMode= none;

    enum on_speed_Mode
    {
        NoNe,
        Dinamic
    };

    on_speed_Mode currspeed=NoNe;

    enum NightSkyStarStates
    {
        Rising,
        On,
        Falling
    };

    struct NightSkyStar
    {
        cv::Point pos;
        double Brightness;
        NightSkyStarStates state;
        cv::Scalar color;
        int onTime;
        int starRadius;
    };

    struct NightSkyStarSetting
    {
        //radius settings
        int LowerRadiusLimit=1;
        int UpperRadiusLimit= 3;

        //time settings
        int LowerOnTime=1000;
        int UpperOnTime=5000;

        //speed
        double RisingSpeed=0.2;
        double FallingSpeed=0.05;

        //state on-off
        bool randomColorState=false;
        bool fixedColorState=false;
        bool useRGB=false;

        //animation
        int StarCount=50;

        //color
        QColor StarColor= QColor(190,190,190);
    };

    QVector<NightSkyStar>nightSkyStars;
    NightSkyStarSetting setting;


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

    cv::Scalar RandomColor();
    cv::Mat Image;
    cv::Scalar color= cv::Scalar(0,0,0);
};

#endif // CORE_H
