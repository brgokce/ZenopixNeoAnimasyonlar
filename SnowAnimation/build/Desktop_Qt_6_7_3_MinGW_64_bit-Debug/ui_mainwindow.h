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
    QSpinBox *snowflake_spinbx;
    QLabel *label;
    QLabel *Screen;
    QSlider *Speed_sldr;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *extent_snowflake_spnbx;
    QLabel *label_4;
    QComboBox *color_combobx;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QSlider *brightness_sldr;
    QLabel *label_9;
    QComboBox *comboBox;
    QSlider *brightness_sldr_2;
    QLabel *label_8;
    QLabel *label_10;
    QLabel *zenopix_icon;
    QLabel *znpx;
    QLabel *label_11;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(506, 700);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        startBt = new QPushButton(centralwidget);
        startBt->setObjectName("startBt");
        startBt->setGeometry(QRect(200, 610, 83, 41));
        snowflake_spinbx = new QSpinBox(centralwidget);
        snowflake_spinbx->setObjectName("snowflake_spinbx");
        snowflake_spinbx->setGeometry(QRect(10, 40, 131, 29));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 131, 20));
        Screen = new QLabel(centralwidget);
        Screen->setObjectName("Screen");
        Screen->setGeometry(QRect(20, 300, 461, 291));
        Screen->setStyleSheet(QString::fromUtf8(""));
        Speed_sldr = new QSlider(centralwidget);
        Speed_sldr->setObjectName("Speed_sldr");
        Speed_sldr->setGeometry(QRect(20, 160, 441, 41));
        Speed_sldr->setMinimum(1);
        Speed_sldr->setMaximum(100);
        Speed_sldr->setOrientation(Qt::Orientation::Horizontal);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(470, 170, 31, 20));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 150, 121, 20));
        extent_snowflake_spnbx = new QSpinBox(centralwidget);
        extent_snowflake_spnbx->setObjectName("extent_snowflake_spnbx");
        extent_snowflake_spnbx->setGeometry(QRect(180, 40, 141, 29));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(180, 10, 141, 20));
        color_combobx = new QComboBox(centralwidget);
        color_combobx->addItem(QString());
        color_combobx->addItem(QString());
        color_combobx->setObjectName("color_combobx");
        color_combobx->setGeometry(QRect(180, 110, 141, 28));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(180, 80, 141, 20));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 200, 121, 20));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(470, 220, 31, 20));
        brightness_sldr = new QSlider(centralwidget);
        brightness_sldr->setObjectName("brightness_sldr");
        brightness_sldr->setGeometry(QRect(20, 210, 441, 41));
        brightness_sldr->setMaximum(255);
        brightness_sldr->setOrientation(Qt::Orientation::Horizontal);
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 80, 161, 20));
        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(10, 110, 151, 28));
        brightness_sldr_2 = new QSlider(centralwidget);
        brightness_sldr_2->setObjectName("brightness_sldr_2");
        brightness_sldr_2->setGeometry(QRect(20, 260, 441, 41));
        brightness_sldr_2->setMaximum(255);
        brightness_sldr_2->setOrientation(Qt::Orientation::Horizontal);
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(20, 250, 121, 20));
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(470, 270, 31, 20));
        zenopix_icon = new QLabel(centralwidget);
        zenopix_icon->setObjectName("zenopix_icon");
        zenopix_icon->setGeometry(QRect(360, 30, 111, 91));
        znpx = new QLabel(centralwidget);
        znpx->setObjectName("znpx");
        znpx->setGeometry(QRect(464, 5, 41, 31));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(340, 120, 161, 20));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 506, 21));
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
        label->setText(QCoreApplication::translate("MainWindow", "Number of Snowflake", nullptr));
        Screen->setText(QCoreApplication::translate("MainWindow", "SCREEN", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "%", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Animation Speed", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Diameter  of Snowflake", nullptr));
        color_combobx->setItemText(0, QCoreApplication::translate("MainWindow", "Random Color", nullptr));
        color_combobx->setItemText(1, QCoreApplication::translate("MainWindow", "Steady Color", nullptr));

        label_5->setText(QCoreApplication::translate("MainWindow", "Color Preferences Menu", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Snowflake Brightness", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "%", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Animation Preferences Menu", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Circles", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Stars", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Squares", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "SnowFlakes", nullptr));

        label_8->setText(QCoreApplication::translate("MainWindow", "Twinkle Speed", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "%", nullptr));
        zenopix_icon->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        znpx->setText(QCoreApplication::translate("MainWindow", "znpx", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\360\237\214\250\342\235\204\360\235\231\203\360\235\231\226\360\235\231\245\360\235\231\245\360\235\231\256 \360\235\231\211\360\235\231\232\360\235\231\254 \360\235\231\224\360\235\231\232\360\235\231\226\360\235\231\247\342\235\204\360\237\214\250\357\270\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
