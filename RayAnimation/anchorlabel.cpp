#include "anchorlabel.h"
#include "qpainter.h"

AnchorLabel::AnchorLabel(Core* c,QWidget* parent) :QLabel(parent)
{
    core = c;

    Abutton= nullptr;
    Bbutton= nullptr;
    Cbutton=nullptr;
}

void AnchorLabel::setAButton()
{
    qDebug() << "Setting AScaledOn to false in setAButton, current value: " << core->rayanimset.AScaledOn;
    Abutton= new AnchorButton(&parentwidth,&parentheight,&core->x_a, core,this);
}

void AnchorLabel::setBButton()
{
    Bbutton= new AnchorButton(&parentwidth, &parentheight, &core->y_a, core, this);
}

void AnchorLabel::setCButton()
{
    Cbutton= new AnchorButton(&parentwidth, &parentheight, &core->AScale, core, this);
    Cbutton->AScaledOn = true;
    core->rayanimset.AScaledOn= Cbutton->AScaledOn;
    connect(Cbutton, &AnchorButton::AnchorZVal, this, &AnchorLabel::AUpdateScale);
}

void AnchorLabel::AUpdateScale(float scaleValue)
{
    scaleZ = scaleValue;
    if(core->rayanimset.AScaledOn){
        emit AScaleChanged(scaleZ, core->Img);
    }
    qDebug() << "Scale updated in Label:" << scaleZ;
}
