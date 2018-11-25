#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>

#include "histograma.h"

#define CV_BGR2GRAY cv::COLOR_BGR2GRAY

using namespace std;
using namespace cv;

/*
    Realizati un program cu GUI care sa permita
utilizatorului sa incarce o imagine in format
grayscale si sa ii calculeze si afiseze ca imagine
histograma.
*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_Image;
    ui->label_Histogram;

    ui->pushButton_Load_Image->setStyleSheet("color: white;"
                                             "background-color: orange;"
                                             "border-radius: 5px;");

    ui->pushButton_Histogram->setStyleSheet("color: white;"
                                            "background-color: blue;"
                                            "border-radius: 5px;");

    ui->pushButton_Histogram->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Load_Image_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"),
                                                    ".",
                                                    tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));

    poza = imread(fileName.toLatin1().data(), 0);

   // cvtColor(poza, poza, CV_BGR2GRAY);
    if(poza.data)
         ui->pushButton_Histogram->setEnabled(true);

    QImage img = QImage((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_Indexed8);

      //trimitem poza catre label-ul
     ui->label_Image->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Image->size(), Qt::IgnoreAspectRatio));
}

void MainWindow::on_pushButton_Histogram_clicked()
{

    Histogram1D h;
    MatND histro = h.getHistogramImage(poza);

    QImage img = QImage((uchar*) histro.data, histro.cols, histro.rows, histro.step, QImage::Format_Indexed8);

    ui->label_Histogram->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Histogram->size(), Qt::IgnoreAspectRatio));

}
