#include "rgbcolorwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QLabel>
#include <algorithm>

RGBColorWidget::RGBColorWidget(QWidget *parent)
    : QWidget(parent), rPosition(10), gPosition(10), bPosition(10), draggingR(false), draggingG(false), draggingB(false) {
    setFixedHeight(150); // Widget yüksekliğini ayarla
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
    int posX = event->pos().x(); // Fare X pozisyonu

    int startX = 10;             // Kaydırıcı başlangıç noktası
    int endX = width() - 30;     // Kaydırıcı bitiş noktası
    int sliderWidth = 7;         // Dikdörtgen ikon genişliği (örnek olarak 7 piksel)

    if (draggingR) {
        // Kırmızı kaydırıcıyı fare hareketine göre tam olarak hizala, ikonun genişliği hesaba katılıyor
        rPosition = std::clamp(posX - sliderWidth / 2, startX, endX - sliderWidth);
    }

    if (draggingG) {
        // Yeşil kaydırıcıyı fare hareketine göre tam olarak hizala, ikonun genişliği hesaba katılıyor
        gPosition = std::clamp(posX - sliderWidth / 2, startX, endX - sliderWidth);
    }

    if (draggingB) {
        // Mavi kaydırıcıyı fare hareketine göre tam olarak hizala, ikonun genişliği hesaba katılıyor
        bPosition = std::clamp(posX - sliderWidth / 2, startX, endX - sliderWidth);
    }

    update(); // Yeniden çizim isteği gönder
}


void RGBColorWidget::mousePressEvent(QMouseEvent *event) {
    // Kırmızı kaydırıcıyı kontrol et
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
}

void RGBColorWidget::mouseReleaseEvent(QMouseEvent *event) {
    // Sürüklemeyi durdur
    draggingR = draggingG = draggingB = false;
}
