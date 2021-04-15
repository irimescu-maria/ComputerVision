/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
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
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_Load;
    QLabel *label_Thresholding_Binary;
    QLabel *label_Initial_Image;
    QLabel *label_Thresholding_Bin_Inv;
    QLabel *label_Thresholding_Trunc;
    QLabel *label_Thresholding_Tozero;
    QLabel *label_Thresholding_Tozero_Inv;
    QRadioButton *radioButton_Thresh_Binary;
    QRadioButton *radioButton_Thresh_Bin_Inv;
    QRadioButton *radioButton_Thresh_Trunc;
    QRadioButton *radioButton_Thresh_Tozero;
    QRadioButton *radioButton_Thresh_Tozero_Inv;
    QSlider *verticalSlider;
    QSlider *verticalSlider_2;
    QLabel *label_Slider1;
    QLabel *label_Slider2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(963, 704);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_Load = new QPushButton(centralWidget);
        pushButton_Load->setObjectName(QStringLiteral("pushButton_Load"));
        pushButton_Load->setGeometry(QRect(10, 0, 75, 23));
        label_Thresholding_Binary = new QLabel(centralWidget);
        label_Thresholding_Binary->setObjectName(QStringLiteral("label_Thresholding_Binary"));
        label_Thresholding_Binary->setGeometry(QRect(440, 40, 201, 201));
        label_Initial_Image = new QLabel(centralWidget);
        label_Initial_Image->setObjectName(QStringLiteral("label_Initial_Image"));
        label_Initial_Image->setGeometry(QRect(230, 40, 201, 201));
        label_Thresholding_Bin_Inv = new QLabel(centralWidget);
        label_Thresholding_Bin_Inv->setObjectName(QStringLiteral("label_Thresholding_Bin_Inv"));
        label_Thresholding_Bin_Inv->setGeometry(QRect(670, 40, 201, 201));
        label_Thresholding_Trunc = new QLabel(centralWidget);
        label_Thresholding_Trunc->setObjectName(QStringLiteral("label_Thresholding_Trunc"));
        label_Thresholding_Trunc->setGeometry(QRect(230, 300, 201, 201));
        label_Thresholding_Tozero = new QLabel(centralWidget);
        label_Thresholding_Tozero->setObjectName(QStringLiteral("label_Thresholding_Tozero"));
        label_Thresholding_Tozero->setGeometry(QRect(440, 300, 201, 201));
        label_Thresholding_Tozero_Inv = new QLabel(centralWidget);
        label_Thresholding_Tozero_Inv->setObjectName(QStringLiteral("label_Thresholding_Tozero_Inv"));
        label_Thresholding_Tozero_Inv->setGeometry(QRect(700, 300, 201, 201));
        radioButton_Thresh_Binary = new QRadioButton(centralWidget);
        radioButton_Thresh_Binary->setObjectName(QStringLiteral("radioButton_Thresh_Binary"));
        radioButton_Thresh_Binary->setGeometry(QRect(490, 10, 101, 17));
        radioButton_Thresh_Bin_Inv = new QRadioButton(centralWidget);
        radioButton_Thresh_Bin_Inv->setObjectName(QStringLiteral("radioButton_Thresh_Bin_Inv"));
        radioButton_Thresh_Bin_Inv->setGeometry(QRect(740, 10, 131, 17));
        radioButton_Thresh_Trunc = new QRadioButton(centralWidget);
        radioButton_Thresh_Trunc->setObjectName(QStringLiteral("radioButton_Thresh_Trunc"));
        radioButton_Thresh_Trunc->setGeometry(QRect(250, 270, 91, 17));
        radioButton_Thresh_Tozero = new QRadioButton(centralWidget);
        radioButton_Thresh_Tozero->setObjectName(QStringLiteral("radioButton_Thresh_Tozero"));
        radioButton_Thresh_Tozero->setGeometry(QRect(490, 270, 111, 17));
        radioButton_Thresh_Tozero_Inv = new QRadioButton(centralWidget);
        radioButton_Thresh_Tozero_Inv->setObjectName(QStringLiteral("radioButton_Thresh_Tozero_Inv"));
        radioButton_Thresh_Tozero_Inv->setGeometry(QRect(750, 270, 131, 17));
        verticalSlider = new QSlider(centralWidget);
        verticalSlider->setObjectName(QStringLiteral("verticalSlider"));
        verticalSlider->setGeometry(QRect(10, 40, 22, 160));
        verticalSlider->setOrientation(Qt::Vertical);
        verticalSlider_2 = new QSlider(centralWidget);
        verticalSlider_2->setObjectName(QStringLiteral("verticalSlider_2"));
        verticalSlider_2->setGeometry(QRect(90, 40, 22, 160));
        verticalSlider_2->setMaximum(255);
        verticalSlider_2->setOrientation(Qt::Vertical);
        label_Slider1 = new QLabel(centralWidget);
        label_Slider1->setObjectName(QStringLiteral("label_Slider1"));
        label_Slider1->setGeometry(QRect(10, 220, 47, 13));
        label_Slider2 = new QLabel(centralWidget);
        label_Slider2->setObjectName(QStringLiteral("label_Slider2"));
        label_Slider2->setGeometry(QRect(80, 220, 47, 13));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 963, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_Load->setText(QApplication::translate("MainWindow", "Load Image", nullptr));
        label_Thresholding_Binary->setText(QString());
        label_Initial_Image->setText(QString());
        label_Thresholding_Bin_Inv->setText(QString());
        label_Thresholding_Trunc->setText(QString());
        label_Thresholding_Tozero->setText(QString());
        label_Thresholding_Tozero_Inv->setText(QString());
        radioButton_Thresh_Binary->setText(QApplication::translate("MainWindow", "Threshold Binary", nullptr));
        radioButton_Thresh_Bin_Inv->setText(QApplication::translate("MainWindow", "Threshold Binary Inv", nullptr));
        radioButton_Thresh_Trunc->setText(QApplication::translate("MainWindow", "Threshold Trunc", nullptr));
        radioButton_Thresh_Tozero->setText(QApplication::translate("MainWindow", "Threshold ToZero", nullptr));
        radioButton_Thresh_Tozero_Inv->setText(QApplication::translate("MainWindow", "Threshold ToZero Inv", nullptr));
        label_Slider1->setText(QString());
        label_Slider2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
