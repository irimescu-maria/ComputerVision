#include "mainwindow.h"
#include "ui_mainwindow.h"
#define CV_BGR2RGB cv::COLOR_BGR2RGB
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_Image;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Open_clicked()
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

       ui->label_Image->setPixmap(QPixmap::fromImage(img));
        ui->label_Image->resize(ui->label_Image->pixmap()->size());
     //   ui->label_Image->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Image->size(), Qt::IgnoreAspectRatio));
}
