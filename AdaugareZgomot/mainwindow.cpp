#include "mainwindow.h"
#include "ui_mainwindow.h"

#define CV_BGR2RGB cv::COLOR_BGR2RGB

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label;
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
    poza = imread(fileName.toLatin1().data());
    cvtColor(poza, poza, CV_BGR2RGB);

    QImage img = QImage((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_RGB888);

    ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size(), Qt::IgnoreAspectRatio));
}

//Adaugare zgomot pe imagine
void zgomot(Mat &image, int n){
    for(int k=0;k<n;k++){
        int i=rand()%image.rows;
        int j=rand()%image.cols;

        if(image.channels() == 1){
            image.at<char>(i, j) =255;
        }else{
            if(image.channels() == 3){
                image.at<Vec3b>(i, j)[0] = 255;
                image.at<Vec3b>(i, j)[1] = 255;
                image.at<Vec3b>(i, j)[2] = 255;
            }
        }


    }
}

//Reducerea numarului de culori
void reducereCulori(Mat &image, int div){
    //nr de linii
    int nl = image.rows;

    //nr total de elemene pe linie
    int nc = image.cols * image.channels();
    for(int j=0; j<nl;j ++){
        uchar* data = image.ptr<uchar>(j);
        for(int i = 0; i < nc; i++)
            data[i] = (data[i]/div) * div + div/2;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QImage img = QImage((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_RGB888);

    zgomot(poza, 500);

    ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size(), Qt::IgnoreAspectRatio));

}

void MainWindow::on_pushButton_3_clicked()
{
    QImage img = QImage((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_RGB888);

    reducereCulori(poza, 50);

    ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size(), Qt::IgnoreAspectRatio));


}

void MainWindow::on_pushButton_4_clicked()
{
    Mat poza1 = imread("D:/images2.jpg");

    addWeighted(poza,1.0,poza1,0.3,0.,poza);

    QImage img = QImage((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_RGB888);


    ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size(), Qt::IgnoreAspectRatio));


}
