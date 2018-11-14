#include "mainwindow.h"
#include "ui_mainwindow.h"

#define CV_BGR2RGB cv::COLOR_BGR2RGB

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_Initial_Img;
    ui->label_Img_Orizontally;

    ui->pushButton_Orizontally->setEnabled(false);
    ui->pushButton_Vertically->setEnabled(false);
    ui->pushButton_Both->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openImg_clicked()
{
    QString fileName = QFileDialog::
            getOpenFileName(this, tr("Open image"),
                            ".", tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));
    poza = imread(fileName.toLatin1().data());

    if(poza.data){
        ui->pushButton_Orizontally->setEnabled(true);
        ui->pushButton_Vertically->setEnabled(true);
        ui->pushButton_Both->setEnabled(true);
    }
    cvtColor(poza, poza, CV_BGR2RGB);

    QImage img = QImage((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_RGB888);

    ui->label_Initial_Img->setPixmap(QPixmap::fromImage(img));
    ui->label_Initial_Img->resize(ui->label_Initial_Img->pixmap()->size());
    ui->label_Initial_Img->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Initial_Img->size(), Qt::IgnoreAspectRatio));
}

void MainWindow::on_pushButton_Orizontally_clicked()
{
    //Oglindire orizonala
    flip(poza, poza, 1);

    QImage img = QImage((uchar*) poza.data, poza.cols,
                        poza.rows, poza.step,
                        QImage::Format_RGB888);

  //  ui->label_Img_Orizontally->setPixmap(QPixmap::fromImage(img));
    ui->label_Img_Orizontally->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Img_Orizontally->size(), Qt::IgnoreAspectRatio));

}

void MainWindow::on_pushButton_Vertically_clicked()
{
    //Oglindire verticala
    flip(poza, poza, 0);

    QImage img = QImage((uchar*) poza.data, poza.cols,
                        poza.rows, poza.step,
                        QImage::Format_RGB888);

    ui->label_Img_Vertically->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Img_Vertically->size(), Qt::IgnoreAspectRatio));

}

void MainWindow::on_pushButton_Both_clicked()
{
    //Oglindire atat verticala cat si orizontala
    flip(poza, poza, -1);

    QImage img = QImage((uchar*) poza.data, poza.cols,
                        poza.rows, poza.step,
                        QImage::Format_RGB888);

   // ui->label_Both->setPixmap(QPixmap::fromImage(img));
    ui->label_Both->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Both->size(), Qt::IgnoreAspectRatio));

}

void MainWindow::on_pushButton_Save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
           tr("Save Image"), "",
          tr("JPEG (*.jpg *.jpeg);;PNG (*.png)"));

    imageObject = new QImage((uchar*) poza.data, poza.cols,
                        poza.rows, poza.step,
                        QImage::Format_RGB888);

    imageObject->save(fileName);

}
