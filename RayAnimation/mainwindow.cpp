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

    if(ui->gridLayout)
    {
        ui->gridLayout->addWidget(hsbcolorwheel);
    }

    ui->verticalLayout->addWidget(colorWheel);

    connect(rayAnimthread,SIGNAL(processFinished(cv::Mat)),this,SLOT(onprocessFinished(cv::Mat)));

    connect(colorWheel, &ColorWheelWidget::colorHovered, this, &MainWindow::onColorHovered);

    connect(colorWheel, &ColorWheelWidget::colorSelected, this, &MainWindow::onColorSelected);

    connect(hsbcolorwheel, &HSBColorWheel::hueChanged, this, &MainWindow::onHueChanged);
    connect(hsbcolorwheel, &HSBColorWheel::saturationChanged, this, &MainWindow::onSaturationChanged);
    connect(hsbcolorwheel, &HSBColorWheel::brightnessChanged, this, &MainWindow::onBrightnessChanged);

    core->spinbox= ui->spinBox_3;

}

MainWindow::~MainWindow()
{
    rayAnimthread->stop(); // Thread'i düzgün şekilde durdur
    rayAnimthread->wait(); // Thread'in tamamen durmasını bekle
    delete ui;
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
        updateRayColors();
    }
    else if(core->rayanimset.useHSB)
    {
        core->rayanimset.useHSB=true;
    }

    else
    {
        core->rayanimset.useColorWheel=true;
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
        if (currentHue == 0 || currentHue == 360)
        {
            currentSaturation = 255; // Tam doygunluk
            currentBrightness = 255; // Tam parlaklık
        }

        QColor color = hsbcolorwheel->hsbToRgb(currentHue, currentSaturation, currentBrightness);
        core->HSBcolor = hsbcolorwheel->qColorToScalar(color);


        if(core->rayanimset.useHSB)
        {
            cv::Scalar fixedColor(core->HSBcolor[0], core->HSBcolor[1], core->HSBcolor[2]); // BGR sırası
            for (int i = 0; i < core->rayanimset.Ray_Lines.size(); ++i)
            {
                core->rayanimset.Ray_Lines[i].dColor = fixedColor; // Sabit renk kullan
            }
        }
        else
        {
            cv::Scalar fixedColor(core->rayanimset.color[2], core->rayanimset.color[1], core->rayanimset.color[0]); // BGR sırası
            for (int i = 0; i < core->rayanimset.Ray_Lines.size(); ++i)
            {
                core->rayanimset.Ray_Lines[i].dColor = fixedColor; // Sabit renk kullan
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
        updateRayColors();  // Update colors when saturation changes
    }
    qDebug() << "Saturation: " << saturation;
}

void MainWindow::onBrightnessChanged(int brightness)
{
    if (core->rayanimset.lastBrightness != brightness) {
        core->rayanimset.lastBrightness = brightness;
        core->rayanimset.useHSB = true;
        updateRayColors();  // Update colors when brightness changes
    }
    qDebug() << "Brightness: " << brightness;
}
