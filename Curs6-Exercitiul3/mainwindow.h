#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QFileDialog>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_LoadImage_clicked();

    void on_radioButton_Threshold_Binary_clicked();

    void on_radioButton_Threshold_Binary_Inv_clicked();



    void on_verticalSlider_valueChanged(int value);

    void on_verticalSlider_sliderReleased();

private:
    Ui::MainWindow *ui;
    Mat pozaThreshold_Binary, pozaThreshold_Binary_Inv;
    Mat poza;
    Mat cruce;
    int val;

    Mat binara;

    int valueSlider;
};

#endif // MAINWINDOW_H
