#ifndef CHANNELLABEL_H
#define CHANNELLABEL_H

#include "buttoneventclass.h"
#include <QLabel>
#include <QObject>
#include <QWidget>

class ChannelLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ChannelLabel(QWidget *parent = nullptr);
signals:
    void ValueChanged(int value);

public slots:
    void updateButtonPosition(int x, int y);

private:
    buttonEventClass* Lbutton;
    int ChannelColor, XB;
    int parentwidth=256;

};

#endif // CHANNELLABEL_H
