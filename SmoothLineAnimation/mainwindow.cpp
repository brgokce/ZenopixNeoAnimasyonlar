#include "mainwindow.h"
#include "smoothlinesanimationthread.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->startBt->setStyleSheet("QPushButton { border: none; background: transparent; }");
    ui->startBt->setIcon(QIcon("C:/Users/ASUS/Downloads/power-button.png"));
    ui->startBt->setIconSize(ui->startBt->size());

    ui->zenopix_icon->setPixmap(QPixmap("C:/Users/ASUS/Downloads/unnamed.png"));
    ui->zenopix_icon->setScaledContents(true);

    core= new Core();
    smoothTh= new SmoothLinesAnimationThread(core, this);

    tabwidget = new QTabWidget(this);
    sliderTab = new QWidget();
    tabwidget->addTab(sliderTab, "RGB");
    sliderLayout = new QVBoxLayout(sliderTab);
    scrollArea= new QScrollArea(sliderTab);
    scrollArea->setFixedSize(334, 273);

    if(ui->gridLayout_3){
        ui->gridLayout_3->addWidget(tabwidget);
    }

    rLabel= new RgbLabel(scrollArea);
    rLabel->setGeometry(5,10,256,20);
    rLabel->setScaledContents(true);

    gLabel= new RgbLabel(scrollArea);
    gLabel->setScaledContents(true);
    gLabel->setGeometry(5,40,256,20);

    bLabel= new RgbLabel(scrollArea);
    bLabel->setGeometry(5,70,256,20);
    bLabel->setScaledContents(true);

    connect(smoothTh, SIGNAL(processFinished(cv::Mat)), this, SLOT(onProcessFinished(cv::Mat)));

    connect(rLabel, SIGNAL(ValueChanged(int)), this, SLOT(onRedValueChanged(int)));
    connect(gLabel, SIGNAL(ValueChanged(int)), this, SLOT(onGreenValueChanged(int)));
    connect(bLabel, SIGNAL(ValueChanged(int)), this, SLOT(onBlueValueChanged(int)));

    connect(tabwidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);

    UpdateRGB();
}

MainWindow::~MainWindow()
{
    smoothTh->stop();
    smoothTh->wait();
    delete ui;
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

void MainWindow::ViewProcess(cv::Mat imgV)
{
    qimg= matToImage(imgV);

    if(qimg.isNull()){
        qDebug()<<"QImage is empty";
        return;
    }

    ui->Screen->setPixmap(QPixmap::fromImage(qimg));
    ui->Screen->resize(imgV.cols, imgV.rows);
}

void MainWindow::onProcessFinished(cv::Mat img)
{
    ViewProcess(img);
}

void MainWindow::on_Delta_sldr_valueChanged(int value)
{
    core->StaticSmoothSet.Delta= value;
    ui->offst_prc->setText(QString("%1%").arg(value-20));
}

void MainWindow::on_startBt_clicked()
{
    smoothTh->start();
}

void MainWindow::on_Random_bttn_clicked()
{
    core->StaticSmoothSet.randomColorEn=true;
}

void MainWindow::on_standart_bttn_clicked()
{
    core->StaticSmoothSet.randomColorEn= false;
}

void MainWindow::checkRadioButtonState()
{
    if(!ui->standart_bttn->isChecked() && !ui->Random_bttn->isChecked()){
        core->StaticSmoothSet.randomColorEn= false;
    }
}

void MainWindow::onRedValueChanged(int value)
{
    core->StaticSmoothSet.useRGB= true;
    core->StaticSmoothSet.useColorWheel = false;

    core->rgbWidgetValues.RWidgetValue= value;
    UpdateRGB();

    qDebug() << "onRedValueChanged tetiklendi, değer: " << value;

    core->StaticSmoothSet.color[2]= value;
    addColorToSmoothLinesVector();

}

void MainWindow::onGreenValueChanged(int value)
{
    core->StaticSmoothSet.useRGB= true;
    core->StaticSmoothSet.useColorWheel = false;

    core->rgbWidgetValues.GWidgetValue= value;
    UpdateRGB();

    qDebug() << "onGreenValueChanged tetiklendi, değer: " << value;

    core->StaticSmoothSet.color[1]= value;
    addColorToSmoothLinesVector();

}

void MainWindow::onBlueValueChanged(int value)
{
    core->StaticSmoothSet.useRGB= true;
    core->StaticSmoothSet.useColorWheel = false;

    core->rgbWidgetValues.BWidgetValue= value;
    UpdateRGB();

    qDebug() << "onBlueValueChanged tetiklendi, değer: " << value;

    core->StaticSmoothSet.color[0]= value;
    addColorToSmoothLinesVector();
}

void MainWindow::UpdateRGB()
{
    uint8_t colR,colG,colB;

    core->StaticSmoothSet.useRGB= true;

    for(int col=0; col<256; col++)
    {
        colR= col;
        colG= core->rgbWidgetValues.GWidgetValue;
        colB= core->rgbWidgetValues.BWidgetValue;

        if (col < core->rgbWidgetValues.RImage.width())
        {
            core->rgbWidgetValues.RImage.setPixelColor(col, 0, QColor(colR, colG, colB));
        }

        colR= core->rgbWidgetValues.RWidgetValue;
        colG= col;
        colB= core->rgbWidgetValues.BWidgetValue;

        if (col < core->rgbWidgetValues.GImage.width())
        {
            core->rgbWidgetValues.GImage.setPixelColor(col,0, QColor(colR, colG, colB));
        }

        colR= core->rgbWidgetValues.RWidgetValue;
        colG= core->rgbWidgetValues.GWidgetValue;
        colB= col;

        if (col < core->rgbWidgetValues.BImage.width())
        {
            core->rgbWidgetValues.BImage.setPixelColor(col,0, QColor(colR, colG, colB));
        }
    }
    rLabel->setPixmap(QPixmap::fromImage(core->rgbWidgetValues.RImage));
    gLabel->setPixmap(QPixmap::fromImage(core->rgbWidgetValues.GImage));
    bLabel->setPixmap(QPixmap::fromImage(core->rgbWidgetValues.BImage));
}

void MainWindow::onTabChanged(int index)
{

    if (index == 3)
    {
    }
}

void MainWindow::addColorToSmoothLinesVector()
{
    int red = qBound(0, static_cast<int>(core->StaticSmoothSet.color[0]), 255);
    int green = qBound(0, static_cast<int>(core->StaticSmoothSet.color[1]), 255);
    int blue = qBound(0, static_cast<int>(core->StaticSmoothSet.color[2]), 255);

    QColor newColor(blue, green, red);

    core->StaticSmoothSet.SmoothLinesC.clear();
    core->StaticSmoothSet.SmoothLinesC.push_back(newColor);
}

void MainWindow::on_speed_sldr_valueChanged(int value)
{
    core->StaticSmoothSet.userChangeSpeed= true;

    int minimumSpeed= ui->speed_sldr->minimum();
    int maximumSpeed= ui->speed_sldr->maximum();
    core->StaticSmoothSet.Speed = maximumSpeed - ((maximumSpeed - minimumSpeed) / 100.0) * value;
}
