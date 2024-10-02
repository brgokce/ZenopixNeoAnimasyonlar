#ifndef COLORWHEELWIDGET_H
#define COLORWHEELWIDGET_H

#include <QObject>
#include <QWidget>

class ColorWheelWidget: public QWidget
{
    Q_OBJECT
public:
    explicit ColorWheelWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void colorHovered(const QColor &color);
    void colorSelected(const QColor &color);

private:
    QColor getColorAtPosition(const QPoint &pos);
    bool m_isMousePressed;      // Fare basılı mı
    QColor m_selectedColor;     // Seçilen renk
    QPoint m_hoverPosition;     // Hover pozisyonu

};

#endif // COLORWHEELWIDGET_H
