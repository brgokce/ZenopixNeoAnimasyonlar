#include "rgblabel.h"

RgbLabel::RgbLabel(QWidget *parent): QLabel(parent)
{
    RButton= new RgbButtonClass(&parentwidth, this);
    connect(RButton, &RgbButtonClass::buttonPosChanged, this, &RgbLabel::UpdateButtonPos);
    this->setFixedWidth(256);
    setScaledContents(true);
}

void RgbLabel::UpdateButtonPos(int globalX, int globalY)
{
    qDebug() << "Buton pozisyonu güncellendi: (" << globalX << ", " << globalY << ")";

    int minPos = 0;

    int maxPos = width() - RButton->width();

    XB = qBound(minPos, globalX, maxPos);

    double theta= qAtan(255.0/(width()-RButton->width()));

    double rawChannelColor = abs(XB) * qTan(theta);

    rawChannelColor = qBound(0.0, rawChannelColor, 255.0);

    channelC = static_cast<int>((rawChannelColor /255.0) * 256);

    channelC = qBound(0, channelC, 255);

    emit ValueChanged(channelC);

    qDebug()<<"değer xb:"<<XB;

    qDebug()<<"değer:"<<channelC;

    this->update();
}
