#include "mainwindow.h"
#include "ui_mainwindow.h"

#define CV_BGR2RGB cv::COLOR_BGR2RGB

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_Image1;
    ui->label_Image2;
    ui->label_Image3;
    ui->horizontalSlider_Image1->setRange(0,10);
    ui->horizontalSlider_Image2->setRange(0,10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open image"),
                                                        ".",
                                                        tr("Image Files (*.png *.jpg *.jpeg *. bmp)"));
    poza1 = imread(fileName.toLatin1().data());
    cvtColor(poza1, poza1, CV_BGR2RGB);

    QImage img = QImage((uchar*) poza1.data, poza1.cols, poza1.rows, poza1.step, QImage::Format_RGB888);

    ui->label_Image1->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Image1->size(), Qt::IgnoreAspectRatio));
}

void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open image"),
                                                        ".",
                                                        tr("Image Files (*.png *.jpg *.jpeg *. bmp)"));
    poza2 = imread(fileName.toLatin1().data());
    cvtColor(poza2, poza2, CV_BGR2RGB);

    QImage img = QImage((uchar*) poza2.data, poza2.cols, poza2.rows, poza2.step, QImage::Format_RGB888);

    ui->label_Image2->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Image2->size(), Qt::IgnoreAspectRatio));
}

void MainWindow::on_horizontalSlider_Image1_valueChanged(int value)
{
    //cdt retine valoarea de la slider
//    QString cdt("Reducere \n nr. culori:");
//    cdt.append(QString::number(value));

    x = ((float) value)/10;
    Mat pozaCopie;
    poza1.copyTo(pozaCopie);
    QImage img = QImage((uchar*) pozaCopie.data, poza1.cols, poza1.rows, poza1.step, QImage::Format_RGB888);


    //reducereCulori(pozaCopie, value);
    addWeighted(poza1, x, poza2,y,0.,pozaCopie);
    ui->label_Image3->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Image3->size(), Qt::IgnoreAspectRatio));
}

void MainWindow::on_horizontalSlider_Image2_valueChanged(int value)
{

    y = ((float)value)/10;

    Mat pozaCopie;
    poza1.copyTo(pozaCopie);
    QImage img = QImage((uchar*) pozaCopie.data, poza2.cols, poza2.rows, poza2.step, QImage::Format_RGB888);


    //reducereCulori(pozaCopie, value);
    addWeighted(poza1, x, poza2,y,0.,pozaCopie);
    ui->label_Image3->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Image3->size(), Qt::IgnoreAspectRatio));
}
