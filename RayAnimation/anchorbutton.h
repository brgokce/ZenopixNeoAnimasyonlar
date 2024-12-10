#ifndef ANCHORBUTTON_H
#define ANCHORBUTTON_H

#include "core.h"
#include <QObject>
#include <QPushButton>
#include <QWidget>

class AnchorButton : public QPushButton
{
    Q_OBJECT
public:
    explicit AnchorButton(int *parentWdt, int *parentHgt, int *Anchor, Core* c, QWidget* parent= nullptr);
    ~AnchorButton();
    bool AScaledOn;

signals:
    void ItemReleased();
    void AnchorZVal(float ancZ);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    bool Idragging= false;
    bool moveState= false;
    bool pressed= false;

    int *parentWidth;
    int *parentHeight;
    int DeltaX, currentValue, DeltaY;
    int NPos;
    Core* core;
    int *anchor;
    int startX;

    QPoint PreviousP, currentP;

};

#endif // ANCHORBUTTON_H
