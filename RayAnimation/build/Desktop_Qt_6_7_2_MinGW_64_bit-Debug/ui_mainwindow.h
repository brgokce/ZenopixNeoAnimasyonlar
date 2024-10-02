/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
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
    QSlider *horizontalSlider;
    QSlider *horizontalSlider_2;
    QSlider *horizontalSlider_3;
    QSlider *horizontalSlider_4;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QRadioButton *radioButton_2;
    QSpinBox *spinBox_2;
    QLabel *label_2;
    QSpinBox *spinBox_3;
    QLabel *label_8;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelray;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(589, 470);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(57,80,103);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        spinBox = new QSpinBox(centralwidget);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(10, 30, 91, 22));
        spinBox->setMinimum(1);
        spinBox->setMaximum(60);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(140, 400, 101, 31));
        Screen = new QLabel(centralwidget);
        Screen->setObjectName("Screen");
        Screen->setGeometry(QRect(10, 170, 371, 221));
        radioButton = new QRadioButton(centralwidget);
        radioButton->setObjectName("radioButton");
        radioButton->setGeometry(QRect(340, 30, 111, 18));
        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setGeometry(QRect(10, 60, 281, 21));
        horizontalSlider->setMaximum(255);
        horizontalSlider->setValue(255);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider_2 = new QSlider(centralwidget);
        horizontalSlider_2->setObjectName("horizontalSlider_2");
        horizontalSlider_2->setGeometry(QRect(10, 90, 281, 21));
        horizontalSlider_2->setMaximum(255);
        horizontalSlider_2->setValue(255);
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        horizontalSlider_3 = new QSlider(centralwidget);
        horizontalSlider_3->setObjectName("horizontalSlider_3");
        horizontalSlider_3->setGeometry(QRect(10, 120, 281, 21));
        horizontalSlider_3->setMaximum(255);
        horizontalSlider_3->setValue(255);
        horizontalSlider_3->setOrientation(Qt::Horizontal);
        horizontalSlider_4 = new QSlider(centralwidget);
        horizontalSlider_4->setObjectName("horizontalSlider_4");
        horizontalSlider_4->setGeometry(QRect(10, 150, 281, 21));
        horizontalSlider_4->setMinimum(1);
        horizontalSlider_4->setMaximum(100);
        horizontalSlider_4->setValue(1);
        horizontalSlider_4->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(300, 60, 81, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(300, 90, 81, 16));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(300, 120, 81, 16));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(300, 150, 81, 16));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(370, 10, 201, 20));
        radioButton_2 = new QRadioButton(centralwidget);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setGeometry(QRect(470, 30, 111, 18));
        spinBox_2 = new QSpinBox(centralwidget);
        spinBox_2->setObjectName("spinBox_2");
        spinBox_2->setGeometry(QRect(110, 30, 91, 22));
        spinBox_2->setMinimum(1);
        spinBox_2->setMaximum(40);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(110, 10, 91, 16));
        spinBox_3 = new QSpinBox(centralwidget);
        spinBox_3->setObjectName("spinBox_3");
        spinBox_3->setGeometry(QRect(210, 30, 91, 22));
        spinBox_3->setMinimum(1);
        spinBox_3->setMaximum(50);
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(210, 10, 91, 16));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(390, 80, 181, 191));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(420, 300, 151, 31));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        labelray = new QLabel(centralwidget);
        labelray->setObjectName("labelray");
        labelray->setGeometry(QRect(10, 10, 81, 16));
        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(420, 340, 151, 31));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget_4 = new QWidget(centralwidget);
        verticalLayoutWidget_4->setObjectName("verticalLayoutWidget_4");
        verticalLayoutWidget_4->setGeometry(QRect(420, 380, 151, 31));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 589, 17));
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
        label_3->setText(QCoreApplication::translate("MainWindow", "R", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "G", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
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
