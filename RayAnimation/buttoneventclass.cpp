#include "buttoneventclass.h"
#include "qevent.h"
#include "labelclass.h"
#include "qtimer.h"

buttonEventClass::buttonEventClass(int *parentWdt, QWidget *parent)
    : QPushButton(parent), dragging(false)
{
    setFixedSize(20, 30);
    setStyleSheet("background-color:rgba(0,0,0,0);");
    setIcon(QIcon("C:/Users/ASUS/Desktop/channelButton.png"));
    setIconSize(size());


    parentWidth= parentWdt;
}
void buttonEventClass::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragging = true;
        PreviousPos= event->globalPos();
        event->accept();
    }
}
void buttonEventClass::mouseMoveEvent(QMouseEvent *event)
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

        emit buttonPositionChanged(newPosX, currentPos.y());
        currentValue += (DeltaX > 0) ? 1 : -1;
        currentValue = qBound(0, currentValue, 255);
        emit ButtonvalueChanged(currentValue);

        if (!moveState)
        {
            moveState = true;
        }
    }
}
void buttonEventClass::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragging = false; // Stop dragging
        pressed = false; // Reset pressed state

        // Emit clicked signal if not in move state
        if (!moveState || parentWidget()->styleSheet() == "background-color:rgb(73,87,102);")
        {
            emit clicked(true);
        }
        else
        {
            moveState = false; // Reset move state
        }

        emit itemReleased(); // Emit item released signal
        event->accept();
    }
}

void buttonEventClass::leaveEvent(QEvent *event)
{
    if (dragging)
    {
        dragging = false; // Reset dragging if mouse leaves
    }
    QPushButton::leaveEvent(event);
}
