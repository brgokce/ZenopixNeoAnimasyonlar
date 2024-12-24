#include "smoothlinesanimationthread.h"
#include <QMutexLocker>

SmoothLinesAnimationThread::SmoothLinesAnimationThread(Core* c, QObject *parent): QThread(parent), core(c), running(true)
{

}

SmoothLinesAnimationThread::~SmoothLinesAnimationThread()
{
    stop();
    wait();
}

void SmoothLinesAnimationThread::stop()
{
    QMutexLocker locker(&mutex);
    running = false;
}

void SmoothLinesAnimationThread::updateColors()
{
    emit colorsUpdated();
}

double SmoothLinesAnimationThread::gaussian(double x, double mu, double sigma) {
    return exp(-pow(x - mu, 2) / (2 * pow(sigma, 2)));
}

cv::Scalar SmoothLinesAnimationThread::applyGaussianColor(double position, double lineThickness, cv::Scalar baseColor, double sigma)
{
    double mu = lineThickness / 2.0;
    double normalizeP = std::abs(position) / (lineThickness / 2.0);
    double brightness = gaussian(normalizeP, 0.0, sigma);
    brightness = std::min(std::max(brightness, 0.0), 1.0);

    cv::Scalar ResultColor;
    ResultColor[0] = baseColor[0] * brightness;
    ResultColor[1] = baseColor[1] * brightness;
    ResultColor[2] = baseColor[2] * brightness;
    ResultColor[3] = baseColor[3];

    return ResultColor;
}

void SmoothLinesAnimationThread::SmoothLineAnimationDraws(cv::Mat& img)
{
    img= cv::Mat(280,390, CV_8UC3, cv::Scalar(0,0,0));
    img.setTo(cv::Scalar(core->StaticSmoothSet.background_color.blue(), core->StaticSmoothSet.background_color.green(), core->StaticSmoothSet.background_color.red()));
    Core::SmoothDynamicSettings lines;

    if(core->StaticSmoothSet.offset>=core->StaticSmoothSet.Delta){
        if(core->StaticSmoothSet.currSmoothLineColorIndex>=core->StaticSmoothSet.SmoothLinesC.size()){
            core->StaticSmoothSet.currSmoothLineColorIndex=0;
        }

        cv::Scalar lineColor = cv::Scalar(core->StaticSmoothSet.SmoothLinesC[core->StaticSmoothSet.currSmoothLineColorIndex].red(),
                                          core->StaticSmoothSet.SmoothLinesC[core->StaticSmoothSet.currSmoothLineColorIndex].green(),
                                          core->StaticSmoothSet.SmoothLinesC[core->StaticSmoothSet.currSmoothLineColorIndex].blue());

        core->StaticSmoothSet.currSmoothLineColorIndex++;

        Core::SmoothDynamicSettings newSmoothLineLeft= {0, lineColor};
        core->StaticSmoothSet.Sline.push_back(newSmoothLineLeft);
        core->StaticSmoothSet.offset= 0;
    }

    cv::Scalar previousColor = cv::Scalar(0, 0, 0);
    cv::Scalar currentColor;

    for(const auto& line: core->StaticSmoothSet.Sline){
        int newX= line.position;
        if (newX > 0 && newX < img.cols) {
            if (previousColor == cv::Scalar(255, 0, 0)) {
                previousColor = line.currColor;
            }

            double transitionFactor = static_cast<double>(line.position) / img.cols;
            currentColor[0] = previousColor[2] + (line.currColor[2] - previousColor[2]) * transitionFactor;
            currentColor[1] = previousColor[1] + (line.currColor[1] - previousColor[1]) * transitionFactor;
            currentColor[2] = previousColor[0] + (line.currColor[0] - previousColor[0]) * transitionFactor;
            currentColor[3] = previousColor[3];

            for (int dx = -core->StaticSmoothSet.lineSize / 2; dx <= core->StaticSmoothSet.lineSize / 2; ++dx) {
                int x = newX + dx;
                if (x >= 0 && x < img.cols) {
                    for (int y = 0; y < img.rows; ++y) {
                        img.at<cv::Vec3b>(y, x) = cv::Vec3b(currentColor[0], currentColor[1], currentColor[2]);
                    }
                }
            }
            previousColor = currentColor;
    }
}
    for(auto&line: core->StaticSmoothSet.Sline){
        line.position+= static_cast<int>(5*speed);
    }

    core->StaticSmoothSet.Sline.erase(std::remove_if(core->StaticSmoothSet.Sline.begin(),
                                                     core->StaticSmoothSet.Sline.end(), [&](const Core::SmoothDynamicSettings& line){
                                                        return (line.position>img.cols);}), core->StaticSmoothSet.Sline.end());

    core->StaticSmoothSet.offset+= static_cast<int>(5*speed);

    if(core->StaticSmoothSet.offset>= core->Image.cols){
        core->StaticSmoothSet.offset=0;
    }
}

void SmoothLinesAnimationThread::run()
{
    while (running) {
        QMutexLocker locker(&mutex);

        if (!running)
            break;

        SmoothLineAnimationDraws(core->Image);
        emit processFinished(core->Image);

        if (core->StaticSmoothSet.userChangeSpeed){
            msleep(core->StaticSmoothSet.Speed);
            qDebug()<<"hız"<<core->StaticSmoothSet.Speed;
        }
        else
        {
            msleep(100);
        }
    }
}
