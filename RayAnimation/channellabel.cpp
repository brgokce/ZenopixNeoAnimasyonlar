#include "channellabel.h"

ChannelLabel::ChannelLabel(QWidget *parent)
    : QLabel(parent)
{
    Lbutton= new buttonEventClass(&parentwidth, this);
    connect(Lbutton, &buttonEventClass::buttonPositionChanged, this, &ChannelLabel::updateButtonPosition);
    this->setFixedWidth(256);
    setScaledContents(true);
}

void ChannelLabel::updateButtonPosition(int globalX, int globalY)
{
    qDebug() << "Buton pozisyonu güncellendi: (" << globalX << ", " << globalY << ")";

    int minPos = 0;

    int maxPos = width() - Lbutton->width();

    XB = qBound(minPos, globalX, maxPos);

    double theta= qAtan(255.0/(width()-Lbutton->width()));

    double rawChannelColor = abs(XB) * qTan(theta);

    rawChannelColor = qBound(0.0, rawChannelColor, 255.0);

    ChannelColor = static_cast<int>((rawChannelColor /255.0) * 256);

    ChannelColor = qBound(0, ChannelColor, 255);

    emit ValueChanged(ChannelColor);

    qDebug()<<"değer xb:"<<XB;

    qDebug()<<"değer:"<<ChannelColor;

    this->update();
}
