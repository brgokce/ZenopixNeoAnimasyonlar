/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *startBt;
    QLabel *Screen;
    QComboBox *color_combobx;
    QLabel *label_5;
    QLabel *label_9;
    QComboBox *comboBox;
    QLabel *zenopix_icon;
    QLabel *znpx;
    QLabel *label_11;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_8;
    QSpinBox *NumberOfStar;
    QLabel *label_10;
    QSpinBox *lowerR_spnbx;
    QLabel *label_12;
    QSpinBox *UpperR_spnbx;
    QLabel *label_13;
    QSpinBox *LowerT_spnbx;
    QSpinBox *UpperT_spnbx;
    QLabel *label_14;
    QLabel *label_15;
    QSlider *Rising_sldr;
    QLabel *label_16;
    QSlider *falling_sldr;
    QLabel *label_17;
    QLabel *label_18;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(522, 850);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        startBt = new QPushButton(centralwidget);
        startBt->setObjectName("startBt");
        startBt->setGeometry(QRect(200, 750, 83, 41));
        Screen = new QLabel(centralwidget);
        Screen->setObjectName("Screen");
        Screen->setGeometry(QRect(30, 400, 460, 290));
        Screen->setStyleSheet(QString::fromUtf8(""));
        color_combobx = new QComboBox(centralwidget);
        color_combobx->addItem(QString());
        color_combobx->addItem(QString());
        color_combobx->addItem(QString());
        color_combobx->setObjectName("color_combobx");
        color_combobx->setGeometry(QRect(10, 290, 171, 28));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 270, 181, 20));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 210, 201, 20));
        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(10, 230, 171, 31));
        zenopix_icon = new QLabel(centralwidget);
        zenopix_icon->setObjectName("zenopix_icon");
        zenopix_icon->setGeometry(QRect(380, 70, 121, 91));
        znpx = new QLabel(centralwidget);
        znpx->setObjectName("znpx");
        znpx->setGeometry(QRect(490, 0, 31, 21));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(320, 750, 161, 31));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(190, 210, 231, 151));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(430, 210, 81, 101));
        NumberOfStar = new QSpinBox(centralwidget);
        NumberOfStar->setObjectName("NumberOfStar");
        NumberOfStar->setGeometry(QRect(370, 30, 131, 29));
        NumberOfStar->setMinimum(50);
        NumberOfStar->setMaximum(100);
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 10, 151, 20));
        lowerR_spnbx = new QSpinBox(centralwidget);
        lowerR_spnbx->setObjectName("lowerR_spnbx");
        lowerR_spnbx->setGeometry(QRect(10, 30, 151, 29));
        lowerR_spnbx->setMinimum(1);
        lowerR_spnbx->setMaximum(100);
        label_12 = new QLabel(centralwidget);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 70, 151, 20));
        UpperR_spnbx = new QSpinBox(centralwidget);
        UpperR_spnbx->setObjectName("UpperR_spnbx");
        UpperR_spnbx->setGeometry(QRect(200, 30, 151, 29));
        UpperR_spnbx->setMinimum(3);
        UpperR_spnbx->setMaximum(100);
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(200, 10, 151, 20));
        LowerT_spnbx = new QSpinBox(centralwidget);
        LowerT_spnbx->setObjectName("LowerT_spnbx");
        LowerT_spnbx->setGeometry(QRect(10, 80, 151, 29));
        LowerT_spnbx->setMinimum(1000);
        LowerT_spnbx->setMaximum(10000);
        UpperT_spnbx = new QSpinBox(centralwidget);
        UpperT_spnbx->setObjectName("UpperT_spnbx");
        UpperT_spnbx->setGeometry(QRect(200, 80, 151, 29));
        UpperT_spnbx->setMinimum(5000);
        UpperT_spnbx->setMaximum(10000);
        label_14 = new QLabel(centralwidget);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 60, 151, 20));
        label_15 = new QLabel(centralwidget);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(200, 60, 151, 20));
        Rising_sldr = new QSlider(centralwidget);
        Rising_sldr->setObjectName("Rising_sldr");
        Rising_sldr->setGeometry(QRect(10, 140, 361, 18));
        Rising_sldr->setMinimum(0);
        Rising_sldr->setMaximum(100);
        Rising_sldr->setValue(1);
        Rising_sldr->setOrientation(Qt::Orientation::Horizontal);
        label_16 = new QLabel(centralwidget);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(10, 120, 151, 20));
        falling_sldr = new QSlider(centralwidget);
        falling_sldr->setObjectName("falling_sldr");
        falling_sldr->setGeometry(QRect(10, 180, 361, 18));
        falling_sldr->setMinimum(0);
        falling_sldr->setMaximum(100);
        falling_sldr->setOrientation(Qt::Orientation::Horizontal);
        label_17 = new QLabel(centralwidget);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(10, 160, 151, 20));
        label_18 = new QLabel(centralwidget);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(370, 10, 151, 20));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 522, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        startBt->setText(QCoreApplication::translate("MainWindow", "START", nullptr));
        Screen->setText(QCoreApplication::translate("MainWindow", "SCREEN", nullptr));
        color_combobx->setItemText(0, QCoreApplication::translate("MainWindow", "None", nullptr));
        color_combobx->setItemText(1, QCoreApplication::translate("MainWindow", "Random Color", nullptr));
        color_combobx->setItemText(2, QCoreApplication::translate("MainWindow", "Fixed Color", nullptr));

        label_5->setText(QCoreApplication::translate("MainWindow", "Color Preferences Menu", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Animation Preferences Menu", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "None", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Circles", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Stars", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Squares", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("MainWindow", "SnowFlakes", nullptr));

        zenopix_icon->setText(QCoreApplication::translate("MainWindow", "hppy", nullptr));
        znpx->setText(QCoreApplication::translate("MainWindow", "znpx", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\360\237\214\250\342\235\204\360\235\231\203\360\235\231\226\360\235\231\245\360\235\231\245\360\235\231\256 \360\235\231\211\360\235\231\232\360\235\231\254 \360\235\231\224\360\235\231\232\360\235\231\226\360\235\231\247\342\235\204\360\237\214\250\357\270\217", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "icon", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Lower Radius Limit", nullptr));
        label_12->setText(QString());
        label_13->setText(QCoreApplication::translate("MainWindow", "Upper Radius Limit", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Lower onTime", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Upper onTime", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Rising Speed", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Falling Speed", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Number Of Shapes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
