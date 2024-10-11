#include "hsbcolorwheel.h"
#include "opencv2/core/types.hpp"
#include "rayanimthread.h"
#include <QPainter>
#include <QMouseEvent>



HSBColorWheel::HSBColorWheel(Core* c, QWidget *parent)
    : QWidget(parent),currentHue(0), core(c), currentSaturation(255), currentBrightness(255), dragging(false), draggingHue(false), draggingSaturation(false), draggingBrightness(false)
{
    // Yükseklik sabit
    int rectHeight = 30; // Her alan için yükseklik
    int rectWidth = 150; // Her alan için genişlik

    // Yükseklikleri ve konumları ayarla
    hueRect = QRect(0, 0, rectWidth, rectHeight);          // Hue kısmı
    saturationRect = QRect(0, rectHeight + 5, rectWidth, rectHeight); // Saturation kısmı
    brightnessRect = QRect(0, (rectHeight + 5) * 2, rectWidth, rectHeight); // Brightness kısmı

    // Daire merkezini başlangıçta tanımla
    hueCircleCenter = QPoint(0, hueRect.center().y());
    saturationCircleCenter = QPoint(0, saturationRect.center().y());
    brightnessCircleCenter = QPoint(0, brightnessRect.center().y());

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


    painter.setBrush(QColor(currentHue, 255, 255, Qt::transparent));
    painter.drawEllipse(hueCircleCenter, 7, 7); // Dairenin boyutu

    // Saturation için daire çizimi
    painter.setBrush(QColor(255, currentSaturation, currentBrightness,Qt::transparent));
    painter.drawEllipse(saturationCircleCenter, 7, 7); // Dairenin boyutu

    // Brightness için daire çizimi
    painter.setBrush(QColor(currentHue, currentSaturation, currentBrightness,Qt::transparent));
    painter.drawEllipse(brightnessCircleCenter, 7, 7); // Dairenin boyutu

}

void HSBColorWheel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (hueRect.contains(event->pos())) {
            draggingHue = true;
            hueCircleCenter.setX(event->pos().x());
            updateHue(event->pos());
        } else if (saturationRect.contains(event->pos())) {
            draggingSaturation = true;
            saturationCircleCenter.setX(event->pos().x());
            updateSaturation(event->pos());
        } else if (brightnessRect.contains(event->pos())) {
            draggingBrightness = true;
            brightnessCircleCenter.setX(event->pos().x());
            updateBrightness(event->pos());
        }
        update(); // Yenile
    }
}
void HSBColorWheel::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        if (draggingHue) {
            hueCircleCenter.setX(event->pos().x());
            updateHue(event->pos());
        } else if (draggingSaturation) {
            saturationCircleCenter.setX(event->pos().x());
            updateSaturation(event->pos());
        } else if (draggingBrightness) {
            brightnessCircleCenter.setX(event->pos().x());
            updateBrightness(event->pos());
        }
        update(); // Yenile
    }
}

void HSBColorWheel::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        draggingHue = false;
        draggingSaturation = false;
        draggingBrightness = false; // Sürüklemeyi durdur
        update(); // Yenile
    }
}

void HSBColorWheel::updateColor(const QPoint &pos)
{
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
    float r, g, b;

    // Saturation 0 ise, gri tonlar döndür (achromatic)
    if (s == 0) {
        r = g = b = v / 255.0;  // Doğrudan parlaklık
    } else {
        float hf = h / 60.0;  // Hue'yu 60'a böl, sektör belirleme
        int i = (int)hf;      // Hangi sektör
        float f = hf - i;     // Sektördeki yer (kesirli kısım)
        float p = v * (1.0 - s / 255.0); // Daha koyu ton
        float q = v * (1.0 - s / 255.0 * f);  // Orta ton
        float t = v * (1.0 - s / 255.0 * (1.0 - f));  // Daha açık ton

        switch (i) {
        case 0: r = v; g = t; b = p; break;  // Kırmızıdan Sarıya
        case 1: r = q; g = v; b = p; break;  // Sarıdan Yeşile
        case 2: r = p; g = v; b = t; break;  // Yeşilden Ciyane
        case 3: r = p; g = q; b = v; break;  // Ciyandan Maviye
        case 4: r = t; g = p; b = v; break;  // Maviden Mora
        default: r = v; g = p; b = q; break; // Mor'dan Kırmızıya
        }
    }

    // RGB değerlerini sınırlandır ve geri döndür
    return QColor(qBound(0, (int)(r + 0.5), 255),
                  qBound(0, (int)(g + 0.5), 255),
                  qBound(0, (int)(b + 0.5), 255));
}

cv::Scalar HSBColorWheel::qColorToScalar(const QColor& color)
{
    return cv::Scalar(color.blue(), color.green(), color.red()); // OpenCV renk sırası BGR'dir.
}
