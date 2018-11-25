#include "mainwindow.h"
#include "ui_mainwindow.h"

#define CV_BGR2GRAY cv::COLOR_BGR2GRAY

/*
    Realizati un program cu GUI care sa permita
utilizatorului sa incarce o imagine si sa ii aplice o
segmentare folosing thresholding. Utilizatorul
trebuie sa poata alege din cele 5 tipuri de
thresholding si sa tunifice valorile celor 2 praguri
prin slidere.
*/


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_Initial_Image;
    ui->label_Thresholding_Bin_Inv;
    ui->label_Thresholding_Binary;
    ui->label_Thresholding_Trunc;
    ui->label_Thresholding_Tozero;
    ui->label_Thresholding_Tozero_Inv;
    ui->label_Slider1;
    ui->label_Slider2;


    ui->radioButton_Thresh_Binary;
    ui->radioButton_Thresh_Bin_Inv;
    ui->radioButton_Thresh_Trunc;
    ui->radioButton_Thresh_Tozero;
    ui->radioButton_Thresh_Tozero_Inv;


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Load_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"),
                                                    ".",
                                                    tr("Image Files(*.jpg *.jpeg *.png *.bmp)"));

    poza = imread(fileName.toLatin1().data(), 0);

   // cvtColor(poza, poza, CV_BGR2GRAY);

    QImage img = QImage((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_Indexed8);

    ui->label_Initial_Image->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Initial_Image->size(), Qt::IgnoreAspectRatio));

}


void MainWindow::on_verticalSlider_valueChanged(int value)
{
    QString cdt(" ");
    cdt.append(QString::number(value));

      //Stringul este trimis prin eticheta de sub slider
      this->ui->label_Slider1->setText(cdt);

      Mat thresholded;

      int y = ui->verticalSlider_2->value();

      if(ui->radioButton_Thresh_Binary->isChecked()){
          threshold(poza, thresholded, value, y, THRESH_BINARY);

          QImage img = QImage((uchar*) thresholded.data, thresholded.cols, thresholded.rows, thresholded.step,
                              QImage::Format_Indexed8);

           ui->label_Thresholding_Binary->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Thresholding_Binary->size(), Qt::IgnoreAspectRatio));
      }else if(ui->radioButton_Thresh_Bin_Inv->isChecked()){

          threshold(poza, thresholded, value, y, THRESH_BINARY_INV);

          QImage img = QImage((uchar*) thresholded.data, thresholded.cols, thresholded.rows, thresholded.step,
                              QImage::Format_Indexed8);
          ui->label_Thresholding_Bin_Inv->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Thresholding_Bin_Inv->size(), Qt::IgnoreAspectRatio));
      }else if(ui->radioButton_Thresh_Trunc->isChecked()){

          threshold(poza, thresholded, value, y, THRESH_TRUNC);

          QImage img = QImage((uchar*) thresholded.data, thresholded.cols, thresholded.rows, thresholded.step,
                              QImage::Format_Indexed8);
          ui->label_Thresholding_Trunc->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Thresholding_Trunc->size(), Qt::IgnoreAspectRatio));

      }else if(ui->radioButton_Thresh_Tozero->isChecked()){

          threshold(poza, thresholded, value, y, THRESH_TOZERO);

          QImage img = QImage((uchar*) thresholded.data, thresholded.cols, thresholded.rows, thresholded.step,
                              QImage::Format_Indexed8);
          ui->label_Thresholding_Tozero->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Thresholding_Tozero->size(), Qt::IgnoreAspectRatio));

      }else if(ui->radioButton_Thresh_Tozero_Inv->isChecked()){

          threshold(poza, thresholded, value, y, THRESH_TOZERO_INV);

          QImage img = QImage((uchar*) thresholded.data, thresholded.cols, thresholded.rows, thresholded.step,
                              QImage::Format_Indexed8);
          ui->label_Thresholding_Tozero_Inv->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Thresholding_Tozero_Inv->size(), Qt::IgnoreAspectRatio));

      }
}

void MainWindow::on_verticalSlider_2_valueChanged(int value)
{
    QString cdt(" ");
    cdt.append(QString::number(value));

      //Stringul este trimis prin eticheta de sub slider
      this->ui->label_Slider2->setText(cdt);

      Mat thresholded;

      int x = ui->verticalSlider->value();

      if(ui->radioButton_Thresh_Binary->isChecked()){
          threshold(poza, thresholded, x, value, THRESH_BINARY);

          QImage img = QImage((uchar*) thresholded.data, thresholded.cols, thresholded.rows, thresholded.step,
                              QImage::Format_Indexed8);

           ui->label_Thresholding_Binary->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Thresholding_Binary->size(), Qt::IgnoreAspectRatio));
      }else if(ui->radioButton_Thresh_Bin_Inv->isChecked()){

          threshold(poza, thresholded, x, value, THRESH_BINARY_INV);

          QImage img = QImage((uchar*) thresholded.data, thresholded.cols, thresholded.rows, thresholded.step,
                              QImage::Format_Indexed8);
          ui->label_Thresholding_Bin_Inv->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Thresholding_Bin_Inv->size(), Qt::IgnoreAspectRatio));
      }else if(ui->radioButton_Thresh_Trunc->isChecked()){

          threshold(poza, thresholded, x, value, THRESH_TRUNC);

          QImage img = QImage((uchar*) thresholded.data, thresholded.cols, thresholded.rows, thresholded.step,
                              QImage::Format_Indexed8);
          ui->label_Thresholding_Trunc->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Thresholding_Trunc->size(), Qt::IgnoreAspectRatio));

      }else if(ui->radioButton_Thresh_Tozero->isChecked()){

          threshold(poza, thresholded, x, value, THRESH_TOZERO);

          QImage img = QImage((uchar*) thresholded.data, thresholded.cols, thresholded.rows, thresholded.step,
                              QImage::Format_Indexed8);
          ui->label_Thresholding_Tozero->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Thresholding_Tozero->size(), Qt::IgnoreAspectRatio));

      }else if(ui->radioButton_Thresh_Tozero_Inv->isChecked()){

          threshold(poza, thresholded, x, value, THRESH_TOZERO_INV);

          QImage img = QImage((uchar*) thresholded.data, thresholded.cols, thresholded.rows, thresholded.step,
                              QImage::Format_Indexed8);
          ui->label_Thresholding_Tozero_Inv->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Thresholding_Tozero_Inv->size(), Qt::IgnoreAspectRatio));

      }
}

void MainWindow::on_verticalSlider_sliderReleased()
{
    Mat thresholded;

    int value = ui->verticalSlider->value();
    int y = ui->verticalSlider_2->value();

    if(ui->radioButton_Thresh_Binary->isChecked()){
        threshold(poza, thresholded, value, y, THRESH_BINARY);

        QImage img = QImage((uchar*) thresholded.data, thresholded.cols, thresholded.rows, thresholded.step,
                            QImage::Format_Indexed8);

         ui->label_Thresholding_Binary->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Thresholding_Binary->size(), Qt::IgnoreAspectRatio));
    }else if(ui->radioButton_Thresh_Bin_Inv->isChecked()){

        threshold(poza, thresholded, value, y, THRESH_BINARY_INV);

        QImage img = QImage((uchar*) thresholded.data, thresholded.cols, thresholded.rows, thresholded.step,
                            QImage::Format_Indexed8);
        ui->label_Thresholding_Bin_Inv->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Thresholding_Bin_Inv->size(), Qt::IgnoreAspectRatio));
    }else if(ui->radioButton_Thresh_Trunc->isChecked()){

        threshold(poza, thresholded, value, y, THRESH_TRUNC);

        QImage img = QImage((uchar*) thresholded.data, thresholded.cols, thresholded.rows, thresholded.step,
                            QImage::Format_Indexed8);
        ui->label_Thresholding_Trunc->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Thresholding_Trunc->size(), Qt::IgnoreAspectRatio));

    }else if(ui->radioButton_Thresh_Tozero->isChecked()){

        threshold(poza, thresholded, value, y, THRESH_TOZERO);

        QImage img = QImage((uchar*) thresholded.data, thresholded.cols, thresholded.rows, thresholded.step,
                            QImage::Format_Indexed8);
        ui->label_Thresholding_Tozero->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Thresholding_Tozero->size(), Qt::IgnoreAspectRatio));

    }else if(ui->radioButton_Thresh_Tozero_Inv->isChecked()){

        threshold(poza, thresholded, value, y, THRESH_TOZERO_INV);

        QImage img = QImage((uchar*) thresholded.data, thresholded.cols, thresholded.rows, thresholded.step,
                            QImage::Format_Indexed8);
        ui->label_Thresholding_Tozero_Inv->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Thresholding_Tozero_Inv->size(), Qt::IgnoreAspectRatio));

    }
}

void MainWindow::on_verticalSlider_2_sliderReleased()
{
    Mat thresholded;

    int value = ui->verticalSlider_2->value();
    int x = ui->verticalSlider->value();

    if(ui->radioButton_Thresh_Binary->isChecked()){
        threshold(poza, thresholded, x, value, THRESH_BINARY);

        QImage img = QImage((uchar*) thresholded.data, thresholded.cols, thresholded.rows, thresholded.step,
                            QImage::Format_Indexed8);

         ui->label_Thresholding_Binary->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Thresholding_Binary->size(), Qt::IgnoreAspectRatio));
    }else if(ui->radioButton_Thresh_Bin_Inv->isChecked()){

        threshold(poza, thresholded, x, value, THRESH_BINARY_INV);

        QImage img = QImage((uchar*) thresholded.data, thresholded.cols, thresholded.rows, thresholded.step,
                            QImage::Format_Indexed8);
        ui->label_Thresholding_Bin_Inv->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Thresholding_Bin_Inv->size(), Qt::IgnoreAspectRatio));
    }else if(ui->radioButton_Thresh_Trunc->isChecked()){

        threshold(poza, thresholded, x, value, THRESH_TRUNC);

        QImage img = QImage((uchar*) thresholded.data, thresholded.cols, thresholded.rows, thresholded.step,
                            QImage::Format_Indexed8);
        ui->label_Thresholding_Trunc->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Thresholding_Trunc->size(), Qt::IgnoreAspectRatio));

    }else if(ui->radioButton_Thresh_Tozero->isChecked()){

        threshold(poza, thresholded, x, value, THRESH_TOZERO);

        QImage img = QImage((uchar*) thresholded.data, thresholded.cols, thresholded.rows, thresholded.step,
                            QImage::Format_Indexed8);
        ui->label_Thresholding_Tozero->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Thresholding_Tozero->size(), Qt::IgnoreAspectRatio));

    }else if(ui->radioButton_Thresh_Tozero_Inv->isChecked()){

        threshold(poza, thresholded, x, value, THRESH_TOZERO_INV);

        QImage img = QImage((uchar*) thresholded.data, thresholded.cols, thresholded.rows, thresholded.step,
                            QImage::Format_Indexed8);
        ui->label_Thresholding_Tozero_Inv->setPixmap(QPixmap::fromImage(img).scaled(ui->label_Thresholding_Tozero_Inv->size(), Qt::IgnoreAspectRatio));

    }
}
