#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "caracteristici.h"

#define CV_BGR2GRAY cv::COLOR_BGR2GRAY
#define CV_BGR2RGB cv::COLOR_BGR2RGB

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_LoadImage;
    ui->label_VerticalSlider;
    ui->label_Corner;
    ui->label_Desenare_Colturi;
    ui->label_DetectareColturi;

    ui->pushButton_LoadImage->setStyleSheet("color: white;"
                                            "background-color: orange;"
                                            "border-radius: 5px;");

    ui->label_DetectareColturi->setStyleSheet("color: white;"
                                              "background-color: red;"
                                              "border-radius: 5px;");

    ui->label_DetectareColturi->setVisible(false);
}

/*
Faceti un proiect cu GUI care sa permita incarcarea unei imagini si sa se detecteze apoi pe imagine colturile. Pentru aceasta sa se poata
stabili de catre utilizator marimea elementului structural.
*/

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_LoadImage_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"),
                                                    ".",
                                                    tr("Imsge Files(*.jpg *.jpeg *.png *.bmp)"));

    poza = imread(fileName.toLatin1().data());
    cvtColor(poza, pozaThreshold, CV_BGR2GRAY);

    if(poza.data){
        ui->label_DetectareColturi->setVisible(true);

    }
    cvtColor(poza, poza, CV_BGR2GRAY);
    QImage img = QImage((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_Indexed8);

    ui->label_LoadImage->setPixmap(QPixmap::fromImage(img).scaled(ui->label_LoadImage->size(), Qt::IgnoreAspectRatio));
}


void MainWindow::on_verticalSlider_valueChanged(int value)
{
    valueSlider = value;

    if(valueSlider%2 == 0){
        valueSlider = valueSlider+1;
    }

    QString cdt(" ");
    cdt.append(QString::number(valueSlider));

    //Stringul este trimis prin eticheta de sub slider
    this->ui->label_VerticalSlider->setText(cdt);

        Mat rez;

        cruce = Mat(valueSlider, valueSlider, CV_8U, Scalar(0));

        romb = Mat(valueSlider, valueSlider, CV_8U, Scalar(1));
        x = Mat(valueSlider, valueSlider, CV_8U, Scalar(0));

        //Element structural in forma de cruce
        for(int i = 0; i<valueSlider; i++){
                 cruce.at<uchar>(valueSlider/2, i) = 1;
                 cruce.at<uchar>(i, valueSlider/2) = 1;
             }

        //Element structural in forma de romb
        for(int i = 0; i < valueSlider; i++){
                   for(int j = 0 ; j< valueSlider; j++){
                       if(i<j){
                           if(i+j == (valueSlider-1)/2){
                               romb.at<uchar>(i,j) = 1;
                           }
                           if(j - i == (valueSlider - 1)/2){
                               romb.at<uchar>(i,j) = 1;
                           }
                           if(i+j == (valueSlider+((valueSlider/2)-1))){
                               romb.at<uchar>(i, j) = 1;
                           }
                       }

                       if(i>j){
                           if(i+j == (valueSlider-1)/2){
                               romb.at<uchar>(i,j) = 1;
                           }
                           if(i - j == (valueSlider - 1)/2){
                               romb.at<uchar>(i, j) = 1;
                           }
                           if(i+j == (valueSlider+((valueSlider/2)-1))){
                               romb.at<uchar>(i, j) = 1;
                           }
                       }

                       if(i == j){
                           if(i + j == (valueSlider - 1)/2){
                               romb.at<uchar>(i, j) = 1;
                           }
                           if(i + j == (valueSlider + 1)){
                               romb.at<uchar>(i, j) = 1;
                           }
                       }
                   }
        }

        //Element structural in forma de patrat
        patrat = Mat(valueSlider, valueSlider, CV_8U, Scalar(1));

        //Element structural in forma de X
        for(int i = 0; i < valueSlider; i++){
                   x.at<uchar>(i ,i) = 1;
                   x.at<uchar>(valueSlider-1-i, i) = 1;
               }
        dilate(pozaThreshold, rez, cruce);
        erode(rez,rez,romb);

        Mat rez2;
        dilate(pozaThreshold, rez2, x);
        erode(rez2, rez2, patrat);

        absdiff(rez2,rez, rez);

        Mat poza1;
        threshold(rez,poza1, 120, 255, THRESH_BINARY_INV);

        QImage img = QImage((uchar*) poza1.data, poza1.cols, poza1.rows, poza1.step, QImage::Format_Indexed8);
        ui->label_Corner->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Corner->size(), Qt::IgnoreAspectRatio));

        Caracteristici morf;


        morf.drawOnImage(poza1, poza);

        QImage imgColturi = QImage((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_Indexed8);
        ui->label_Desenare_Colturi->setPixmap(QPixmap::fromImage(imgColturi).scaled(ui->label_Desenare_Colturi->size(), Qt::IgnoreAspectRatio));

}
