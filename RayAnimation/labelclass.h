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
    QColor DefaultPaletteColor(int PaletteNumber) const;

protected:
    void mousePressEvent(QMouseEvent *event);

signals:
    void PaletteValueChanged(QColor value, int pieceIndex);

private:
    QPoint mousePos;
    QColor PColor;

public slots:
    void changeColor(int caseNumber);

};

#endif // LABELCLASS_H
