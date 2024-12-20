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

    sliderTabPalette= new QWidget();

    tabwidget->addTab(sliderTab, "RGB");

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

    tabwidget->addTab(sliderTabPalette, "Palette");

    sliderLayout = new QVBoxLayout(sliderTab);

    sliderLayout = new QVBoxLayout(sliderTabPalette);

    scrollArea= new QScrollArea(sliderTab);

    palettescrolarea= new QScrollArea(sliderTabPalette);

    scrollArea->setFixedSize(334, 273);

    palettescrolarea->setFixedSize(334, 274);

    if (ui->gridLayout_2)
    {
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

    paletteLabel= new labelCLASS(palettescrolarea);

    paletteLabel->setGeometry(7,20,256,25);

    paletteLabel->setScaledContents(true);

    QWidget *scrollWidget = new QWidget(ui->scrollArea);
    QVBoxLayout *layoutA = new QVBoxLayout(scrollWidget);

    AncX = new AnchorLabel(core, scrollWidget);
    AncX->setAButton();
    AncX->setGeometry(10, 10, 300, 30);
    AncX->setScaledContents(true);
    layoutA->addWidget(AncX);

    AncY = new AnchorLabel(core, scrollWidget);
    AncY->setBButton();
    AncY->setGeometry(10, 50, 300, 30);
    AncY->setScaledContents(true);
    layoutA->addWidget(AncY);

    AnchorLabel *AncZ = new AnchorLabel(core, scrollWidget);
    AncZ->setCButton();
    AncZ->setGeometry(10, 120, 300, 30);
    AncZ->setScaledContents(true);
    layoutA->addWidget(AncZ);

    scrollWidget->setLayout(layoutA);
    ui->scrollArea->setWidget(scrollWidget);

    connect(rLabel, SIGNAL(ValueChanged(int)), this, SLOT(onRedValueChanged(int)));
    connect(gLabel, SIGNAL(ValueChanged(int)), this, SLOT(onGreenValueChanged(int)));
    connect(bLabel, SIGNAL(ValueChanged(int)), this, SLOT(onBlueValueChanged(int)));

    connect(rayAnimthread,SIGNAL(processFinished(cv::Mat)),this,SLOT(onprocessFinished(cv::Mat)));

    connect(colorWheel, &ColorWheelWidget::colorSelected, this, &MainWindow::onColorSelected);

    connect(hsbcolorwheel, &HSBColorWheel::hueChanged, this, &MainWindow::onHueChanged);
    connect(hsbcolorwheel, &HSBColorWheel::saturationChanged, this, &MainWindow::onSaturationChanged);
    connect(hsbcolorwheel, &HSBColorWheel::brightnessChanged, this, &MainWindow::onBrightnessChanged);

    connect(tabwidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);
    connect(tabwidget, &QTabWidget::currentChanged, this, &MainWindow::onTabCWheel);
    connect(tabwidget, &QTabWidget::currentChanged, this, &MainWindow::onTabHSB);
    connect(tabwidget, &QTabWidget::currentChanged, this, &MainWindow::onTabPltte);

    connect(paletteLabel, &labelCLASS::PaletteValueChanged, this, &MainWindow::handlePaletteValueChange);
    connect(AncZ, &AnchorLabel::AScaleChanged, this, &MainWindow::Z_Axis_Anchor);

    core->spinbox= ui->spinBox_3;
    UpdateRGB();
    drawColors();
}

MainWindow::~MainWindow()
{
    rayAnimthread->stop(); // Thread'i düzgün şekilde durdur
    rayAnimthread->wait(); // Thread'in tamamen durmasını bekle
    delete ui;
}

void MainWindow::Z_Axis_Anchor(float scaleF, cv::Mat& imgZ)
{
    if (scaleF <= 0) {
        qDebug() << "Error: Invalid scale factor (must be greater than 0)";
        return;
    }

    if (imgZ.cols <= 0 || imgZ.rows <= 0) {
        qDebug() << "Hata: Geçersiz görüntü boyutları";
        return;
    }

    int ARectW= imgZ.cols/(scaleF);
    int ARectH= imgZ.rows/(scaleF);

    int stX= (imgZ.cols-ARectW)/2;
    int stY= (imgZ.rows-ARectH)/2;

    stX= std::max(0, stX);
    stY= std::max(0, stY);

    ARectW= std::min(ARectW, imgZ.cols-stX);
    ARectH= std::min(ARectH, imgZ.rows-stY);

    if(imgZ.cols*scaleF>ui->Screen->width()|| imgZ.rows*scaleF>ui->Screen->height()){
        cv::Rect ARoi(stX, stY, ARectW, ARectH);
        cv::Mat ARoiImg= imgZ(ARoi);

        if(ARoiImg.empty()){
            qDebug()<<"Error: Cropped image is empty";
            return;
        }
        cv::resize(ARoiImg, ARoiImg, cv::Size(ui->Screen->width(), ui->Screen->height()));

        ViewProcess(ARoiImg);
    }
    else
    {
        int ANewW= imgZ.cols * scaleF;
        int ANewH= imgZ.rows * scaleF;

        ANewW = std::max(1, ANewW);
        ANewH = std::max(1, ANewH);

        if (ANewW <= 0 || ANewH <= 0) {
            qDebug() << "Hata: Geçersiz yeni boyutlar - ANewW: " << ANewW << " ANewH: " << ANewH;
            return;
        }

        QImage ZScaleImg(ui->Screen->width(), ui->Screen->height(), QImage::Format_RGB888);
        ZScaleImg.fill(Qt::black);

        cv::resize(imgZ, imgZ, cv::Size(ANewW, ANewH));
        QImage AImgQImage= matToImage(imgZ);

        QPainter painter(&ZScaleImg);
        int offsetX = (ZScaleImg.width() - AImgQImage.width())/2;
        int offsetY = (ZScaleImg.height() - AImgQImage.height())/2;
        painter.drawImage(offsetX, offsetY, AImgQImage);

        ViewProcess(QImageToMat(ZScaleImg));
    }
}

void MainWindow::Scale(cv::Mat imgR)
{
    core->rayanimset.ScaleOn=true;
    ScaleTablePos(core->rayanimset.MousePos, core->rayanimset.Scale);

    int rectW= imgR.cols/(core->rayanimset.Scale);
    int rectH= imgR.rows/(core->rayanimset.Scale);

    int startX= (imgR.cols-rectW)/2;
    int startY= (imgR.rows-rectH)/2;

    startX = std::max(0, startX);
    startY = std::max(0, startY);

    rectW = std::min(rectW, imgR.cols - startX);
    rectH = std::min(rectH, imgR.rows - startY);

    if (imgR.cols*core->rayanimset.Scale>ui->Screen->width() || imgR.rows*core->rayanimset.Scale>ui->Screen->height()){

        cv::Rect roi(startX,startY,rectW,rectH);
        cv::Mat roiImg= imgR(roi);

        if (roiImg.empty()) {
            qDebug() << "Error: Cropped image is empty!";
            return;
        }

        cv::resize(roiImg, roiImg, cv::Size(ui->Screen->width(),ui->Screen->height()));

        ViewProcess(roiImg);
    }

    else
    {
        int newW = imgR.cols * core->rayanimset.Scale;
        int newH = imgR.rows * core->rayanimset.Scale;

        QImage scaledImage(ui->Screen->width(), ui->Screen->height(), QImage::Format_RGB888);
        scaledImage.fill(Qt::black);

        cv::resize(imgR, imgR, cv::Size(newW, newH));

        QImage imgQImage = matToImage(imgR);

        QPainter painter(&scaledImage);
        int offsetX = (scaledImage.width() - imgQImage.width())/2;
        int offsetY = (scaledImage.height() - imgQImage.height())/2;
        painter.drawImage(offsetX, offsetY, imgQImage);

        ViewProcess(QImageToMat(scaledImage));
    }
}

void MainWindow::handlePaletteValueChange(QColor color,int pieceIndex)
{
    core->rayanimset.usePalette=true;
    qDebug() << "Color changed to:" << color.name() << " for pieceIndex:" << pieceIndex;

    if (pieceIndex >= 0 && pieceIndex < 8)
    {
        if (core->PaletteColor.size() < 8)
        {
            core->PaletteColor.resize(8);
        }

        qDebug() << "Setting PaletteColor[" << pieceIndex << "] to:" << "R:" << color.red() << "G:" << color.green() << "B:" << color.blue();
        core->PaletteColor[pieceIndex] = cv::Scalar(static_cast<double>(color.blue()),static_cast<double>(color.green()),static_cast<double>(color.red()));
        core->rayanimset.selectedIndex=pieceIndex;

        if (pieceIndex < core->rayanimset.Ray_Lines.size())
        {
            core->rayanimset.Ray_Lines[pieceIndex].dColor = core->PaletteColor[pieceIndex];

            qDebug() << "Updated Ray_Line[" << pieceIndex << "] color:"
                     << "R:" << core->rayanimset.Ray_Lines[pieceIndex].dColor[2]
                     << "G:" << core->rayanimset.Ray_Lines[pieceIndex].dColor[1]
                     << "B:" << core->rayanimset.Ray_Lines[pieceIndex].dColor[0];
        }
    }
    drawColors();
    updateRayPaletteColors();
}

void MainWindow::drawColors()
{
    core->rayanimset.usePalette = true;

    QImage image(paletteLabel->size(), QImage::Format_RGB32);
    image.fill(Qt::transparent);

    int pieceWidth = paletteLabel->width() / 8;

    for (int p = 0; p < 8; ++p)
    {
        QColor color;

        color = paletteLabel->DefaultPaletteColor(p + 1);

        for (int x = 0; x < pieceWidth; ++x)
        {
            for (int y = 0; y < paletteLabel->height(); ++y)
            {
                image.setPixelColor(p * pieceWidth + x, y, color);
            }
        }
    }

    paletteLabel->setPixmap(QPixmap::fromImage(image));
    paletteLabel->update();
}

void MainWindow::onRedValueChanged(int value)
{
    core->rayanimset.useRGB= true;
    core->rayanimset.useColorWheel = false;
    core->rayanimset.usePalette=false;

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
    core->rayanimset.usePalette=false;

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
    core->rayanimset.usePalette=false;

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
    core->rayanimset.color[0]= value;
    core->rayanimset.useColorWheel = false;
    updateRayColors();
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    core->rayanimset.color[1]= value;
    core->rayanimset.useColorWheel = false;
    updateRayColors();
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    core->rayanimset.color[2]= value;
    core->rayanimset.useColorWheel = false;
    updateRayColors();
}

void MainWindow::on_radioButton_2_clicked()
{
    core->rayanimset.randomColorEnable=false;

    if(!core->rayanimset.useColorWheel)
    {
        ui->horizontalSlider->setEnabled(true);
        ui->horizontalSlider_2->setEnabled(true);
        ui->horizontalSlider_3->setEnabled(true);
        core->rayanimset.useRGB= true;
        updateRayColors();
    }
    else if(core->rayanimset.useHSB)
    {
        core->rayanimset.useHSB=true;
    }
    else
    {
        core->rayanimset.useColorWheel=true;
        core->rayanimset.useRGB= false;
        core->rayanimset.useHSB=false;
        core->rayanimset.usePalette=false;
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

void MainWindow::ViewProcess(cv::Mat imgP)
{
    qimg= matToImage(imgP);

    if (qimg.isNull()) {
        qDebug() << "QImage is empty!";
        return;
    }

    ui->Screen->setPixmap(QPixmap::fromImage(qimg));
    ui->Screen->resize(imgP.cols, imgP.rows);

}

void MainWindow::onprocessFinished(cv::Mat img)
{
    if(core->rayanimset.ScaleOn){
        core->rayanimset.AScaledOn=false;
        Scale(img);
    }
    if(core->rayanimset.AScaledOn){
        Z_Axis_Anchor(core->currScale, img);
    }
    else
    {
        ViewProcess(img);
    }
}

cv::Mat MainWindow::QImageToMat(const QImage &image)
{
    if (image.isNull()) {
        qDebug() << "QImage is null, returning empty cv::Mat";
        return cv::Mat();
    }

    switch (image.format()) {
    case QImage::Format_RGB888: {

        cv::Mat mat(image.height(), image.width(), CV_8UC3, (void*)image.bits(), image.bytesPerLine());
        return mat.clone();
    }
    case QImage::Format_BGR888: {

        cv::Mat mat(image.height(), image.width(), CV_8UC3, (void*)image.bits(), image.bytesPerLine());
        return mat.clone();
    }
    case QImage::Format_RGB32: {

        cv::Mat mat(image.height(), image.width(), CV_8UC4, (void*)image.bits(), image.bytesPerLine());
        cv::Mat matRGB;
        cv::cvtColor(mat, matRGB, cv::COLOR_BGRA2BGR);
        return matRGB.clone();
    }
    case QImage::Format_Grayscale8: {

        cv::Mat mat(image.height(), image.width(), CV_8UC1, (void*)image.bits(), image.bytesPerLine());
        return mat.clone();
    }
    case QImage::Format_ARGB32: {

        cv::Mat mat(image.height(), image.width(), CV_8UC4, (void*)image.bits(), image.bytesPerLine());
        cv::Mat matRGB;
        cv::cvtColor(mat, matRGB, cv::COLOR_BGRA2BGR);
        return matRGB.clone();
    }
    case QImage::Format_Indexed8: {

        QImage imgCopy = image.convertToFormat(QImage::Format_RGB888);
        return QImageToMat(imgCopy);
    }
    default:
        qDebug() << "Unsupported QImage format: " << image.format();
        return cv::Mat();
    }
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    core->rayanimset.ScaleOn= true;
    core->rayanimset.MousePos= event->position();

    if(event->angleDelta().y()>0)
    {
        core->rayanimset.ScaleFactor=1.1;
        core->rayanimset.Scale*=core->rayanimset.ScaleFactor;
    }

    else
    {
        core->rayanimset.ScaleFactor=0.9;
        core->rayanimset.Scale*=core->rayanimset.ScaleFactor;
    }

    event->accept();
}

void MainWindow::ScaleTablePos(const QPointF &currCursorPoint, double scaleFactor)
{
    double newX_d = core->rayanimset.MousePos.x() - (core->rayanimset.MousePos.x() + currCursorPoint.x() - (core->rayanimset.MousePos.x() + currCursorPoint.x()) * scaleFactor);
    double newY_d = core->rayanimset.MousePos.y() - (core->rayanimset.MousePos.y() + currCursorPoint.y() - (core->rayanimset.MousePos.y() + currCursorPoint.y()) * scaleFactor);

    int newX = round(newX_d * 1000.0) / 1000.0;
    int newY = round(newY_d * 1000.0) / 1000.0;

    core->rayanimset.MousePos.setX(newX);
    core->rayanimset.MousePos.setY(newY);

    update();
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
                core->rayanimset.usePalette=false;
            }
        }

        else
        {
            core->rayanimset.useColorWheel = true;

            cv::Scalar fixedColor(core->rayanimset.color[2], core->rayanimset.color[1], core->rayanimset.color[0]);
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
  if (!core->rayanimset.randomColorEnable)
  {
     if(core->rayanimset.useRGB)
      {

        cv::Scalar fixedColor(core->RGBcolor[0], core->RGBcolor[1], core->RGBcolor[2]);
        for (int i = 0; i < core->rayanimset.Ray_Lines.size(); ++i)
        {
            core->rayanimset.Ray_Lines[i].dColor = fixedColor;
        }
        core->rayanimset.useHSB= false;
        core->rayanimset.useColorWheel = false;
        core->rayanimset.usePalette=false;
      }
  }
    rayAnimthread->updateColors();
}

void MainWindow::updateRayPaletteColors()
{
    core->rayanimset.usePalette=true;

    if (core->rayanimset.randomColorEnable || !core->rayanimset.usePalette)
        return;

    int selectedColorIndex = core->rayanimset.selectedIndex;

    if(core->rayanimset.usePalette)
 {

      for (int i = 0; i < core->rayanimset.Ray_Lines.size(); ++i)
     {
           core->rayanimset.Ray_Lines[i].dColor = core->PaletteColor[selectedColorIndex];
     }

     core->rayanimset.useHSB = false;
     core->rayanimset.useColorWheel = false;
     core->rayanimset.useRGB = false;
 }
    rayAnimthread->updateColors();
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
        updateRayColors();
    }
    qDebug() << "Hue: " << hue;
}

void MainWindow::onSaturationChanged(int saturation)
{
    if (core->rayanimset.lastSaturation != saturation) {
        core->rayanimset.lastSaturation = saturation;
        core->rayanimset.useHSB = true;
        core->RGBcolor= false;
        updateRayColors();
    }
    qDebug() << "Saturation: " << saturation;
}

void MainWindow::onBrightnessChanged(int brightness)
{
    if (core->rayanimset.lastBrightness != brightness) {
        core->rayanimset.lastBrightness = brightness;
        core->rayanimset.useHSB = true;
        core->RGBcolor= false;
        updateRayColors();
    }
    qDebug() << "Brightness: " << brightness;
}

void MainWindow::onTabChanged(int index)
{

    if (index == 3)
    {
    }
}

void MainWindow::onTabPltte(int index)
{
    if(index==2)
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

