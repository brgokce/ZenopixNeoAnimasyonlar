#include "colorwheelwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <cmath>

ColorWheelWidget::ColorWheelWidget(QWidget *parent) : QWidget(parent), m_isMousePressed(false)
{
    setMouseTracking(true); // Fare hareketlerini izlemek için
    m_selectedColor = QColor(255, 255, 255); // İlk seçili renk (varsayılan beyaz)
}

void ColorWheelWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    int centerX = width() / 2;
    int centerY = height() / 2;
    int radius = qMin(centerX, centerY) - 10;

    // Renk çemberini çiz
    for (int i = 0; i < 360; i++)
    {
        QColor color;
        color.setHsv(i, 255, 255);  // HSV rengi
        painter.setBrush(QBrush(color));
        painter.setPen(Qt::NoPen);
        painter.drawPie(centerX - radius, centerY - radius, 2 * radius, 2 * radius, i * 16, 16);
    }

    // Fare basılıysa ve geçerli bir pozisyon varsa şeffaf daireyi çiz
    if (!m_hoverPosition.isNull())
    {
        painter.setBrush(Qt::transparent);
        painter.setPen(QPen(Qt::black, 2));
        painter.drawEllipse(m_hoverPosition, 10, 10);  // Şeffaf dairenin boyutu
    }

    // Seçilen rengi görüntülemek için küçük bir alan çiz (örnek: sol üst köşeye)

}

void ColorWheelWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isMousePressed)  // Sadece fare basılıyken renkleri değiştir
    {
        // İmleci değiştir
        int centerX = width() / 2;
        int centerY = height() / 2;
        int dx = event->pos().x() - centerX;
        int dy = event->pos().y() - centerY;
        int distance = std::sqrt(dx * dx + dy * dy);
        int radius = qMin(centerX, centerY) - 10;

        // Mouse tekerleği içinde ise özel bir imleç göster
        if (distance <= radius)
        {
            setCursor(Qt::PointingHandCursor);  // İmleci parmak okuna değiştir

            // Rengi dinamik olarak al ve yay
            QColor color = getColorAtPosition(event->pos());
            if (color.isValid())
            {
                emit colorHovered(color);  // Her fare hareketinde rengi yay
                qDebug() << "Mouse Moved at:" << event->pos() << "Hovered Color:" << color;

                // Dinamik olarak rengi değiştir
                emit colorSelected(color);  // Animasyonun rengini değiştir

                // Hover pozisyonunu güncelle
                m_hoverPosition = event->pos();
            }
        }
        else
        {
            setCursor(Qt::ArrowCursor);  // Normal imleç
        }

        update();  // Yeniden çizim
    }
}

void ColorWheelWidget::mousePressEvent(QMouseEvent *event)
{
    m_isMousePressed = true;  // Fare basıldı
    m_hoverPosition = event->pos();  // Pozisyonu al
    update();  // Yeniden çizim
}

void ColorWheelWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_isMousePressed = false;  // Fare bırakıldı

    // Fare bırakıldığında son rengi kaydet
    QColor color = getColorAtPosition(event->pos());
    if (color.isValid())
    {
        m_selectedColor = color;  // Son rengi kaydet
        emit colorSelected(m_selectedColor);  // Rengi yay
        qDebug() << "Mouse Released. Selected Color:" << m_selectedColor;
    }

    update();  // Çizimi yenile
}

QColor ColorWheelWidget::getColorAtPosition(const QPoint &pos)
{
    int centerX = width() / 2;
    int centerY = height() / 2;

    int dx = pos.x() - centerX;
    int dy = pos.y() - centerY;
    int distance = std::sqrt(dx * dx + dy * dy);

    double angle = std::atan2(dy, dx) * 180 / M_PI;
    angle = 360 - angle; // Açıyı tersine çevir

    if (angle < 0)
        angle += 360;

    int radius = qMin(centerX, centerY) - 10;

    if (distance <= radius)
    {
        QColor color;
        color.setHsv(static_cast<int>(angle), 255, 255);  // Renk hesapla
        return color;
    }
    return QColor();  // Geçersiz renk döndür
}

