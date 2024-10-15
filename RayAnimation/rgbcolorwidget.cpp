#include "rgbcolorwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QLabel>
#include <algorithm>

RGBColorWidget::RGBColorWidget(QWidget *parent)
    : QWidget(parent), rPosition(10), gPosition(10), bPosition(10),alphaPosition(10), draggingR(false), draggingG(false), draggingB(false),draggingAlpha(false) {
    setFixedHeight(200); // Widget yüksekliğini ayarla
}

void RGBColorWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.fillRect(rect(), Qt::transparent); // Arka planı beyaz yap

    // Kırmızı kaydırıcıyı çiz
    drawSlider(painter, rPosition, 0, Qt::transparent);
    // Yeşil kaydırıcıyı çiz
    drawSlider(painter, gPosition, 1, Qt::transparent);
    // Mavi kaydırıcıyı çiz
    drawSlider(painter, bPosition, 2, Qt::transparent);

    drawAlphaSlider(painter, alphaPosition);
}

void RGBColorWidget::drawAlphaSlider(QPainter &painter, int position) {
    int startX = 10;                // Alfa kaydırıcı başlangıç pozisyonu
    int endX = width() - 30;        // Alfa kaydırıcı bitiş pozisyonu
    int sliderWidth = 7;            // Kaydırıcı ikonunun genişliği

    // Alfa gradyanı
    QLinearGradient gradient(startX, 130, endX, 130);
    gradient.setColorAt(0, QColor(0, 0, 0, 0)); // Tam şeffaf
    gradient.setColorAt(1, QColor(0, 0, 0, 255)); // Tam opak

    // Alfa alanını çiz
    painter.setBrush(gradient);
    painter.drawRect(startX, 130, endX - startX, 30); // Alfa gradyanı alanını çiz

    // Kaydırıcı ikonunu çizin
    painter.setBrush(Qt::transparent); // İkon için siyah rengi ayarla
    painter.drawRect(position, 130, sliderWidth, 30); // Kaydırıcı ikonunu çiz
}

void RGBColorWidget::drawSlider(QPainter &painter, int position, int channel, const QColor &color) {
    int startX = 10;                // Kaydırıcı başlangıç pozisyonu
    int endX = width() - 30;        // Kaydırıcı bitiş pozisyonu
    int sliderWidth = endX - startX; // Kaydırıcı genişliği

    // Renk gradyanını çizin
    QLinearGradient gradient(startX, 10 + channel * 40, endX, 10 + channel * 40);

    // Gradyanı ayarlayın
    switch (channel) {
    case 0: // Kırmızı için
        gradient.setColorAt(0, Qt::red);
        gradient.setColorAt(1, Qt::yellow); // Kırmızıdan sarıya geçiş
        break;
    case 1: // Yeşil için
        gradient.setColorAt(0, Qt::green);
        gradient.setColorAt(1, Qt::yellow); // Yeşilden sarıya geçiş
        break;
    case 2: // Mavi için
        gradient.setColorAt(0, Qt::blue);
        gradient.setColorAt(1, Qt::cyan); // Mavi'den cyan'a geçiş
        break;
    }

    // Renk alanını çiz
    painter.setBrush(gradient);
    painter.drawRect(startX, 10 + channel * 40, sliderWidth, 30); // Renk gradyanı alanını çiz

    // Kaydırıcı ikonunu çizin
    painter.setBrush(color); // İkon için verilen rengi ayarla
    painter.drawRect(position, 10 + channel * 40, 7, 30); // Kaydırıcı ikonunu çiz
}

void RGBColorWidget::mouseMoveEvent(QMouseEvent *event) {
    if (draggingR || draggingG || draggingB || draggingAlpha) {
        int posX = event->pos().x(); // Fare X pozisyonu
        int startX = 10;             // Kaydırıcı başlangıç noktası
        int endX = width() - 30;     // Kaydırıcı bitiş noktası
        int sliderWidth = 7;         // Kaydırıcı ikon genişliği

        // Kırmızı kaydırıcıyı güncelle
        if (draggingR) {
            rPosition = std::clamp(posX - sliderWidth / 2, startX, endX - sliderWidth);
        }
        // Yeşil kaydırıcıyı güncelle
        else if (draggingG) {
            gPosition = std::clamp(posX - sliderWidth / 2, startX, endX - sliderWidth);
        }
        // Mavi kaydırıcıyı güncelle
        else if (draggingB) {
            bPosition = std::clamp(posX - sliderWidth / 2, startX, endX - sliderWidth);
        }
        // Alfa kaydırıcıyı güncelle
        else if (draggingAlpha) {
            alphaPosition = std::clamp(posX - sliderWidth / 2, startX, endX - sliderWidth);
        }


        update(); // Yeniden çizim isteği gönder
    }
}


void RGBColorWidget::mousePressEvent(QMouseEvent *event) {
    // Kırmızı kaydırıcıyı kontrol et

    int sliderWidth = 7;

    if (event->pos().x() >= rPosition && event->pos().x() <= rPosition + 20 &&
        event->pos().y() >= 10 && event->pos().y() <= 40) {
        draggingR = true;
    }
    // Yeşil kaydırıcıyı kontrol et
    else if (event->pos().x() >= gPosition && event->pos().x() <= gPosition + 20 &&
             event->pos().y() >= 50 && event->pos().y() <= 90) {
        draggingG = true;
    }
    // Mavi kaydırıcıyı kontrol et
    else if (event->pos().x() >= bPosition && event->pos().x() <= bPosition + 20 &&
             event->pos().y() >= 90 && event->pos().y() <= 130) {
        draggingB = true;
    }
    else if (event->pos().x() >= alphaPosition && event->pos().x() <= alphaPosition + sliderWidth &&
             event->pos().y() >= 130 && event->pos().y() <= 180) {
        draggingAlpha = true;
    }
}

void RGBColorWidget::mouseReleaseEvent(QMouseEvent *event) {
    // Sürüklemeyi durdur
    draggingR = draggingG = draggingB =draggingAlpha = false;
}
