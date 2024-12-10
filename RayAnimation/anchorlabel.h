#ifndef ANCHORLABEL_H
#define ANCHORLABEL_H

#include "anchorbutton.h"
#include <QLabel>
#include <QObject>
#include <QWidget>

class AnchorLabel : public QLabel
{
    Q_OBJECT
public:
    explicit AnchorLabel(Core* c, QWidget* parent= nullptr);

    void setAButton();
    void setBButton();
    void setCButton();

public slots:
    void AUpdateScale(float scaleValue);

signals:
    void AScaleChanged(float scaleValue, cv::Mat& img);

private:
  AnchorButton* Abutton;
  AnchorButton* Bbutton;
  AnchorButton* Cbutton;
  int parentwidth=300;
  int parentheight=30;
  float scaleZ;
  Core* core;

};

#endif // ANCHORLABEL_H
