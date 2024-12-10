#include "anchorbutton.h"
#include "core.h"
#include "qevent.h"
#include "qpainter.h"

AnchorButton::AnchorButton(int *parentWdt,int *parentHgt, int *Anchor, Core* c, QWidget* parent): QPushButton(parent), AScaledOn(false)
{
    setFixedSize(20, 30);
    setStyleSheet("background-color:rgba(0,0,0,0);");
    setIcon(QIcon("C:/Users/ASUS/Desktop/channelButton.png"));
    setIconSize(size());

    parentWidth= parentWdt;
    parentHeight= parentHgt;

    core=c;
    anchor= Anchor;

    int startX= (*parentWidth / 2) - (width() / 2);
    move(startX, 0);
    *anchor=0;
}

AnchorButton::~AnchorButton() {

}

void AnchorButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button()== Qt::LeftButton)
    {
        Idragging= true;
        PreviousP= event->globalPos();
        event->accept();
    }
}
void AnchorButton::mouseMoveEvent(QMouseEvent *event)
{
    if (Idragging)
    {
        currentP = event->globalPos();
        DeltaX = currentP.x() - PreviousP.x();
        NPos = x() + DeltaX;

        if (NPos < 0){
            NPos = 0;
        }
        else if (NPos > (*parentWidth - width())){
            NPos = *parentWidth - width();
        }

        else
        {
            *anchor= -(*parentWidth / 2) + (static_cast<double>(NPos) / (*parentWidth - width())) * (*parentWidth);
        }

        if(NPos==*parentWidth-width()){
            return;
        }

        if (*anchor < -(*parentWidth / 2)) {
            *anchor = -(*parentWidth / 2);
        }
        if (*anchor > (*parentWidth / 2)) {
            *anchor = (*parentWidth / 2);
        }

        move(NPos, y());
        PreviousP = currentP;

        if (NPos == (*parentWidth / 2) - (width() / 2)){
            *anchor = 0;
        }

        if(AScaledOn){

            float scaleFactor = 1.0 + (DeltaX / 100.0);
            if (scaleFactor < 0.9) scaleFactor = 0.9;
            if (scaleFactor > 1.1) scaleFactor = 1.1;

            core->currScale *= scaleFactor;

            if (core->currScale < 0.135) {
                qDebug() << "Warning: currScale below 0.15, adjusting to 0.15.";
                core->currScale = 0.135;
            }
            if (core->currScale > 13.5) {
                qDebug() << "Warning: currScale above 13.5, adjusting to 13.5.";
                core->currScale = 13.5;
            }
            if(NPos==(*parentWidth / 2) - (width() / 2)){
                core->currScale=1.0;
            }

            emit AnchorZVal(core->currScale);

            qDebug() << "NPos:" << NPos << "<<scaleFactor<" << scaleFactor << "Scale:" << core->currScale;
        }

        if (!moveState){
            moveState = true;
        }
    }
}

void AnchorButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        Idragging = false;
        pressed = false;

        if (!moveState || parentWidget()->styleSheet() == "background-color:rgb(73,87,102);")
        {
            if (NPos == (*parentWidth / 2) - (width() / 2)) {
                *anchor = 0;
            }
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

void AnchorButton::leaveEvent(QEvent *event)
{
    if (Idragging)
    {
        Idragging = false;
    }
    QPushButton::leaveEvent(event);
}
