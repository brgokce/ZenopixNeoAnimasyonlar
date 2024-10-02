#include "hsbcolorwheel.h"
#include <QPainter>
#include <QMouseEvent>

HSBColorWheel::HSBColorWheel(QWidget *parent)
    : QWidget(parent), currentHue(0), currentSaturation(255), currentBrightness(255), dragging(false)
{
    // Widget'ı üç dikdörtgene ayır
    int rectHeight = height() / 3; // Yüksekliği üç parçaya böldük
    int rectWidth = width(); // Genişliği tam al

    // Genişliği artırıyoruz
    int increasedWidth = rectWidth * 1.5; // Genişliği artır

    // Yükseklikleri ayarla
    hueRect = QRect(0, 0, increasedWidth, rectHeight * 2);           // Hue kısmı daha yüksek
    saturationRect = QRect(0, rectHeight * 2, increasedWidth, rectHeight * 1.5); // Saturation kısmı
    brightnessRect = QRect(0, rectHeight * 3 + rectHeight * 0.5, increasedWidth, rectHeight * 2); // Brightness kısmı daha yüksek

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

