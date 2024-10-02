#include "hsbcolorwheel.h"

HSBColorWheel::HSBColorWheel(QWidget *parent)
    : QWidget(parent) {
    setFixedSize(300, 100);
}

void HSBColorWheel::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    // Renk tekerleği için piksel piksel çizim
    for (int y = 0; y < height(); ++y) {
        for (int x = 0; x < width(); ++x) {
            double hue = static_cast<double>(x) / width() * 360.0; // Hue değeri
            double saturation = 1.0 - static_cast<double>(y) / height(); // Doygunluk değeri
            QColor color;
            color.setHsv(static_cast<int>(hue), static_cast<int>(saturation * 255), 255);
            painter.setPen(color);
            painter.drawPoint(x, y);
        }
    }
}

void HSBColorWheel::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        updateColor(event->pos());
    }
}

void HSBColorWheel::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        updateColor(event->pos());
    }
}

void HSBColorWheel::updateColor(const QPoint &pos) {
    if (pos.x() >= 0 && pos.x() < width() && pos.y() >= 0 && pos.y() < height()) {
        int hue = static_cast<int>(static_cast<double>(pos.x()) / width() * 360.0);
        int saturation = static_cast<int>((1.0 - static_cast<double>(pos.y()) / height()) * 255);
        currentColor = QColor::fromHsv(hue, saturation, 255);
        emit colorChanged(currentColor);
        emit hueChanged(hue);
        emit saturationChanged(saturation);
        emit brightnessChanged(255); // Tam parlaklık
    }
}
