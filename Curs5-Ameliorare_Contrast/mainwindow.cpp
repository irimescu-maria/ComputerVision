#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "histograma.h"

/*
5. Realizati un program cu GUI care sa permita
utilizatorului sa incarce o imagine si sa ii amelioreze
contrastul prin diferite metode care sa poata fi
selectate de catre utilizator:
o Strangerea imaginii cu un parametru ce poate fi stabilit
o Egalizarea imaginii

*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_Initial_Image;
    ui->label_Image_Strange;
    ui->label_Image_Egalizer;

    ui->pushButton_Strange->setEnabled(false);
    ui->pushButton_Egalizer->setEnabled(false);

    ui->pushButton_Load_Image->setStyleSheet("color: white;"
                                            "background-color: orange;"
                                            "border-radius: 5px;");

    ui->pushButton_Strange->setStyleSheet("color: white;"
                                          "background-color: green;"
                                          "border-radius: 5px;");

    ui->pushButton_Egalizer->setStyleSheet("color: white;"
                                           "background-color: violet;"
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
                                                    tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));

    poza = imread(fileName.toLatin1().data(), 0);

   // cvtColor(poza, poza, CV_BGR2GRAY);
    if(poza.data){
         ui->pushButton_Egalizer->setEnabled(true);
           ui->pushButton_Strange->setEnabled(true);
}
    QImage img = QImage((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_Indexed8);

      //trimitem poza catre label-ul
     ui->label_Initial_Image->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Initial_Image->size(), Qt::IgnoreAspectRatio));
}

void MainWindow::on_pushButton_Strange_clicked()
{
    Histogram1D h;
    Mat stransa = h.strange(poza, 100);

    QImage img = QImage((uchar*) stransa.data, stransa.cols, stransa.rows, stransa.step, QImage::Format_Indexed8);
    ui->label_Image_Strange->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Image_Strange->size(), Qt::IgnoreAspectRatio));

}

void MainWindow::on_pushButton_Egalizer_clicked()
{
    Histogram1D h;

    Mat pozaEgalizare = h.equalize(poza);

    QImage img = QImage((uchar*) pozaEgalizare.data, pozaEgalizare.cols, pozaEgalizare.rows, pozaEgalizare.step, QImage::Format_Indexed8);
    ui->label_Image_Egalizer->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Image_Egalizer->size(), Qt::IgnoreAspectRatio));

}
