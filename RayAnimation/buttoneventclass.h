#ifndef BUTTONEVENTCLASS_H
#define BUTTONEVENTCLASS_H



#include "qpushbutton.h"
#include <QObject>
#include <QWidget>

class buttonEventClass: public QPushButton
{
    Q_OBJECT
public:
    explicit buttonEventClass(int *parentWdt, QWidget *parent = nullptr);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;


signals:
    void ButtonvalueChanged(int value);
    void buttonPositionChanged(int x, int y);



private:
    int XB, Wb;
    bool dragging;
    int DeltaX, DeltaY, currentValue;
    QPoint PreviousPos, currentPos;
    int *parentWidth;
    QTimer *updateTimer;
    float lerpFactor;

    void smoothMove();
};

#endif // BUTTONEVENTCLASS_H
