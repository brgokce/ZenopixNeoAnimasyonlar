#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("QMainWindow {" "background-color: qlineargradient(" "spread:pad, x1:0, y1:0, x2:1, y2:1, " "stop:0 rgba(255, 0, 0, 255), " "stop:1 rgba(0, 128, 0, 255) " "    );"
        "    border: 2px solid rgba(255, 215, 0, 1);" "border-radius: 3px;" "margin: 0px;" "padding: 0px;" "}" );

    ui->startBt->setStyleSheet("QPushButton { border: none; background: transparent; }");
    ui->startBt->setIcon(QIcon("C:/Users/ASUS/Downloads/power.png"));
    ui->startBt->setIconSize(ui->startBt->size());

    ui->Screen->setStyleSheet("QLabel {" "background-color: qlineargradient(""spread:pad, x1:0, y1:0, x2:1, y2:1, ""stop:0 rgba(255, 69, 0, 180), ""stop:0.5 rgba(255, 215, 0, 120), ""stop:1 rgba(0, 128, 0, 180) "");"
        "    border: 2px solid rgba(255, 215, 0, 200);" "border-radius: 5px;" "margin: 2px;" "padding: 5px;" "}" );

    ui->zenopix_icon->setPixmap(QPixmap("C:/Users/ASUS/Downloads/fireworks-.png"));
    ui->zenopix_icon->setScaledContents(true);

    ui->znpx->setPixmap((QPixmap("C:/Users/ASUS/Downloads/unnamed.png")));
    ui->znpx->setScaledContents(true);

    core= new Core();
    snowTh= new SnowFlakeAnimationThread(core,this);
}

MainWindow::~MainWindow()
{
    snowTh->stop();
    snowTh->wait();
    delete ui;
}

void MainWindow::on_snowflake_spinbx_valueChanged(int arg1)
{
    core->snowFlakeStaticParameters.NumberOfSnowFlake= arg1;
}


void MainWindow::on_extent_snowflake_spnbx_valueChanged(int arg1)
{
    //yarıçap olarak boyutu alıyorum.
    core->snowFlakeStaticParameters.ExtentSnowFlake= static_cast<double>(arg1)/2.0;
}


void MainWindow::on_color_combobx_currentIndexChanged(int index)
{
    if(index==0){
        core->snowFlakeStaticParameters.randomColorEnable=true;
    }
    else if(index==1){
        core->snowFlakeStaticParameters.randomColorEnable=false;
        core->snowFlakeStaticParameters.SteadyColorEnable=true;
    }
}


void MainWindow::on_Speed_sldr_valueChanged(int value)
{
    if(value>30){
        core->snowFlakeStaticParameters.AnimSpeed= value/10.0;
    }
    else
    {
        core->snowFlakeStaticParameters.AnimSpeed= 1000/(101-value);
    }

}


void MainWindow::on_brightness_sldr_valueChanged(int value)
{
    core->snowFlakeStaticParameters.brightnessChanged= true;

    if (value == 0)
    {
        core->snowFlakeStaticParameters.brightness = 0;
        return;
    }

    double A= 255.0;
    double mu= static_cast<double>(value);

    double sigma = 1.0 + (value / 10.0);
    double brightness= A * exp(-pow(value - mu, 2) / (2 * pow(sigma, 2)));

    if (brightness < 0)
    {
        brightness = 0;
    }

    core->snowFlakeStaticParameters.brightness = static_cast<int>(brightness);
}


void MainWindow::on_startBt_clicked()
{
    snowTh->start();
}

void MainWindow::ViewProcess(cv::Mat imgS)
{
    qimg= matToImage(imgS);
    if(qimg.isNull()){
        qDebug()<<"QImage is empty";
        return;
    }
    ui->Screen->setPixmap(QPixmap::fromImage(qimg));
}

void MainWindow::onprocessFinished(cv::Mat img)
{
    ViewProcess(img);
}

QImage MainWindow::matToImage(const cv::Mat &mat) const noexcept
{
    if(mat.empty())
    {
        qDebug() << "Error: MatToQImage - Input image is empty";
        return QImage(1, 1, QImage::Format_RGB888);
    }
    int imgType =  mat.type();
    int imgDepth = mat.depth();

    int channelCount = mat.channels();
    int channelBits =  mat.elemSize1() * 8;

    QImage::Format format = QImage::Format_Invalid;
    switch (imgType)
    {
    case CV_8UC1:
        format = QImage::Format_Grayscale8;
        break;
    case CV_8UC3:
        format = QImage::Format_BGR888;
        break;
    case CV_8UC4:
        format = QImage::Format_RGBA8888;
        break;
    default:
        qDebug() << "Error: MatToQImage - Unsupported image type.";
        return QImage(1, 1, QImage::Format_RGB888);
    }

    QImage result(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), format);

    return result.copy();
}

void MainWindow::updateRayColors()
{
    if(!core->snowFlakeStaticParameters.randomColorEnable){
        cv::Scalar fixedColor(core->snowFlakeStaticParameters.color[2], core->snowFlakeStaticParameters.color[1], core->snowFlakeStaticParameters.color[0]);
        for(int i=0; i<core->snowFlakeStaticParameters.snowFlakeVector.size(); ++i){
            core->snowFlakeStaticParameters.snowFlakeVector[i].currColor= fixedColor;
        }
    }
}

