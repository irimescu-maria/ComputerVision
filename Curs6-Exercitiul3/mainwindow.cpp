#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "watershedsegmenter.h"

#define CV_BGR2GRAY cv::COLOR_BGR2GRAY
#define CV_BGR2RGB cv::COLOR_BGR2RGB
/*
    Faceti un proiect cu GUI care sa permita incarcarea unei imagini si sa se detecteze contururile elementelor din prim plan. Thresholdingul pentru
imaginea initiala trebuie sa se poata selecta de catre utilizator ca fiind binar sau invers binar. Utilizatorul trebuie sa poata stabili si marimea
elementului structural.

*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_LoadImage;

    ui->label_VerticalSlider;
    ui->label_Markers;
    ui->label_Watershed;
    ui->label_Prim_Plan;

    ui->label_Marker;
    ui->label_PrimPlan;
    ui->label_Watersheds;


    ui->pushButton_LoadImage->setStyleSheet("color: white;"
                                            "background-color: #f48c42;"
                                            "border-radius: 5px;");
    ui->label_PrimPlan->setStyleSheet("color: white;"
                                            "background-color: green;"
                                            "border-radius: 5px;");
    ui->label_Marker->setStyleSheet("color: white;"
                                    "background-color: darkslateblue;"
                                    "border-radius: 5px;");

    ui->label_Watersheds->setStyleSheet("color: white;"
                                        "background-color: orange;"
                                        "border-radius: 5px;");

     ui->label_PrimPlan->setVisible(false);
     ui->label_Marker->setVisible(false);
     ui->label_Watersheds->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_LoadImage_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"),
                                                    ".",
                                                    tr("Image Files(*.jpg *.jpeg *.png *.bmp)"));

    poza = imread(fileName.toLatin1().data());
    cvtColor(poza, binara, CV_BGR2GRAY);

    cvtColor(poza,poza, CV_BGR2RGB);
    QImage img = QImage((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_RGB888);
    ui->label_LoadImage->setPixmap(QPixmap::fromImage(img).scaled(ui->label_LoadImage->size(), Qt::IgnoreAspectRatio));
}

void MainWindow::on_radioButton_Threshold_Binary_clicked()
{
    val = 0;
    ui->label_PrimPlan->setVisible(true);
    ui->label_Marker->setVisible(true);
    ui->label_Watersheds->setVisible(true);

}

void MainWindow::on_radioButton_Threshold_Binary_Inv_clicked()
{
    val = 1;
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

    if(val == 0){ // binary
        threshold(binara, pozaThreshold_Binary, 120, 255, THRESH_BINARY);

        //Eliminam zgomot si obiecte mici
        Mat fg;
        erode(pozaThreshold_Binary, fg, Mat(valueSlider,valueSlider, CV_8U, Scalar(1)), Point(-1,-1), 6);

        QImage img = QImage((uchar*) fg.data, fg.cols, fg.rows, fg.step, QImage::Format_Indexed8);
        //Afisez imaginea in prim plan
        ui->label_Prim_Plan->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Prim_Plan->size(), Qt::IgnoreAspectRatio));

        Mat bg;
        dilate(pozaThreshold_Binary, bg, Mat(valueSlider,valueSlider, CV_8U, Scalar(1)), Point(-1,-1), 6);
        threshold(bg, bg, 1,128, THRESH_BINARY_INV);

        //Imaginea cu markeri;
        Mat markers(pozaThreshold_Binary.size(), CV_8U, Scalar(0));
        markers = fg+bg;

        //Afisam imagine cu markeri
        QImage imgMarkers = QImage((uchar*) markers.data, markers.cols, markers.rows, markers.step, QImage::Format_Indexed8);
        ui->label_Markers->setPixmap(QPixmap::fromImage(imgMarkers).scaled(ui->label_Markers->size(), Qt::IgnoreAspectRatio));

        WatershedSegmenter segment;
        segment.setMarkers(markers);
        segment.process(poza);

        Mat wat = segment.getWatersheds();

        QImage imgWatershed = QImage((uchar*) wat.data, wat.cols, wat.rows, wat.step, QImage::Format_Indexed8);
        ui->label_Watershed->setPixmap(QPixmap::fromImage(imgWatershed).scaled(ui->label_Watershed->size(), Qt::IgnoreAspectRatio));


    }else if(val == 1 ){ // binary_inv

        threshold(binara, pozaThreshold_Binary_Inv, 120, 255, THRESH_BINARY_INV);

        //Eliminam zgomot si obiecte mici
        Mat fg;
         erode(pozaThreshold_Binary_Inv, fg, Mat(valueSlider,valueSlider, CV_8U, Scalar(1)), Point(-1,-1), 6);

        QImage img = QImage((uchar*) fg.data, fg.cols, fg.rows, fg.step, QImage::Format_Indexed8);
        //Afisez imaginea in prim plan
        ui->label_Prim_Plan->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Prim_Plan->size(), Qt::IgnoreAspectRatio));

        Mat bg;
        dilate(pozaThreshold_Binary_Inv, bg, Mat(valueSlider,valueSlider, CV_8U, Scalar(1)), Point(-1,-1), 6);
        threshold(bg, bg, 1, 128, THRESH_BINARY_INV);

        //Imaginea cu markeri;
        Mat markers(pozaThreshold_Binary_Inv.size(), CV_8U, Scalar(0));
        markers = fg+bg;

        //Afisam imagine cu markeri
        QImage imgMarkers = QImage((uchar*) markers.data, markers.cols, markers.rows, markers.step, QImage::Format_Indexed8);
        ui->label_Markers->setPixmap(QPixmap::fromImage(imgMarkers).scaled(ui->label_Markers->size(), Qt::IgnoreAspectRatio));


        WatershedSegmenter segment;
        segment.setMarkers(markers);
        segment.process(poza);

        Mat wat = segment.getWatersheds();

        QImage imgWatershed = QImage((uchar*) wat.data, wat.cols, wat.rows, wat.step, QImage::Format_Indexed8);
        ui->label_Watershed->setPixmap(QPixmap::fromImage(imgWatershed).scaled(ui->label_Watershed->size(), Qt::IgnoreAspectRatio));


    }
}

void MainWindow::on_verticalSlider_sliderReleased()
{

}
