#ifndef LABELCLASS_H
#define LABELCLASS_H

#include "buttoneventclass.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include <QObject>
#include <QWidget>

class labelCLASS: public QLabel
{
    Q_OBJECT
public:
    explicit labelCLASS(QWidget *parent = nullptr);
    uint8_t* WidgetValue;

signals:
    void ValueChanged(int value);

public slots:
    void updateButtonPosition(int x, int y);

private:
    buttonEventClass* Lbutton;
    int ChannelColor, XB;
    int parentwidth=305;
};

#endif // LABELCLASS_H
