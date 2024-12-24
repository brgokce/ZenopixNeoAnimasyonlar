#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "core.h"
#include "snowflakeanimationthread.h"
#include <QMainWindow>

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

public slots:
    void onprocessFinished(cv::Mat img);

private slots:
    void on_snowflake_spinbx_valueChanged(int arg1);

    void on_extent_snowflake_spnbx_valueChanged(int arg1);

    void on_color_combobx_currentIndexChanged(int index);

    void on_Speed_sldr_valueChanged(int value);

    void on_brightness_sldr_valueChanged(int value);

    void on_startBt_clicked();

private:
    Ui::MainWindow *ui;
    Core* core;
    SnowFlakeAnimationThread* snowTh;

    void ViewProcess(cv::Mat imgS);

    QImage matToImage(const cv::Mat &mat) const noexcept;
    QImage qimg;

    void updateRayColors();
};
#endif // MAINWINDOW_H
