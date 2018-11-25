#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QFileDialog>
#include <QColorDialog>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "colordetector.h"

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
    void on_pushButton_Load_clicked();

    void on_pushButton_Select_Color_clicked();

    void on_verticalSlider_valueChanged(int value);

    void on_pushButton_Process_clicked();

    void on_pushButton_Save_clicked();

private:
    Ui::MainWindow *ui;

    Mat poza;
    Mat rez;
        ColorDetector cDetect;
    bool pozaFormatQT;
};

#endif // MAINWINDOW_H
