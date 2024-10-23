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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QSpinBox *spinBox;
    QPushButton *pushButton;
    QLabel *Screen;
    QRadioButton *radioButton;
    QSlider *horizontalSlider_4;
    QLabel *label_6;
    QLabel *label_7;
    QRadioButton *radioButton_2;
    QSpinBox *spinBox_2;
    QLabel *label_2;
    QSpinBox *spinBox_3;
    QLabel *label_8;
    QLabel *labelray;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QSlider *horizontalSlider;
    QSlider *horizontalSlider_2;
    QSlider *horizontalSlider_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(853, 552);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(57,80,103);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        spinBox = new QSpinBox(centralwidget);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(10, 50, 91, 22));
        spinBox->setMinimum(1);
        spinBox->setMaximum(60);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(130, 450, 101, 31));
        Screen = new QLabel(centralwidget);
        Screen->setObjectName("Screen");
        Screen->setGeometry(QRect(10, 170, 371, 221));
        radioButton = new QRadioButton(centralwidget);
        radioButton->setObjectName("radioButton");
        radioButton->setGeometry(QRect(270, 10, 111, 18));
        horizontalSlider_4 = new QSlider(centralwidget);
        horizontalSlider_4->setObjectName("horizontalSlider_4");
        horizontalSlider_4->setGeometry(QRect(10, 100, 281, 21));
        horizontalSlider_4->setMinimum(1);
        horizontalSlider_4->setMaximum(100);
        horizontalSlider_4->setValue(1);
        horizontalSlider_4->setOrientation(Qt::Orientation::Horizontal);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(300, 100, 81, 16));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(300, -10, 201, 20));
        radioButton_2 = new QRadioButton(centralwidget);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setGeometry(QRect(400, 10, 111, 18));
        spinBox_2 = new QSpinBox(centralwidget);
        spinBox_2->setObjectName("spinBox_2");
        spinBox_2->setGeometry(QRect(110, 50, 91, 22));
        spinBox_2->setMinimum(1);
        spinBox_2->setMaximum(40);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(110, 30, 91, 16));
        spinBox_3 = new QSpinBox(centralwidget);
        spinBox_3->setObjectName("spinBox_3");
        spinBox_3->setGeometry(QRect(210, 50, 91, 22));
        spinBox_3->setMinimum(1);
        spinBox_3->setMaximum(50);
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(210, 30, 91, 16));
        labelray = new QLabel(centralwidget);
        labelray->setObjectName("labelray");
        labelray->setGeometry(QRect(10, 30, 81, 16));
        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName("gridLayoutWidget_2");
        gridLayoutWidget_2->setGeometry(QRect(460, 240, 311, 251));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(460, 60, 361, 161));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setGeometry(QRect(10, 130, 369, 15));
        horizontalSlider->setMaximum(255);
        horizontalSlider->setValue(255);
        horizontalSlider->setOrientation(Qt::Orientation::Horizontal);
        horizontalSlider_2 = new QSlider(centralwidget);
        horizontalSlider_2->setObjectName("horizontalSlider_2");
        horizontalSlider_2->setGeometry(QRect(10, 140, 369, 15));
        horizontalSlider_2->setMaximum(255);
        horizontalSlider_2->setValue(255);
        horizontalSlider_2->setOrientation(Qt::Orientation::Horizontal);
        horizontalSlider_3 = new QSlider(centralwidget);
        horizontalSlider_3->setObjectName("horizontalSlider_3");
        horizontalSlider_3->setGeometry(QRect(460, 30, 369, 15));
        horizontalSlider_3->setMaximum(255);
        horizontalSlider_3->setValue(255);
        horizontalSlider_3->setOrientation(Qt::Orientation::Horizontal);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 853, 21));
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
        pushButton->setText(QCoreApplication::translate("MainWindow", "START", nullptr));
        Screen->setText(QCoreApplication::translate("MainWindow", "SCREEN", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "RANDOM RENK", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "SPEED", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "                 RENK TERC\304\260H\304\260", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "SAB\304\260T RENK", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Ray Tickness", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Ray bore", nullptr));
        labelray->setText(QCoreApplication::translate("MainWindow", "Ray Number", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
