#ifndef HSBCOLORWHEEL_H
#define HSBCOLORWHEEL_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class HSBColorWheel : public QWidget
{
    Q_OBJECT
public:
   explicit HSBColorWheel(QWidget *parent = nullptr);


signals:
   void colorChanged(const QColor &color);
   void hueChanged(int hue);
   void saturationChanged(int saturation);
   void brightnessChanged(int brightness);

protected:
   void paintEvent(QPaintEvent *event) override;
   void mousePressEvent(QMouseEvent *event) override;
   void mouseMoveEvent(QMouseEvent *event) override;

private:
   QColor currentColor;
   void updateColor(const QPoint &pos);
};

#endif // HSBCOLORWHEEL_H
