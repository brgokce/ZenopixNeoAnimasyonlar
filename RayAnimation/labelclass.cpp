#include "labelclass.h"
#include "qevent.h"
#include "qpainter.h"
#include "qpushbutton.h"

labelCLASS::labelCLASS(QWidget *parent)
    : QLabel(parent)
{
    this->setFixedWidth(296);
    this->setFixedHeight(20);
    setScaledContents(true);
}

QColor labelCLASS::DefaultPaletteColor(int PaletteNumber) const
{
    switch(PaletteNumber)
    {
    case 1: return QColor(Qt::red);
    case 2: return QColor(Qt::green);
    case 3: return QColor(Qt::yellow);
    case 4: return QColor(Qt::gray);
    case 5: return QColor(0, 0, 135);
    case 6: return QColor(128, 0, 128);
    case 7: return QColor(173, 216, 230);
    case 8: return QColor(Qt::white);
    default: return QColor(Qt::black);
    }  
}

void labelCLASS::changeColor(int caseNumber)
{
    QColor newColor = DefaultPaletteColor(caseNumber);
    emit PaletteValueChanged(newColor, caseNumber-1);
}

void labelCLASS::mousePressEvent(QMouseEvent *event)
{
    int pieceWidth = width() / 8;

    int pieceIndex = event->x() / pieceWidth;
    qDebug() << "Mouse clicked at: " << event->x() << ", Piece index: " << pieceIndex;

    if (pieceIndex >= 0 && pieceIndex < 8)
    {
        QColor clickedColor = DefaultPaletteColor(pieceIndex + 1);
        emit PaletteValueChanged(clickedColor, pieceIndex);
    }

    QLabel::mousePressEvent(event);
}
