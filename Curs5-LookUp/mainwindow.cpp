#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "histograma.h"

/*
    Realizati un program cu interfata grafica in
care sa se introduca o imagine si pentru aceasta
sa se aplice un tablou lookup pentru a o modifica.
Fereastra afiseaza ambele imagini.
*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_Image_LookUp;
    ui->label_Initial_Image;

    ui->pushButton_Process_Image->setEnabled(false);

    ui->pushButton_Load_Image->setStyleSheet("color: white;"
                                             "background-color: orange;"
                                             "border-radius: 5px;");

    ui->pushButton_Process_Image->setStyleSheet("color: white;"
                                                "background-color: green;"
                                                "border-radius: 5px;");
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
                                                    tr("Image Files(*.jpg *.jpeg *.png *.bmp)"));
    poza = imread(fileName.toLatin1().data(), 0);

    if(poza.data)
        ui->pushButton_Process_Image->setEnabled(true);

    QImage img = QImage((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_Indexed8);

    ui->label_Initial_Image->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Initial_Image->size(), Qt::IgnoreAspectRatio));
}

void MainWindow::on_pushButton_Process_Image_clicked()
{
    Histogram1D h;
    Mat lut(1, //1 dimensiune
            256, // 256 de valori
            CV_8U);

    for(int i = 0; i<256; i++)
        lut.at<uchar>(i) = 255 - i;

    Mat pozaNoua = h.applyLookUp(poza, lut);

    QImage img = QImage((uchar*) pozaNoua.data, pozaNoua.cols, pozaNoua.rows, pozaNoua.step, QImage::Format_Indexed8);

    ui->label_Image_LookUp->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Image_LookUp->size(), Qt::IgnoreAspectRatio));

}
