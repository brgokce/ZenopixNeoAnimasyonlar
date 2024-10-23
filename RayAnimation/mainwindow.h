#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QScrollArea>
#include <QMainWindow>
#include "core.h"
#include "hsbcolorwheel.h"
#include "labelclass.h"
#include "qboxlayout.h"
#include "qpushbutton.h"
#include "rayanimthread.h"
#include "colorwheelwidget.h"
#include "hsbcolorwheel.h"
#include "channellabel.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    ChannelLabel*rLabel;
    ChannelLabel*gLabel;
        ChannelLabel*bLabel;
public slots:
    void onRedValueChanged(int value);
    void onGreenValueChanged(int value);
    void onBlueValueChanged(int value);

signals:
    int rgbValueChanged();

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_radioButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_horizontalSlider_3_valueChanged(int value);

    void on_horizontalSlider_4_valueChanged(int value);

    void on_pushButton_clicked();

    void onprocessFinished(cv::Mat img);

    void on_radioButton_2_clicked();

    void on_spinBox_2_valueChanged(int arg1);

    void on_spinBox_3_valueChanged(int arg1);



private slots:
    void onColorHovered(const QColor &color);
    void onColorSelected(const QColor &color);

    void onHueChanged(int hue);
    void onSaturationChanged(int saturation);
    void onBrightnessChanged(int brightness);


private:
    Ui::MainWindow *ui;
    Core* core;
    RayAnimThread* rayAnimthread;
    bool isRunning;
    QImage matToImage(const cv::Mat &mat) const noexcept;
    void checkRadioButtonState();
    void updateRayColors();
    void updateSpinBoxLimits(int minValue, int maxValue);
    ColorWheelWidget *colorWheel;
    HSBColorWheel* hsbcolorwheel;
    QTabWidget *tabwidget;
    void onTabChanged(int index);
    void onTabCWheel(int index);
    void onTabHSB(int index);
    QVBoxLayout *sliderLayout;
    QWidget *sliderTab;
    QScrollArea* scrollArea;
    void UpdateRGB();

};
#endif // MAINWINDOW_H
