#include "labelclass.h"
#include "qevent.h"
#include "qpushbutton.h"
#include "cmath"

labelCLASS::labelCLASS(QWidget *parent)
    : QLabel(parent)
{
    Lbutton= new buttonEventClass(&parentwidth, this);
    connect(Lbutton, &buttonEventClass::buttonPositionChanged, this, &labelCLASS::updateButtonPosition);
}

void labelCLASS::updateButtonPosition(int globalX, int globalY)
{
    qDebug() << "Buton pozisyonu güncellendi: (" << globalX << ", " << globalY << ")";

    XB= globalX;

    ChannelColor= static_cast<int>(abs(XB) * tan(255.0 /(width()- Lbutton->width())));

    emit ValueChanged(ChannelColor);

    qDebug()<<"değer xb:"<<XB;

    qDebug()<<"değer:"<<ChannelColor;
}
