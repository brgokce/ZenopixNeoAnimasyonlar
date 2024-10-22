#include "labelclass.h"
#include "qevent.h"
#include "qpushbutton.h"
#include "cmath"
#include <QtMath>

labelCLASS::labelCLASS(QWidget *parent)
    : QLabel(parent)
{
    Lbutton= new buttonEventClass(&parentwidth, this);
    connect(Lbutton, &buttonEventClass::buttonPositionChanged, this, &labelCLASS::updateButtonPosition);
    Lbutton->setStyleSheet("background-color:rgba(0,0,0,0);");
    this->setFixedWidth(256);
}

void labelCLASS::updateButtonPosition(int globalX, int globalY)
{
    qDebug() << "Buton pozisyonu güncellendi: (" << globalX << ", " << globalY << ")";

    XB= globalX;

    double theta= qAtan(255.0/(width()-Lbutton->width()));

    ChannelColor= static_cast<int>(abs(XB) * qTan(theta));

    emit ValueChanged(ChannelColor);

    qDebug()<<"değer xb:"<<XB;

    qDebug()<<"değer xb:"<<width();

    qDebug()<<"değer:"<<ChannelColor;
}
