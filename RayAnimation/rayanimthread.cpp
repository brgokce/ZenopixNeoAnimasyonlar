#include "rayanimthread.h"
#include <QRandomGenerator>
#include <QMutexLocker>
#include "hsbcolorwheel.h"

RayAnimThread::RayAnimThread(Core* c, QObject *parent)
    : QThread(parent), core(c), running(true)
{

}

RayAnimThread::~RayAnimThread()
{
    stop();
    wait();
}

void RayAnimThread::stop()
{
    QMutexLocker locker(&mutex);
    running = false;
}

void RayAnimThread::updateColors()
{
    emit colorsUpdated();
}

void RayAnimThread::run()
{
    if (!core->rayanimset.userChangedSpeed)
    {
        // Varsayılan hız değerini kullan
        core->rayanimset.Speed = 100; // İlk hız
    }

    core->rayanimset.Ray_Lines.clear();

    cv::Mat Img = cv::Mat(221 ,371, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::cvtColor(Img, Img, cv::COLOR_BGR2RGB);
    core->Img = Img;

    QPoint center(core->Img.cols / 2, core->Img.rows / 2);

    int blinkCounter = 0;
    int oldNumberOfRay = 1;
    int oldnumberin=1;// Store the initial number of rays

    // Initialize rays based on the current number of rays
    for (int r = 0; r < core->rayanimset.NumberOfRay; r++)
    {
        Core::DynamicRayAnimSet dynamicRay;
        dynamicRay.Position = center;

        double angleStep = 360.0 / core->rayanimset.NumberOfRay;

        dynamicRay.Angle = r * angleStep;
        dynamicRay.radian = round(dynamicRay.Angle * CV_PI / 180.0);
        dynamicRay.dir = QRandomGenerator::global()->bounded(0, 2) ? 1 : -1;
        dynamicRay.startAngle= QRandomGenerator::global()->bounded(360);
        dynamicRay.EndPoint= cv::Point(-1,-1);
        dynamicRay.SecondPoint = cv::Point(-1, -1);
        dynamicRay.ray_in= core->rayanimset.Ray_bore;
        dynamicRay.Long= QRandomGenerator::global()->bounded(10,100);


        if(core->Img.rows<core->Img.cols)
        {
            dynamicRay.deltah1= core->Img.rows*0.5 * 0.9;

            core->Img.rows = 2* (dynamicRay.ray_in + dynamicRay.deltah1);

            core->spinbox->setMinimum(1);

            core->spinbox->setMaximum(dynamicRay.deltah1);

            core->rayanimset.Ray_bore = core->spinbox->value();

            dynamicRay.deltaw2= ((core->Img.rows* 0.5) /dynamicRay.ray_in) * core->Img.rows*0.5;
        }

        else
        {
            dynamicRay.deltaw1= core->Img.cols*0.5* 0.9;

            core->Img.cols = 2* (dynamicRay.deltaw1 + dynamicRay.deltaw2);

            core->spinbox->setMinimum(1);

            core->spinbox->setMaximum(dynamicRay.deltaw2);

            core->rayanimset.Ray_bore = core->spinbox->value();

            dynamicRay.ray_in= ((core->Img.cols*0.5)/dynamicRay.deltaw2) * core->Img.rows*0.5;

        }

        if (core->rayanimset.randomColorEnable)
            dynamicRay.dColor = core->RandomColor();

        else if(core->rayanimset.useHSB)
            dynamicRay.dColor = core->HSBcolor;

        else if(core->rayanimset.useColorWheel)
            dynamicRay.dColor = core->currentRayColor;
        else if(core->rayanimset.useRGB)
            dynamicRay.dColor= core->RGBcolor;

        else
            dynamicRay.dColor = core->rayanimset.color;



        core->rayanimset.Ray_Lines.append(dynamicRay);
    }

    while (running)
    {

        QMutexLocker locker(&mutex);
        if (!running)
            break;

        if (oldNumberOfRay != core->rayanimset.NumberOfRay || oldnumberin!= core->rayanimset.Ray_bore)
        {
            oldNumberOfRay = core->rayanimset.NumberOfRay;
            oldnumberin= core->rayanimset.Ray_bore;

            core->rayanimset.Ray_Lines.clear();


            for (int r = 0; r < core->rayanimset.NumberOfRay; r++)
            {
                Core::DynamicRayAnimSet dynamicRay;
                dynamicRay.Position = center;

                double angleStep = 360.0 / core->rayanimset.NumberOfRay;

                dynamicRay.Angle = r * angleStep;
                dynamicRay.radian = round(dynamicRay.Angle * CV_PI / 180.0);
                dynamicRay.dir = QRandomGenerator::global()->bounded(0, 2) ? 1 : -1;
                dynamicRay.startAngle= QRandomGenerator::global()->bounded(360);
                dynamicRay.EndPoint= cv::Point(-1,-1);
                dynamicRay.SecondPoint = cv::Point(-1, -1);
                dynamicRay.ray_in= core->rayanimset.Ray_bore;
                dynamicRay.Long= QRandomGenerator::global()->bounded(10,100);

                if(core->Img.rows<core->Img.cols)
                {
                    dynamicRay.deltah1= core->Img.rows*0.5 * 0.9;

                    core->Img.rows = 2* (dynamicRay.ray_in + dynamicRay.deltah1);

                    core->spinbox->setMinimum(1);

                    core->spinbox->setMaximum(dynamicRay.deltah1);

                    core->rayanimset.Ray_bore = core->spinbox->value();

                    dynamicRay.deltaw2= ((core->Img.rows* 0.5) /dynamicRay.ray_in) * core->Img.rows*0.5;
                }

                else
                {
                    dynamicRay.deltaw1= core->Img.cols*0.5* 0.9;

                    core->Img.cols = 2* (dynamicRay.deltaw1 + dynamicRay.deltaw2);

                    core->spinbox->setMinimum(1);

                    core->spinbox->setMaximum(dynamicRay.deltaw2);

                    core->rayanimset.Ray_bore = core->spinbox->value();

                    dynamicRay.ray_in= ((core->Img.cols*0.5)/dynamicRay.deltaw2) * core->Img.rows*0.5;

                }

                if (core->rayanimset.randomColorEnable)
                    dynamicRay.dColor = core->RandomColor();

                else if(core->rayanimset.useHSB)
                    dynamicRay.dColor = core->HSBcolor;

                else if(core->rayanimset.useColorWheel)
                    dynamicRay.dColor = core->currentRayColor;

                else if(core->rayanimset.useRGB)
                    dynamicRay.dColor= core->RGBcolor;

                else
                    dynamicRay.dColor = core->rayanimset.color;

                core->rayanimset.Ray_Lines.append(dynamicRay);

            }
        }

        core->Img = cv::Mat(221, 371, CV_8UC3, cv::Scalar(0, 0, 0));

        for (int ry = 0; ry < core->rayanimset.Ray_Lines.length(); ry++)
        {
            Core::DynamicRayAnimSet& ray = core->rayanimset.Ray_Lines[ry];
            int x_start = ray.Position.x();
            int y_start = ray.Position.y();

            int x_second; int y_second;

            if(ray.SecondPoint!= cv::Point(-1,1))
            {
                ray.SecondPoint= cv::Point(x_start,y_start);

                x_second = x_start + ray.ray_in * cos(ray.Angle * CV_PI / 180.0);
                y_second = y_start - ray.ray_in * sin(ray.Angle * CV_PI / 180.0);
                cv::line(core->Img, cv::Point(x_start,y_start), cv::Point(x_second, y_second),cv::Scalar(0,0,0),core->rayanimset.tickness);
            }

            if(ray.EndPoint!= cv::Point(-1,-1))
            {
                ray.EndPoint= cv::Point(x_second, y_second);

                int x_end = x_second + ray.Long * cos(ray.Angle * CV_PI / 180.0);
                int y_end = y_second - ray.Long * sin(ray.Angle * CV_PI / 180.0);

                cv::line(core->Img, cv::Point(x_second,y_second), cv::Point(x_end, y_end),cv::Scalar(0,0,0),core->rayanimset.tickness);
            }

            int x_end = x_second + ray.Long * cos(ray.Angle * CV_PI / 180.0);
            int y_end = y_second - ray.Long * sin(ray.Angle * CV_PI / 180.0);

            cv::line(core->Img, cv::Point(x_second,y_second), cv::Point(x_end, y_end),ray.dColor,core->rayanimset.tickness);

            ray.EndPoint= cv::Point(x_end,y_end);
            ray.SecondPoint= cv::Point(x_second,y_second);
            ray.ray_in= QRandomGenerator::global()->bounded(core->rayanimset.Ray_bore/2,core->rayanimset.Ray_bore);


            ray.Angle+= ray.dir* 5.0;
            if(ray.Angle>360)
            {
                ray.Angle-=360;
            }
            else if(ray.Angle<0)
            {
                ray.Angle+=360;
            }

            if (core->rayanimset.randomColorEnable)
            {
                if (blinkCounter % 10 == 0)
                {
                    ray.dColor = core->RandomColor();
                }
            }


        }

        emit processFinished(core->Img);

        msleep(core->rayanimset.Speed);

        blinkCounter++;
    }
}
