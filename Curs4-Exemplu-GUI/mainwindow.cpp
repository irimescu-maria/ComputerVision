#include "mainwindow.h"
#include "ui_mainwindow.h"

#define CV_BGR2RGB cv::COLOR_BGR2RGB
#define CV_RGB2BGR cv::COLOR_RGB2BGR

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_Image;

    ui->pushButton_Load->setStyleSheet("color: white;"
                                       "background-color: #f48c42;"
                                       "border-radius: 5px;");
    ui->pushButton_Process->setStyleSheet("color: white;"
                                          "background-color: orange;"
                                          "border-radius: 5px;"
                                          );
    ui->pushButton_Save->setStyleSheet("color: white;"
                                       "background-color: green;"
                                       "border-radius: 5px;");

    ui->pushButton_Select_Color->setStyleSheet("color: white;"
                                               "background-color: blue;"
                                               "border-radius: 5px;");

    ui->pushButton_Save->setEnabled(false);
    ui->pushButton_Process->setEnabled(false);
    ui->pushButton_Select_Color;

    pozaFormatQT = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Load_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Select Image"),
                                                        ".",
                                                    tr("Image Files(*.jpg *.png *.jpeg *.bmp)"));
    poza = imread(fileName.toLatin1().data());

    //activez butonul de procesare a imaginii
    ui->pushButton_Process->setEnabled(true);

    cvtColor(poza, poza, CV_BGR2RGB);
    pozaFormatQT = true;

    QImage img = QImage((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_RGB888);

    //trimitem poza catre label-ul
    ui->label_Image->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Image->size(), Qt::IgnoreAspectRatio));



}

void MainWindow::on_pushButton_Select_Color_clicked()
{
    QColor color = QColorDialog::getColor(Qt::blue, this);

    //culoarea este setata ca si tinta in cDetect
    if(color.isValid())
        cDetect.setTargetColor(color.red(), color.green(), color.blue());
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    QString cdt("Distanta \nprag culori: ");
    cdt.append(QString::number(value));

    //Stringul este trimis prin eticheta de sub slider
    this->ui->label_Prag->setText(cdt);

    cDetect.setColorDistanceThreshold(value);
}

void MainWindow::on_pushButton_Process_clicked()
{
    if(pozaFormatQT){
        cvtColor(poza, poza, CV_RGB2BGR);
        pozaFormatQT = false;
    }

    //procesez poza si rezultatul este pus in rez
    rez = cDetect.process(poza);

    //rez este alb-negru
    QImage img = QImage((uchar*) rez.data, rez.cols, rez.rows, rez.step, QImage::Format_Indexed8);
    ui->label_Image->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Image->size(), Qt::IgnoreAspectRatio));

    //activam butonul de salvare
    if(!ui->pushButton_Save->isEnabled()){
        ui->pushButton_Save->setEnabled(true);
    }
}

void MainWindow::on_pushButton_Save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Salvare Fisier"),
                                                    ".",
                                                    tr("Imagini(*.png *.bmp *.jpg"));
    QFile f(fileName);
    f.open(QIODevice::WriteOnly);

    QImage img = QImage((uchar*) rez.data, rez.cols,
                        rez.rows, rez.step, QImage::Format_Indexed8);
    QPixmap::fromImage(img).save(&f, "PNG");
}
