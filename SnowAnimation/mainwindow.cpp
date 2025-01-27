#include "mainwindow.h"
#include "rgblabl.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QMessageBox>

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

    ui->label_8->setPixmap((QPixmap("C:/Users/ASUS/Downloads/lantern.png")));
    ui->label_8->setScaledContents(true);


    core= new Core();

    snowTh= new SnowFlakeAnimationThread(core,this);

    tabwidget = new QTabWidget(this);
    sliderTab = new QWidget();
    tabwidget->addTab(sliderTab, "RGB");
    sliderLayout = new QVBoxLayout(sliderTab);
    scrollArea= new QScrollArea(sliderTab);
    scrollArea->setFixedSize(334, 273);

    if(ui->gridLayout){
        ui->gridLayout->addWidget(tabwidget);
        tabwidget->setStyleSheet("background: transparent;");
    }

    rLabel= new RGBLabl(scrollArea);
    rLabel->setGeometry(5,10,256,30);
    rLabel->setScaledContents(true);

    gLabel= new RGBLabl(scrollArea);
    gLabel->setScaledContents(true);
    gLabel->setGeometry(5,50,256,30);

    bLabel= new RGBLabl(scrollArea);
    bLabel->setGeometry(5,90,256,30);
    bLabel->setScaledContents(true);

    connect(snowTh,SIGNAL(processFinished(cv::Mat)),this,SLOT(onprocessFinished(cv::Mat)));

    connect(rLabel, SIGNAL(ValueChanged(int)), this, SLOT(onRedValueChanged(int)));
    connect(gLabel, SIGNAL(ValueChanged(int)), this, SLOT(onGreenValueChanged(int)));
    connect(bLabel, SIGNAL(ValueChanged(int)), this, SLOT(onBlueValueChanged(int)));

    UpdateRGB();

}

MainWindow::~MainWindow()
{
    snowTh->stop();
    snowTh->wait();
    delete ui;
}

void MainWindow::on_lowerR_spnbx_valueChanged(int arg1)
{
    core->setting.LowerRadiusLimit=arg1;
}


void MainWindow::on_UpperR_spnbx_valueChanged(int arg1)
{
    core->setting.UpperRadiusLimit=arg1;
}


void MainWindow::on_NumberOfStar_valueChanged(int arg1)
{
    core->setting.StarCount= arg1;
}


void MainWindow::on_LowerT_spnbx_valueChanged(int arg1)
{
    core->setting.LowerOnTime=arg1;
}


void MainWindow::on_UpperT_spnbx_valueChanged(int arg1)
{
    core->setting.UpperOnTime=arg1;
}


void MainWindow::on_Rising_sldr_valueChanged(int value)
{
    core->setting.RisingSpeed=value;
}


void MainWindow::on_falling_sldr_valueChanged(int value)
{
    core->setting.FallingSpeed=value;
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

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    switch(index){
    case 0:
        core->currMode= Core::None;
        break;
    case 1:
        core->currMode= Core::CircleMode;
        break;
    case 2:
        core->currMode= Core::StarMode;
        break;
    case 3:
        core->currMode= Core::SquareMode;
        break;
    case 4:
        core->currMode= Core::SnowFlakeMode;
    default:
        break;
    }
}

void MainWindow::on_color_combobx_currentIndexChanged(int index)
{
    switch(index){
    case 0:
        break;
    case 1:
        core->setting.randomColorState=true;
        break;
    case 2:
        core->setting.fixedColorState=true;
        core->setting.randomColorState=false;
    default:
        break;
    }
}


void MainWindow::onRedValueChanged(int value)
{
    core->setting.useRGB= true;

    core->rgbWidgetValues.RWidgetValue= value;
    UpdateRGB();

    qDebug() << "onRedValueChanged tetiklendi, değer: " << value;

    core->color[2]= value;
    addColorToSmoothCircleVector();
}

void MainWindow::onGreenValueChanged(int value)
{
    core->setting.useRGB= true;
    core->rgbWidgetValues.GWidgetValue= value;
    UpdateRGB();

    qDebug() << "onGreenValueChanged tetiklendi, değer: " << value;

    core->color[1]= value;
    addColorToSmoothCircleVector();

}

void MainWindow::onBlueValueChanged(int value)
{
    core->setting.useRGB= true;
    core->rgbWidgetValues.BWidgetValue= value;
    UpdateRGB();

    qDebug() << "onBlueValueChanged tetiklendi, değer: " << value;

    core->color[0]= value;
    addColorToSmoothCircleVector();
}

void MainWindow::UpdateRGB()
{
    uint8_t colR,colG,colB;

    core->setting.useRGB= true;

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

void MainWindow::addColorToSmoothCircleVector()
{
    Core::NightSkyStar star;

    int red = qBound(0, static_cast<int>(core->color[0]), 255);
    int green = qBound(0, static_cast<int>(core->color[1]), 255);
    int blue = qBound(0, static_cast<int>(core->color[2]), 255);

    const int baseTotalRGB= 3*190;
    int newTotalRGB= red+green+blue;

    if (newTotalRGB > baseTotalRGB) {
        double scale = static_cast<double>(baseTotalRGB) / newTotalRGB;
        red = static_cast<int>(red * scale);
        green = static_cast<int>(green * scale);
        blue = static_cast<int>(blue * scale);
    }

    QColor newColor(blue, green, red);

    if(core->setting.StarColor== QColor(190,190,190)){
        if(core->setting.useRGB){
            core->setting.StarColor= newColor;
        }
    }
}
