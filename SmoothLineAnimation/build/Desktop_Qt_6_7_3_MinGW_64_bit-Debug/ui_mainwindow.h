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
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *Screen;
    QPushButton *startBt;
    QRadioButton *standart_bttn;
    QRadioButton *Random_bttn;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *zenopix_icon;
    QLabel *percent;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_3;
    QSlider *Delta_sldr;
    QLabel *offst_prc;
    QSlider *speed_sldr;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(418, 618);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(57, 80, 103);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        Screen = new QLabel(centralwidget);
        Screen->setObjectName("Screen");
        Screen->setGeometry(QRect(10, 230, 390, 280));
        Screen->setStyleSheet(QString::fromUtf8("background-color: rgb(0,0,0);"));
        startBt = new QPushButton(centralwidget);
        startBt->setObjectName("startBt");
        startBt->setGeometry(QRect(170, 530, 51, 41));
        standart_bttn = new QRadioButton(centralwidget);
        standart_bttn->setObjectName("standart_bttn");
        standart_bttn->setGeometry(QRect(10, 40, 112, 26));
        Random_bttn = new QRadioButton(centralwidget);
        Random_bttn->setObjectName("Random_bttn");
        Random_bttn->setGeometry(QRect(10, 70, 112, 26));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 10, 111, 20));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 110, 111, 20));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 160, 121, 20));
        zenopix_icon = new QLabel(centralwidget);
        zenopix_icon->setObjectName("zenopix_icon");
        zenopix_icon->setGeometry(QRect(360, 0, 41, 41));
        percent = new QLabel(centralwidget);
        percent->setObjectName("percent");
        percent->setGeometry(QRect(350, 130, 41, 21));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(140, 0, 171, 111));
        gridLayout_3 = new QGridLayout(gridLayoutWidget);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        Delta_sldr = new QSlider(centralwidget);
        Delta_sldr->setObjectName("Delta_sldr");
        Delta_sldr->setGeometry(QRect(10, 180, 331, 31));
        Delta_sldr->setMinimum(20);
        Delta_sldr->setMaximum(100);
        Delta_sldr->setValue(20);
        Delta_sldr->setOrientation(Qt::Orientation::Horizontal);
        offst_prc = new QLabel(centralwidget);
        offst_prc->setObjectName("offst_prc");
        offst_prc->setGeometry(QRect(350, 180, 41, 21));
        speed_sldr = new QSlider(centralwidget);
        speed_sldr->setObjectName("speed_sldr");
        speed_sldr->setGeometry(QRect(10, 130, 331, 31));
        speed_sldr->setMinimum(1);
        speed_sldr->setMaximum(100);
        speed_sldr->setValue(1);
        speed_sldr->setOrientation(Qt::Orientation::Horizontal);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 418, 21));
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
        Screen->setText(QCoreApplication::translate("MainWindow", "SCREEN", nullptr));
        startBt->setText(QString());
        standart_bttn->setText(QCoreApplication::translate("MainWindow", "Standart Color", nullptr));
        Random_bttn->setText(QCoreApplication::translate("MainWindow", "Random Color", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Color Preference", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Speed Preference", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Offset Amount", nullptr));
        zenopix_icon->setText(QCoreApplication::translate("MainWindow", "zeno_ic", nullptr));
        percent->setText(QCoreApplication::translate("MainWindow", "%", nullptr));
        offst_prc->setText(QCoreApplication::translate("MainWindow", "%", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
