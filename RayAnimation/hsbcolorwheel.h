#ifndef HSBCOLORWHEEL_H
#define HSBCOLORWHEEL_H

#include "opencv2/core/types.hpp"
#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QLabel>

class RayAnimThread;

class Core;

class HSBColorWheel : public QWidget

{
    Q_OBJECT
public:
   explicit HSBColorWheel(Core* c, QWidget *parent = nullptr);
   QColor hsbToRgb(int h, int s, int v);
   cv::Scalar qColorToScalar(const QColor& color);

   int getCurrentHue() const { return currentHue; }
   int getCurrentSaturation() const { return currentSaturation; }
   int getCurrentBrightness() const { return currentBrightness; }

signals:
   void colorChanged(const QColor &color);

   void hueChanged(int hue);
   void saturationChanged(int saturation);
   void brightnessChanged(int brightness);

protected:
   void paintEvent(QPaintEvent *event) override;
   void mousePressEvent(QMouseEvent *event) override;
   void mouseMoveEvent(QMouseEvent *event) override;
   void mouseReleaseEvent(QMouseEvent *event) override;


private:

   int currentHue;
   int currentSaturation;
   int currentBrightness;

   QRect hueRect;
   QRect saturationRect;
   QRect brightnessRect;
   bool dragging;
   QPoint circleCenter;


   void updateColor(const QPoint &pos);
   void updateHue(const QPoint &pos);
   void updateSaturation(const QPoint &pos);
   void updateBrightness(const QPoint &pos);

   Core* core;

};

#endif // HSBCOLORWHEEL_H
