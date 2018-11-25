#ifndef HISTOGRAMA_H
#define HISTOGRAMA_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class Histogram1D{
private:
    int histSize[1];
    float hranges[2];
    const float* ranges[1];
    int channels[1];

public:
    Histogram1D(){
        //initializam argumentele
        histSize[0] = 256;
        hranges[0] = 0.0;
        hranges[1] = 255.0;
        ranges[0] = hranges;
        channels[0] = 0;
    }

    MatND getHistogram(const Mat &image){

        MatND hist;

        //Calculez histograma
        calcHist(&image,
                 1,
                 channels,
                 Mat(),
                 hist,
                 1,
                 histSize,
                 ranges);

        return hist;
    }

    //Intoarce maginea unei histograme
    Mat getHistogramImage(const Mat &image){

        MatND hist = getHistogram(image);

        //Aflam valorile min si max
        double maxVal = 0;
        double minVal = 0;

        minMaxLoc(hist, &minVal, &maxVal, 0, 0);

        //Imaginea in care sa afisam histograma
        Mat histImg(histSize[0], histSize[0], CV_8U, Scalar(255));

        //Pun cel mai inalt punct la 90% din 256
        int hpt = static_cast<int>(0.9*histSize[0]);
        for(int h = 0; h < histSize[0]; h++){
            float binVal = hist.at<float>(h);
            int intensity = static_cast<int>(binVal*hpt/maxVal);
            line(histImg, Point(h, histSize[0]), Point(h, histSize[0]- intensity), Scalar::all(0));
        }
        return histImg;
    }

    void multipleThreshold(Mat &poza, int type){

        String rez;
        rez = "Ponderata";
        Mat thresholded;

        switch (type) {

        case 0: //Thresh_Binary
            rez += "Thresh_Binary";
            threshold(poza,thresholded, 120, 255, THRESH_BINARY);
            break;

        case 1: //Thresh_Binry_Inv
            rez += "Thresh_Binary_Inv";
            threshold(poza, thresholded, 120, 255, THRESH_BINARY_INV);
            break;

        case 2: //Thresh_Trunc
            rez += "Thresh_Trunc";
            threshold(poza, thresholded, 120, 255, THRESH_TRUNC);
            break;

        case 3: //Thresh_Tozero
            rez += "Thresh_Tozero";
            threshold(poza, thresholded, 120, 255, THRESH_TOZERO);
            break;

        case 4: //Thresh_Tozero_Inv
            rez += "Thresh_Tozero_Inv";
            threshold(poza, thresholded, 120, 255, THRESH_TOZERO_INV);
            break;

        default:
            cout<<"Sunt numai 5 posibilitati: 0-4";
            break;

        }


    }

};

#endif // HISTOGRAMA_H
