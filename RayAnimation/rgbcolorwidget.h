#ifndef RGBCOLORWIDGET_H
#define RGBCOLORWIDGET_H

#include <QObject>
#include <QWidget>

#include <QLabel>
#include <QVBoxLayout>

class RGBColorWidget: public QWidget
{
    Q_OBJECT
public:
    explicit RGBColorWidget(QWidget *parent = nullptr);

signals:
     void colorChanged(int r, int g, int b);

protected:
     void paintEvent(QPaintEvent *event) override; // Çizim olayı
     void mouseMoveEvent(QMouseEvent *event) override; // Fare hareketi olayı
     void mousePressEvent(QMouseEvent *event) override; // Fare basma olayı
     void mouseReleaseEvent(QMouseEvent *event) override; // Fa

private:
     int rPosition; // Kırmızı kaydırıcı pozisyonu
     int gPosition; // Yeşil kaydırıcı pozisyonu
     int bPosition; // Mavi kaydırıcı pozisyonu
     bool draggingR; // Kırmızı kaydırıcı için sürükleme durumu
     bool draggingG; // Yeşil kaydırıcı için sürükleme durumu
     bool draggingB; // Mavi kaydırıcı için sürükleme durumu

     void drawSlider(QPainter &painter, int x, int channel, const QColor &color);
};

#endif // RGBCOLORWIDGET_H
