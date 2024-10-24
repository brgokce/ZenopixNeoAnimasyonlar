#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include "ColorWheelWidget.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    core= new Core();

    rayAnimthread= new RayAnimThread(core, this);

    colorWheel= new ColorWheelWidget(this);

    hsbcolorwheel= new HSBColorWheel(core,this);

    tabwidget = new QTabWidget(this);

    sliderTab = new QWidget();

    tabwidget->addTab(sliderTab, "RGB");

    sliderLayout = new QVBoxLayout(sliderTab);

    scrollArea= new QScrollArea(sliderTab);

    scrollArea->setFixedSize(334, 273);


    if (ui->gridLayout_2) {
        ui->gridLayout_2->addWidget(tabwidget);
    }

    hsbcolorwheel->setHueText("Hue");
    QLabel* HueLabel = hsbcolorwheel->getHueLabel();

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(HueLabel);

    hsbcolorwheel->setSaturationText("Saturation");

    QLabel* saturationLabel = hsbcolorwheel->getSaturationLabel();
    QVBoxLayout* layoutSat = new QVBoxLayout();
    layoutSat->addWidget(saturationLabel);

    hsbcolorwheel->setBrightnessText("Brightness");

    QLabel* brightnesslabel = hsbcolorwheel->getSaturationLabel();
    QVBoxLayout* layoutBrh = new QVBoxLayout();
    layoutBrh->addWidget(brightnesslabel);

    rLabel= new ChannelLabel(scrollArea);

    rLabel->setGeometry(10,10,256,30);

    rLabel->setScaledContents(true);

    gLabel= new ChannelLabel(scrollArea);

    gLabel->setScaledContents(true);

    gLabel->setGeometry(10,79,256,30);

    bLabel= new ChannelLabel(scrollArea);

    bLabel->setGeometry(10,150,256,30);

    bLabel->setScaledContents(true);

    connect(rLabel, SIGNAL(ValueChanged(int)), this, SLOT(onRedValueChanged(int)));
    connect(gLabel, SIGNAL(ValueChanged(int)), this, SLOT(onGreenValueChanged(int)));
    connect(bLabel, SIGNAL(ValueChanged(int)), this, SLOT(onBlueValueChanged(int)));

    QWidget *hsbTab = new QWidget();
    QVBoxLayout *hsbLayout = new QVBoxLayout(hsbTab);
    hsbcolorwheel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    hsbLayout->addWidget(hsbcolorwheel);
    hsbTab->setLayout(hsbLayout);
    tabwidget->addTab(hsbTab, "HSB Wheel");

    QWidget *tab2 = new QWidget();
    tabwidget->addTab(tab2, "Color Wheel");
    tab2->setLayout(new QVBoxLayout());
    tab2->layout()->addWidget(colorWheel);

    QWidget *tab3 = new QWidget();
    QVBoxLayout *layout3 = new QVBoxLayout();
    tab3->setLayout(layout3);
    tabwidget->addTab(tab3, "Palette");

    connect(rayAnimthread,SIGNAL(processFinished(cv::Mat)),this,SLOT(onprocessFinished(cv::Mat)));

    connect(colorWheel, &ColorWheelWidget::colorHovered, this, &MainWindow::onColorHovered);

    connect(colorWheel, &ColorWheelWidget::colorSelected, this, &MainWindow::onColorSelected);

    connect(hsbcolorwheel, &HSBColorWheel::hueChanged, this, &MainWindow::onHueChanged);
    connect(hsbcolorwheel, &HSBColorWheel::saturationChanged, this, &MainWindow::onSaturationChanged);
    connect(hsbcolorwheel, &HSBColorWheel::brightnessChanged, this, &MainWindow::onBrightnessChanged);

    connect(tabwidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);
    connect(tabwidget, &QTabWidget::currentChanged, this, &MainWindow::onTabCWheel);
    connect(tabwidget, &QTabWidget::currentChanged, this, &MainWindow::onTabHSB);

    core->spinbox= ui->spinBox_3;
    UpdateRGB();

}

MainWindow::~MainWindow()
{
    rayAnimthread->stop(); // Thread'i düzgün şekilde durdur
    rayAnimthread->wait(); // Thread'in tamamen durmasını bekle
    delete ui;
}

void MainWindow::onRedValueChanged(int value)
{
    core->rayanimset.useRGB= true;
    core->rayanimset.useColorWheel = false;

    core->rgbWidgetValues.RWidgetValue= value;
    UpdateRGB();

    qDebug() << "onRedValueChanged tetiklendi, değer: " << value;

    core->RGBcolor[2]= value;
    updateRayRGBColors();

}

void MainWindow::onGreenValueChanged(int value)
{
    core->rayanimset.useRGB= true;
    core->rayanimset.useColorWheel = false;

    core->rgbWidgetValues.GWidgetValue= value;
    UpdateRGB();

    qDebug() << "onGreenValueChanged tetiklendi, değer: " << value;

    core->RGBcolor[1]= value;
    updateRayRGBColors();

}

void MainWindow::onBlueValueChanged(int value)
{
    core->rayanimset.useRGB= true;
    core->rayanimset.useColorWheel = false;

    core->rgbWidgetValues.BWidgetValue= value;
    UpdateRGB();

    qDebug() << "onBlueValueChanged tetiklendi, değer: " << value;

    core->RGBcolor[0]= value;
    updateRayRGBColors();
}

void MainWindow::UpdateRGB()
{
    uint8_t colR,colG,colB;

    core->rayanimset.useRGB= true;

    for(int col=0; col<256; col++)
    {
        colR= col;
        colG= core->rgbWidgetValues.GWidgetValue;
        colB= core->rgbWidgetValues.BWidgetValue;

        if (col < core->rgbWidgetValues.Rimage.width())
        {
            core->rgbWidgetValues.Rimage.setPixelColor(col, 0, QColor(colR, colG, colB));
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
    rLabel->setPixmap(QPixmap::fromImage(core->rgbWidgetValues.Rimage));
    gLabel->setPixmap(QPixmap::fromImage(core->rgbWidgetValues.GImage));
    bLabel->setPixmap(QPixmap::fromImage(core->rgbWidgetValues.BImage));
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    core->rayanimset.NumberOfRay= arg1;

}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    core->rayanimset.tickness=arg1;
}

void MainWindow::on_spinBox_3_valueChanged(int arg1)
{
    core->rayanimset.Ray_bore= arg1;
}


void MainWindow::on_radioButton_clicked()
{
    core->rayanimset.randomColorEnable =true;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    core->rayanimset.color[0]= value; //red
    core->rayanimset.useColorWheel = false;
    updateRayColors();

}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    core->rayanimset.color[1]= value; //green
    core->rayanimset.useColorWheel = false;
    updateRayColors();

}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    core->rayanimset.color[2]= value; //blue
    core->rayanimset.useColorWheel = false;
    updateRayColors();

}

void MainWindow::on_radioButton_2_clicked()
{
    core->rayanimset.randomColorEnable=false;

    if(!core->rayanimset.useColorWheel)
    {
        ui->horizontalSlider->setEnabled(true); // Kırmızı slider'ı etkinleştir
        ui->horizontalSlider_2->setEnabled(true); // Yeşil slider'ı etkinleştir
        ui->horizontalSlider_3->setEnabled(true);
        core->rayanimset.useRGB= true;
        updateRayColors();
    }
    else if(core->rayanimset.useHSB)
    {
        core->rayanimset.useHSB=true;
    }
    else if(!core->rayanimset.useColorWheel &&core->rayanimset.useHSB &&  core->rayanimset.useRGB && !core->rayanimset.randomColorEnable)
    {
        core->rayanimset.color= cv::Scalar(255,255,255);
    }

    else
    {
        core->rayanimset.useColorWheel=true;
        core->rayanimset.useRGB= false;
        core->rayanimset.useHSB=false;
    }
}

void MainWindow::checkRadioButtonState()
{
    if (!ui->radioButton->isChecked() && !ui->radioButton_2->isChecked()) {
        core->rayanimset.randomColorEnable = false;  // Hiçbir buton tıklanmadıysa false yap
    }
}

void MainWindow::on_horizontalSlider_4_valueChanged(int value)
{
    core->rayanimset.userChangedSpeed= true;
    if (value > 50)
    {
        core->rayanimset.Speed = 110 - value;

    }

    else
    {
        core->rayanimset.Speed = -2*(value)+200;
    }
}

void MainWindow::onprocessFinished(cv::Mat img)
{
    QImage qimg= matToImage(img);
    ui->Screen->setPixmap(QPixmap::fromImage(qimg));
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

void MainWindow::on_pushButton_clicked()
{
    rayAnimthread->start();
}

void MainWindow::updateRayColors()
{
    int currentHue = hsbcolorwheel->getCurrentHue();
    int currentSaturation = hsbcolorwheel->getCurrentSaturation();
    int currentBrightness = hsbcolorwheel->getCurrentBrightness();

    if (!core->rayanimset.randomColorEnable) // Sabit renk aktifse
    {

        QColor color = hsbcolorwheel->hsbToRgb(currentHue, currentSaturation, currentBrightness);
        core->HSBcolor = hsbcolorwheel->qColorToScalar(color);

        if(core->rayanimset.useHSB)
        {
            cv::Scalar fixedColor(core->HSBcolor[0], core->HSBcolor[1], core->HSBcolor[2]); // BGR sırası
            for (int i = 0; i < core->rayanimset.Ray_Lines.size(); ++i)
            {
                core->rayanimset.Ray_Lines[i].dColor = fixedColor; // Sabit renk kullan
                core->rayanimset.useRGB= false;
                core->rayanimset.useColorWheel = false;
            }
        }

        else
        {
            core->rayanimset.useColorWheel = true;

            cv::Scalar fixedColor(core->rayanimset.color[2], core->rayanimset.color[1], core->rayanimset.color[0]); // BGR sırası
            for (int i = 0; i < core->rayanimset.Ray_Lines.size(); ++i)
            {
                core->rayanimset.Ray_Lines[i].dColor = fixedColor;
            }
        }

    }

    rayAnimthread->updateColors();

}

void MainWindow::updateRayRGBColors()
{
  if (!core->rayanimset.randomColorEnable) // Sabit renk aktifse
  {
     if(core->rayanimset.useRGB)
      {

        cv::Scalar fixedColor(core->RGBcolor[0], core->RGBcolor[1], core->RGBcolor[2]); // BGR sırası
        for (int i = 0; i < core->rayanimset.Ray_Lines.size(); ++i)
        {
            core->rayanimset.Ray_Lines[i].dColor = fixedColor; // Sabit renk kullan
            core->rayanimset.useHSB= false;
            core->rayanimset.useColorWheel = false;
        }
      }
  }
    rayAnimthread->updateColors();
}

void MainWindow::onColorHovered(const QColor &color)
{
    // Example: Set the background color of the MainWindow to the hovered color
    //QPalette palette = this->palette();
    //palette.setColor(QPalette::Window, color);
    //this->setPalette(palette);

    //qDebug() << "Selected color:" << color;

    // ui->coloscreen->setText("Hovered Color: " + color.name());
}

void MainWindow::onColorSelected(const QColor &color)
{
    if (!color.isValid())
    {
        qDebug() << "Invalid color selected!";
        return;
    }

    int red = color.red();
    int green = color.green();
    int blue = color.blue();

    core->rayanimset.color[0] = red;
    core->rayanimset.color[1] = green;
    core->rayanimset.color[2] = blue;

    core->currentRayColor = cv::Scalar(red, green, blue);

    // Renkleri kontrol et
    qDebug() << "Selected Color (R,G,B):" << red << green << blue;

    core->rayanimset.useColorWheel=true;
    core->rayanimset.useHSB=false;
    core->RGBcolor= false;

    ui->horizontalSlider->setValue(red);
    ui->horizontalSlider_2->setValue(green);
    ui->horizontalSlider_3->setValue(blue);

    updateRayColors();
}

void MainWindow::onHueChanged(int hue)
{
    if (core->rayanimset.lastHue != hue) {
        core->rayanimset.lastHue = hue;
        core->rayanimset.useHSB = true;
        updateRayColors();  // Update colors when hue changes
    }
    qDebug() << "Hue: " << hue;
}

void MainWindow::onSaturationChanged(int saturation)
{
    if (core->rayanimset.lastSaturation != saturation) {
        core->rayanimset.lastSaturation = saturation;
        core->rayanimset.useHSB = true;
        core->RGBcolor= false;
        updateRayColors();  // Update colors when saturation changes
    }
    qDebug() << "Saturation: " << saturation;
}

void MainWindow::onBrightnessChanged(int brightness)
{
    if (core->rayanimset.lastBrightness != brightness) {
        core->rayanimset.lastBrightness = brightness;
        core->rayanimset.useHSB = true;
        core->RGBcolor= false;
        updateRayColors();  // Update colors when brightness changes
    }
    qDebug() << "Brightness: " << brightness;
}

void MainWindow::onTabChanged(int index)
{

    if (index == 3)
    {

    }
}

void MainWindow::onTabCWheel(int index)
{
    if(index==1)
    {

    }
}

void MainWindow::onTabHSB(int index)
{
    if(index==0)
    {

    }
}
