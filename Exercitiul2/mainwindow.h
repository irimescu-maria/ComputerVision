#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<QFileDialog>
#include<QtGui>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

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
    void on_pushButton_Open_clicked();

private:
    Ui::MainWindow *ui;

    Mat poza;
};

#endif // MAINWINDOW_H
