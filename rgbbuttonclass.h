#ifndef RGBBUTTONCLASS_H
#define RGBBUTTONCLASS_H

#include "qpushbutton.h"
#include <QObject>
#include <QWidget>

class RgbButtonClass: public QPushButton
{
    Q_OBJECT
public:
    explicit RgbButtonClass(int *parentWdt, QWidget *parent= nullptr);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;

signals:
    void ButtonValueChanged(int value);
    void buttonPosChanged(int x, int y);
    void ItemReleased();

private:
    bool dragging;
    int DeltaX, DeltaY, currentValue;
    QPoint PreviousPos, currentPos;
    int *parentWidth;
    bool moveState= false;
    bool pressed= false;
};

#endif // RGBBUTTONCLASS_H
