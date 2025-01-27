#ifndef RGBLABL_H
#define RGBLABL_H

#include <QLabel>
#include <QObject>
#include <QWidget>
#include "rgbwidget.h"

class RGBLabl:  public QLabel
{
    Q_OBJECT
public:
    explicit RGBLabl(QWidget *parent= nullptr);

signals:
    void ValueChanged(int value);

public slots:
    void UpdateButtonPos(int x, int y);

private:
    RGBWidget* RButton;
    int channelC, XB;
    int parentwidth= 256;
};

#endif // RGBLABL_H
