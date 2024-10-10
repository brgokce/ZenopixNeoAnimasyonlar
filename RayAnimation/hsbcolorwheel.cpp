#include "hsbcolorwheel.h"
#include "opencv2/core/types.hpp"
#include "rayanimthread.h"
#include <QPainter>
#include <QMouseEvent>



HSBColorWheel::HSBColorWheel(Core* c, QWidget *parent)
    : QWidget(parent),currentHue(0), core(c), currentSaturation(255), currentBrightness(255), dragging(false)
{
    // Yükseklik sabit
    int rectHeight = 30; // Her alan için yükseklik
    int rectWidth = 150; // Her alan için genişlik

    // Yükseklikleri ve konumları ayarla
    hueRect = QRect(0, 0, rectWidth, rectHeight);          // Hue kısmı
    saturationRect = QRect(0, rectHeight + 5, rectWidth, rectHeight); // Saturation kısmı
    brightnessRect = QRect(0, (rectHeight + 5) * 2, rectWidth, rectHeight); // Brightness kısmı

    // Daire merkezini başlangıçta tanımla
    circleCenter = QPoint(0, 0); // İlk daire merkezi
}

void HSBColorWheel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // Hue çizimi
    QLinearGradient hueGradient(hueRect.topLeft(), hueRect.topRight());
    for (int i = 0; i <= 360; i += 60) {
        QColor color;
        color.setHsv(i, 255, 255);
        hueGradient.setColorAt(i / 360.0, color);
    }
    painter.fillRect(hueRect, hueGradient);

    // Saturation çizimi
    QLinearGradient saturationGradient(saturationRect.topLeft(), saturationRect.topRight());
    saturationGradient.setColorAt(0, QColor(255, 255, 255));
    saturationGradient.setColorAt(1, QColor::fromHsv(currentHue, 255, currentBrightness));
    painter.fillRect(saturationRect, saturationGradient);

    // Brightness çizimi
    QLinearGradient brightnessGradient(brightnessRect.topLeft(), brightnessRect.topRight());
    brightnessGradient.setColorAt(0, QColor(0, 0, 0));
    brightnessGradient.setColorAt(1, QColor::fromHsv(currentHue, currentSaturation, 255));
    painter.fillRect(brightnessRect, brightnessGradient);

    // Daire çizimi
    painter.setBrush(QColor(currentHue, currentSaturation, currentBrightness, 128)); // Şeffaflık %50
    painter.drawEllipse(circleCenter, 10, 10); // Dairenin boyutu
}

void HSBColorWheel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = true;
        circleCenter = event->pos(); // Daire merkezini güncelle
        updateColor(event->pos());
        update(); // Yenile
    }
}

void HSBColorWheel::mouseMoveEvent(QMouseEvent *event)
{
    if (dragging && (event->buttons() & Qt::LeftButton)) {
        circleCenter = event->pos(); // Daire merkezini güncelle
        updateColor(event->pos());
        update(); // Yenile
    }
}

void HSBColorWheel::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = false; // Sürüklemeyi durdur
        update(); // Yenile
    }
}

void HSBColorWheel::updateColor(const QPoint &pos)
{
    if (hueRect.contains(pos)) {
        updateHue(pos);
    } else if (saturationRect.contains(pos)) {
        updateSaturation(pos);
    } else if (brightnessRect.contains(pos)) {
        updateBrightness(pos);
    }
     QColor newColor = hsbToRgb(currentHue, currentSaturation, currentBrightness);
     core->HSBcolor = qColorToScalar(newColor);
     emit colorChanged(newColor);
     qDebug() << "Yeni Renk Scalar: B=" << core->HSBcolor[0] << " G=" << core->HSBcolor[1] << " R=" << core->HSBcolor[2];

}

void HSBColorWheel::updateHue(const QPoint &pos)
{
    int hue = (pos.x() * 360) / width();
    currentHue = qBound(0, hue, 360);
    emit hueChanged(currentHue);


    update();
}

void HSBColorWheel::updateSaturation(const QPoint &pos)
{
    int saturation = (pos.x() * 255) / width();
    currentSaturation = qBound(0, saturation, 255);
    emit saturationChanged(currentSaturation);
    update();
}

void HSBColorWheel::updateBrightness(const QPoint &pos)
{
    int brightness = (pos.x() * 255) / width();
    currentBrightness = qBound(0, brightness, 255);
    emit brightnessChanged(currentBrightness);
    update();
}

QColor HSBColorWheel::hsbToRgb(int h, int s, int v)
{
    int r, g, b;

    // Eğer saturation 0 ise, gri tonlar döndür
    if (s == 0) {
        r = g = b = v;
    } else {
        // Hue değerini 0-360 arasında tutun
        int hf = h / 60; // hue kısmını 60'a böl
        int p = (v * (255 - s)) / 255; // Koyu ton
        int q = (v * (255 - (s * (h % 60)) / 255)) / 255; // Orta ton
        int t = (v * (255 - (s * (60 - (h % 60))) / 255)) / 255; // Açık ton

        // Kırmızı rengini tam vermek için hue 0 olduğunda
        switch (hf) {
        case 0: r = v; g = t; b = p; break; // Kırmızıdan Sarıya
        case 1: r = q; g = v; b = p; break; // Sarıdan Yeşile
        case 2: r = p; g = v; b = t; break; // Yeşilden Ciyane
        case 3: r = p; g = q; b = v; break; // Ciyandan Maviye
        case 4: r = t; g = p; b = v; break; // Maviden Mor'a
        default: r = v; g = p; b = q; break; // Mor'dan Kırmızıya
        }

        // Saturation ve brightness'a göre rengi ayarlayın
        // Eğer tam kırmızı istiyorsanız, saturation ve brightness 255 olmalı
        if (h == 0 && s == 255 && v == 255) {
            return QColor(255, 0, 0); // Tam kırmızı
        }
    }

    // RGB değerlerini sınırlandırarak geri döndür
    return QColor(qBound(0, r, 255), qBound(0, g, 255), qBound(0, b, 255)); // 0-255 aralığına kısıtlama
}

cv::Scalar HSBColorWheel::qColorToScalar(const QColor& color)
{
    return cv::Scalar(color.blue(), color.green(), color.red()); // OpenCV renk sırası BGR'dir.
}
