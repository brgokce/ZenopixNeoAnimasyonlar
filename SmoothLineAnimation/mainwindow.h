#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "core.h"
#include "qscrollarea.h"
#include "rgblabel.h"
#include "smoothlinesanimationthread.h"
#include <QMainWindow>
#include "qboxlayout.h"

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

    RgbLabel*rLabel;
    RgbLabel*gLabel;
    RgbLabel*bLabel;

public slots:
    void onRedValueChanged(int value);
    void onGreenValueChanged(int value);
    void onBlueValueChanged(int value);

private slots:
    void on_startBt_clicked();
    void on_Random_bttn_clicked();
    void on_standart_bttn_clicked();

    void onProcessFinished(cv::Mat img);

    void on_Delta_sldr_valueChanged(int value);

    void on_speed_sldr_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    Core* core;
    SmoothLinesAnimationThread* smoothTh;

    QImage qimg;
    QImage matToImage(const cv::Mat &mat) const noexcept;

    void ViewProcess(cv::Mat imgV);
    void checkRadioButtonState();

    void UpdateRGB();

    void onTabChanged(int index);

    void addColorToSmoothLinesVector();

    QTabWidget *tabwidget;
    QVBoxLayout *sliderLayout;
    QWidget *sliderTab;
    QScrollArea* scrollArea;
};
#endif // MAINWINDOW_H
