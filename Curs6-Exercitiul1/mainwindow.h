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

    void on_pushButton_Erodare_clicked();

    void on_pushButton_Threshold_clicked();

    void on_pushButton_Dilatare_clicked();

    void on_radioButton_Cruce_clicked();

    void on_radioButton_Romb_clicked();

    void on_radioButton_Patrat_clicked();

    void on_radioButton_X_clicked();

    void on_verticalSlider_valueChanged(int value);

    void on_verticalSlider_sliderReleased();

private:
    Ui::MainWindow *ui;
    Mat poza;
    Mat pozaThreshold;

    int val;

    Mat cruce;
    Mat romb;
    Mat patrat;
    Mat x;

    int valueElem;
};

#endif // MAINWINDOW_H
