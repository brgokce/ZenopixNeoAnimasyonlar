#include "buttoneventclass.h"
#include "qevent.h"
#include "labelclass.h"
#include "qtimer.h"

buttonEventClass::buttonEventClass(int *parentWdt, QWidget *parent)
    : QPushButton(parent), dragging(false)
{
    setFixedSize(40, 180);
    setStyleSheet("background-color:rgba(0,0,0,0);");

    parentWidth= parentWdt;
}
void buttonEventClass::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragging = true;
        PreviousPos= event->pos();
        event->accept();
    }
}
void buttonEventClass::mouseMoveEvent(QMouseEvent *event)
{
   if(dragging && (event->buttons() & Qt::LeftButton))
    {
      currentPos = pos();
      DeltaX= event->pos().x() - PreviousPos.x();

      int newPosX = currentPos.x() + DeltaX;

      if (newPosX < 0) newPosX = 0;
      if(newPosX>*parentWidth-width()) newPosX= *parentWidth-width();
         move(newPosX, currentPos.y());

      if (DeltaX != 0)
      {
          emit buttonPositionChanged(newPosX, currentPos.y());
          currentValue += (DeltaX > 0) ? 1 : -1;
          emit ButtonvalueChanged(currentValue);
      }

      PreviousPos= event->pos();
    }
}

void buttonEventClass::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragging = false;
        event->accept();
    }
}
void buttonEventClass::leaveEvent(QEvent *event)
{
    if (dragging)
    {
        dragging = false;
    }
    QPushButton::leaveEvent(event);
}
