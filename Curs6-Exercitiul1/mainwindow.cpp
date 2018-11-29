#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "caracteristici.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_LoadImage;
    ui->label_Dilatare;
    ui->label_Erodare;
    ui->label_Threshold;
    ui->label_Value_Slider;

    ui->verticalSlider;

    ui->pushButton_LoadImage->setStyleSheet("color: white;"
                                            "background-color: orange;"
                                            "border-radius: 5px;");
    ui->pushButton_Dilatare->setStyleSheet("color: white;"
                                           "background-color: green;"
                                           "border-radius: 5px;");

    ui->pushButton_Erodare->setStyleSheet("color: white;"
                                          "background-color: pink;"
                                          "border-radius: 5px;");
    ui->pushButton_Threshold->setStyleSheet("color: white;"
                                            "background-color: red;"
                                            "border-radius: 5px;");

    ui->pushButton_Erodare->setEnabled(false);
    ui->pushButton_Dilatare->setEnabled(false);
    ui->pushButton_Threshold->setEnabled(false);
}

/*
Faceti un proiect cu GUI care sa permita incarcarea unei imagini si sa se aplice apoi dilatarea si erodarea pentru aceasta. Pentru
acestea sa se poata stabili marimea elementului structural si sa se poata alege din mai multe forme posibile (patrat, romb, cruce, x etc).
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
                                                    tr("Image File(*.jpg *.jpeg *.png *.bmp)"));

    poza = imread(fileName.toLatin1().data(), 0);

    if(poza.data){
        ui->pushButton_Dilatare->setEnabled(true);
        ui->pushButton_Erodare->setEnabled(true);
        ui->pushButton_Threshold->setEnabled(true);
    }

    QImage img = QImage((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_Indexed8);

    ui->label_LoadImage->setPixmap(QPixmap::fromImage(img).scaled(ui->label_LoadImage->size(), Qt::IgnoreAspectRatio));

}

void MainWindow::on_pushButton_Erodare_clicked()
{
    Mat erodata;
    erode(pozaThreshold, erodata, Mat());

    QImage img = QImage((uchar*) erodata.data, erodata.cols, erodata.rows, erodata.step, QImage::Format_Indexed8);

    ui->label_Erodare->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Erodare->size(), Qt::IgnoreAspectRatio));

}

void MainWindow::on_pushButton_Threshold_clicked()
{

    poza.copyTo(pozaThreshold);
    threshold(poza,pozaThreshold, 120, 255, THRESH_BINARY_INV);

    QImage img = QImage((uchar*) pozaThreshold.data, pozaThreshold.cols, pozaThreshold.rows, pozaThreshold.step, QImage::Format_Indexed8);

    ui->label_Threshold->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Threshold->size(), Qt::IgnoreAspectRatio));
}

void MainWindow::on_pushButton_Dilatare_clicked()
{
    Mat dilatata;
    dilate(pozaThreshold, dilatata, Mat());

    QImage img = QImage((uchar*) dilatata.data, dilatata.cols, dilatata.rows, dilatata.step, QImage::Format_Indexed8);

    ui->label_Dilatare->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Dilatare->size(), Qt::IgnoreAspectRatio));
}

void MainWindow::on_radioButton_Cruce_clicked()
{
    val = 0;
}

void MainWindow::on_radioButton_Romb_clicked()
{
    val = 1;
}

void MainWindow::on_radioButton_Patrat_clicked()
{
    val = 2;
}

void MainWindow::on_radioButton_X_clicked()
{
    val = 3;
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    valueElem = value;

    if(valueElem%2 == 0){
        valueElem = valueElem+1;
    }
        QString cdt(" ");
    cdt.append(QString::number(valueElem));

    //Stringul este trimis prin eticheta de sub slider
    this->ui->label_Value_Slider->setText(cdt);

    if(val == 0){ //element structural in forma de cruce

        Mat rez;
        cruce = Mat(valueElem, valueElem, CV_8U, Scalar(0));
        for(int i = 0; i<valueElem; i++){
            cruce.at<uchar>(valueElem/2, i) = 1;
            cruce.at<uchar>(i, valueElem/2) = 1;
        }
        dilate(pozaThreshold, rez, cruce);
        QImage img = QImage((uchar*) rez.data, rez.cols, rez.rows, rez.step, QImage::Format_Indexed8);

        ui->label_Dilatare->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Dilatare->size(), Qt::IgnoreAspectRatio));


        erode(pozaThreshold, rez, cruce);
        QImage img1 = QImage((uchar*) rez.data, rez.cols, rez.rows, rez.step, QImage::Format_Indexed8);

        ui->label_Erodare->setPixmap(QPixmap::fromImage(img1).scaled(ui->label_Erodare->size(), Qt::IgnoreAspectRatio));

    }else if(val == 3){ // element structural in forma de x
        Mat rez;

        x = Mat(valueElem,valueElem, CV_8U, Scalar(0));

        for(int i = 0; i < valueElem; i++){
            x.at<uchar>(i ,i) = 1;
            x.at<uchar>(valueElem-1-i, i) = 1;
        }
        dilate(pozaThreshold, rez, x);
        QImage img = QImage((uchar*) rez.data, rez.cols, rez.rows, rez.step, QImage::Format_Indexed8);

        ui->label_Dilatare->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Dilatare->size(), Qt::IgnoreAspectRatio));

        erode(pozaThreshold, rez, x);
        QImage img1 = QImage((uchar*) rez.data, rez.cols, rez.rows, rez.step, QImage::Format_Indexed8);

        ui->label_Erodare->setPixmap(QPixmap::fromImage(img1).scaled(ui->label_Erodare->size(), Qt::IgnoreAspectRatio));

    }else if(val == 2){ //element structural in forma de patrat
        Mat rez;
        patrat = Mat(valueElem, valueElem, CV_8U, Scalar(1));

        dilate(pozaThreshold, rez, patrat);
        QImage img = QImage((uchar*) rez.data, rez.cols, rez.rows, rez.step, QImage::Format_Indexed8);
        ui->label_Dilatare->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Dilatare->size(), Qt::IgnoreAspectRatio));

        erode(rez, rez, cruce);
        QImage img1 = QImage((uchar*) rez.data, rez.cols, rez.rows, rez.step, QImage::Format_Indexed8);
        ui->label_Erodare->setPixmap(QPixmap::fromImage(img1).scaled(ui->label_Erodare->size(), Qt::IgnoreAspectRatio));

    }else if(val == 1){
        Mat rez;
        romb = Mat(valueElem, valueElem, CV_8U, Scalar(0));

        for(int i = 0; i < valueElem; i++){
            for(int j = 0 ; j< valueElem; j++){
                if(i<j){
                    if(i+j == (valueElem-1)/2){
                        romb.at<uchar>(i,j) = 1;
                    }
                    if(j - i == (valueElem - 1)/2){
                        romb.at<uchar>(i,j) = 1;
                    }
                    if(i+j == (valueElem+((valueElem/2)-1))){
                        romb.at<uchar>(i, j) = 1;
                    }
                }

                if(i>j){
                    if(i+j == (valueElem-1)/2){
                        romb.at<uchar>(i,j) = 1;
                    }
                    if(i - j == (valueElem - 1)/2){
                        romb.at<uchar>(i, j) = 1;
                    }
                    if(i+j == (valueElem+((valueElem/2)-1))){
                        romb.at<uchar>(i, j) = 1;
                    }
                }

                if(i == j){
                    if(i + j == (valueElem - 1)/2){
                        romb.at<uchar>(i, j) = 1;
                    }
                    if(i + j == (valueElem + 1)){
                        romb.at<uchar>(i, j) = 1;
                    }
                }
            }
        }
        dilate(pozaThreshold, rez, romb);
        QImage img = QImage((uchar*) rez.data, rez.cols, rez.rows, rez.step, QImage::Format_Indexed8);
        ui->label_Dilatare->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Dilatare->size(), Qt::IgnoreAspectRatio));

        erode(pozaThreshold, rez, romb);
        QImage img1 = QImage((uchar*) rez.data, rez.cols, rez.rows, rez.step, QImage::Format_Indexed8);
        ui->label_Erodare->setPixmap(QPixmap::fromImage(img1).scaled(ui->label_Erodare->size(), Qt::IgnoreAspectRatio));

    }
}

void MainWindow::on_verticalSlider_sliderReleased()
{

    if(val == 0){ //element structural in forma de cruce
        Mat rez;
        cruce = Mat(valueElem, valueElem, CV_8U, Scalar(0));
        for(int i = 0; i<valueElem; i++){
            cruce.at<uchar>(valueElem/2, i) = 1;
            cruce.at<uchar>(i, valueElem/2) = 1;
        }
        dilate(pozaThreshold, rez, cruce);
        QImage img = QImage((uchar*) rez.data, rez.cols, rez.rows, rez.step, QImage::Format_Indexed8);

        ui->label_Dilatare->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Dilatare->size(), Qt::IgnoreAspectRatio));


        erode(pozaThreshold, rez, cruce);
        QImage img1 = QImage((uchar*) rez.data, rez.cols, rez.rows, rez.step, QImage::Format_Indexed8);

        ui->label_Erodare->setPixmap(QPixmap::fromImage(img1).scaled(ui->label_Erodare->size(), Qt::IgnoreAspectRatio));
    }else if (val == 3) { //element structural in forma de x
        Mat rez;
        x = Mat(valueElem,valueElem, CV_8U, Scalar(0));

        for(int i = 0; i < valueElem; i++){
            x.at<uchar>(i ,i) = 1;
            x.at<uchar>(valueElem-1-i, i) = 1;
        }
        dilate(pozaThreshold, rez, x);
        QImage img = QImage((uchar*) rez.data, rez.cols, rez.rows, rez.step, QImage::Format_Indexed8);

        ui->label_Dilatare->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Dilatare->size(), Qt::IgnoreAspectRatio));

        erode(pozaThreshold, rez, x);
        QImage img1 = QImage((uchar*) rez.data, rez.cols, rez.rows, rez.step, QImage::Format_Indexed8);

        ui->label_Erodare->setPixmap(QPixmap::fromImage(img1).scaled(ui->label_Erodare->size(), Qt::IgnoreAspectRatio));

    }else if(val == 2){ //element structural in forma de patrat
        Mat rez;
        patrat = Mat(valueElem, valueElem, CV_8U, Scalar(1));

        dilate(pozaThreshold, rez, patrat);
        QImage img = QImage((uchar*) rez.data, rez.cols, rez.rows, rez.step, QImage::Format_Indexed8);
        ui->label_Dilatare->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Dilatare->size(), Qt::IgnoreAspectRatio));

        erode(pozaThreshold, rez, cruce);
        QImage img1 = QImage((uchar*) rez.data, rez.cols, rez.rows, rez.step, QImage::Format_Indexed8);
        ui->label_Erodare->setPixmap(QPixmap::fromImage(img1).scaled(ui->label_Erodare->size(), Qt::IgnoreAspectRatio));
    }else if(val == 1){ //element structural in forma de romb
        Mat rez;
        romb = Mat(valueElem, valueElem, CV_8U, Scalar(0));

        for(int i = 0; i < valueElem; i++){
            for(int j = 0 ; j< valueElem; j++){
                if(i<j){
                    if(i+j == (valueElem-1)/2){
                        romb.at<uchar>(i,j) = 1;
                    }
                    if(j - i == (valueElem - 1)/2){
                        romb.at<uchar>(i,j) = 1;
                    }
                    if(i+j == (valueElem+((valueElem/2)-1))){
                        romb.at<uchar>(i, j) = 1;
                    }
                }

                if(i>j){
                    if(i+j == (valueElem-1)/2){
                        romb.at<uchar>(i,j) = 1;
                    }
                    if(i - j == (valueElem - 1)/2){
                        romb.at<uchar>(i, j) = 1;
                    }
                    if(i+j == (valueElem+((valueElem/2)-1))){
                        romb.at<uchar>(i, j) = 1;
                    }
                }

                if(i == j){
                    if(i + j == (valueElem - 1)/2){
                        romb.at<uchar>(i, j) = 1;
                    }
                    if(i + j == (valueElem + 1)){
                        romb.at<uchar>(i, j) = 1;
                    }
                }
            }
        }

        dilate(pozaThreshold, rez, romb);
        QImage img = QImage((uchar*) rez.data, rez.cols, rez.rows, rez.step, QImage::Format_Indexed8);
        ui->label_Dilatare->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Dilatare->size(), Qt::IgnoreAspectRatio));

        erode(pozaThreshold, rez, romb);
        QImage img1 = QImage((uchar*) rez.data, rez.cols, rez.rows, rez.step, QImage::Format_Indexed8);
        ui->label_Erodare->setPixmap(QPixmap::fromImage(img1).scaled(ui->label_Erodare->size(), Qt::IgnoreAspectRatio));
    }
}


