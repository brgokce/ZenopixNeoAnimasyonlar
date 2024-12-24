#ifndef RGBLABEL_H
#define RGBLABEL_H

#include <QLabel>
#include <QObject>
#include <QWidget>
#include "rgbbuttonclass.h"

class RgbLabel: public QLabel
{
    Q_OBJECT
public:
    explicit RgbLabel(QWidget *parent= nullptr);

signals:
    void ValueChanged(int value);

public slots:
    void UpdateButtonPos(int x, int y);

private:
    RgbButtonClass* RButton;
    int channelC, XB;
    int parentwidth= 256;
};

#endif // RGBLABEL_H
