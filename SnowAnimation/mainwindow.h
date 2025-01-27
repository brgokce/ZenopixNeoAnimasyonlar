#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "core.h"
#include "rgblabl.h"
#include "snowflakeanimationthread.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QScrollArea>
#include "rgbwidget.h"

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

    RGBLabl*rLabel;
    RGBLabl*gLabel;
    RGBLabl*bLabel;

public slots:
    void onprocessFinished(cv::Mat img);
    void onRedValueChanged(int value);
    void onGreenValueChanged(int value);
    void onBlueValueChanged(int value);

private slots:

    void on_startBt_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_color_combobx_currentIndexChanged(int index);

    void on_lowerR_spnbx_valueChanged(int arg1);

    void on_UpperR_spnbx_valueChanged(int arg1);

    void on_NumberOfStar_valueChanged(int arg1);

    void on_LowerT_spnbx_valueChanged(int arg1);

    void on_UpperT_spnbx_valueChanged(int arg1);

    void on_Rising_sldr_valueChanged(int value);

    void on_falling_sldr_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    Core* core;
    SnowFlakeAnimationThread* snowTh;

    void ViewProcess(cv::Mat imgS);

    QImage matToImage(const cv::Mat &mat) const noexcept;
    QImage qimg;

    void UpdateRGB();
    void addColorToSmoothCircleVector();

    QTabWidget *tabwidget;
    QVBoxLayout *sliderLayout;
    QWidget *sliderTab;
    QScrollArea* scrollArea;
};
#endif // MAINWINDOW_H
