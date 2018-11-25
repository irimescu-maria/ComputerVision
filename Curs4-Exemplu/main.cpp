#include "mainwindow.h"
#include <QApplication>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "colordetector.h"
using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    ColorDetector cdetect;

    //citim imaginea
    Mat poza = imread("C:/Users/Maria/Downloads/image1.jpg");
    if(!poza.data)
        return 0;

    //Stabilim culoarea tinta
    cdetect.setTargetColor(170,255,255);
    Mat rez = cdetect.process(poza);

    namedWindow(("Initial"));
    imshow("Initial", poza);

    namedWindow("Proceseaza");
    imshow("Proceseaza", rez);

    waitKey();

    return a.exec();
}
