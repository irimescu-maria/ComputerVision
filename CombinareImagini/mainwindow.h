#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtGui>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<QFileDialog>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_horizontalSlider_Image1_valueChanged(int value);

    void on_horizontalSlider_Image2_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    Mat poza1;

    Mat poza2;
    float x=0,y=0;
};

#endif // MAINWINDOW_H
