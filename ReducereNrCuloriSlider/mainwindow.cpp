#include "mainwindow.h"
#include "ui_mainwindow.h"

#define CV_BGR2RGB cv::COLOR_BGR2RGB
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label;
    ui->label_ROI;

    ui->pushButton->setStyleSheet("color: white;"
                                       "background-color: #f48c42;"
                                       "border-radius: 5px;");

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


void MainWindow::on_verticalSlider_valueChanged(int value)
{
    //cdt retine valoarea de la slider
    QString cdt("Reducere \n nr. culori:");
    cdt.append(QString::number(value));


    this->ui->label_ROI->setText(cdt);
    Mat pozaCopie;
    poza.copyTo(pozaCopie);
    QImage img = QImage((uchar*) pozaCopie.data, poza.cols, poza.rows, poza.step, QImage::Format_RGB888);


    reducereCulori(pozaCopie, value);

    ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size(), Qt::IgnoreAspectRatio));

}
