#include "rgbbuttonclass.h"
#include "qevent.h"

RgbButtonClass::RgbButtonClass(int *parentWdt, QWidget *parent): QPushButton(parent), dragging(false)
{
    setFixedSize(20,30);
    setStyleSheet("background-color:rgba(0,0,0,0);");
    setIcon(QIcon("C:/Users/ASUS/Desktop/channelButton.png"));
    setIconSize(size());

    parentWidth= parentWdt;
}

void RgbButtonClass::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragging = true;
        PreviousPos= event->globalPos();
        event->accept();
    }
}
void RgbButtonClass::mouseMoveEvent(QMouseEvent *event)
{
    if(dragging && (event->buttons() & Qt::LeftButton))
    {
        currentPos = event->globalPos();
        DeltaX= currentPos.x() - PreviousPos.x();

        int newPosX = x() + DeltaX;

        if (newPosX < 0) newPosX = 0;
        if(newPosX>*parentWidth-width()) newPosX= *parentWidth-width();
        move(newPosX, y());

        PreviousPos= currentPos;

        emit buttonPosChanged(newPosX, currentPos.y());
        currentValue += (DeltaX > 0) ? 1 : -1;
        currentValue = qBound(0, currentValue, 255);
        emit ButtonValueChanged(currentValue);

        if (!moveState)
        {
            moveState = true;
        }
    }
}
void RgbButtonClass::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragging = false;
        pressed = false;

        if (!moveState || parentWidget()->styleSheet() == "background-color:rgb(73,87,102);")
        {
            emit clicked(true);
        }
        else
        {
            moveState = false;
        }

        emit ItemReleased();
        event->accept();
    }
}

void RgbButtonClass::leaveEvent(QEvent *event)
{
    if (dragging)
    {
        dragging = false; // Reset dragging if mouse leaves
    }
    QPushButton::leaveEvent(event);
}
