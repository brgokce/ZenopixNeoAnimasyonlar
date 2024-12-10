#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QScrollArea>
#include <QMainWindow>
#include "anchorlabel.h"
#include "core.h"
#include "hsbcolorwheel.h"
#include "labelclass.h"
#include "qboxlayout.h"
#include "qgraphicsscene.h"
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

    labelCLASS*paletteLabel;

    AnchorLabel* AncX;
    AnchorLabel* AncY;
    AnchorLabel* AncZ;

public slots:
    void onRedValueChanged(int value);
    void onGreenValueChanged(int value);
    void onBlueValueChanged(int value);
    void handlePaletteValueChange(QColor color,int pieceIndex);

    void Z_Axis_Anchor(float scaleF, cv::Mat& imgZ);

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
    void onColorSelected(const QColor &color);

    void onHueChanged(int hue);
    void onSaturationChanged(int saturation);
    void onBrightnessChanged(int brightness);

protected:
    void wheelEvent(QWheelEvent *event) override;

private:
    Ui::MainWindow *ui;
    Core* core;
    RayAnimThread* rayAnimthread;

    bool isRunning;
    double scaleFactor;

    QImage matToImage(const cv::Mat &mat) const noexcept;

    void checkRadioButtonState();
    void updateRayColors();
    void updateRayRGBColors();
    void updateSpinBoxLimits(int minValue, int maxValue);

    ColorWheelWidget *colorWheel;
    HSBColorWheel* hsbcolorwheel;

    QTabWidget *tabwidget;

    void onTabChanged(int index);
    void onTabCWheel(int index);
    void onTabHSB(int index);
    void onTabPltte(int index);

    QVBoxLayout *sliderLayout;
    QVBoxLayout *paletteLayout;

    QWidget *sliderTab;
    QWidget *sliderTabPalette;

    QScrollArea* scrollArea;
    QScrollArea *palettescrolarea;

    void UpdateRGB();
    void drawColors();
    void updateRayPaletteColors();

    void ScaleTablePos(const QPointF &currCursorPoint, double scaleFactor);
    void ViewProcess(cv::Mat imgP);
    cv::Mat QImageToMat(const QImage &image);
    void Scale(cv::Mat imgR);

    QImage qimg;
    QImage finalImage;

    QPoint currCursorPoint;

};
#endif // MAINWINDOW_H
