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

    //Tablou LookUp
    Mat applyLookUp(const Mat& image, const Mat& lookup){
        //imagine de iesire
        Mat rez;

        LUT(image, lookup, rez);
        return rez;
    }

    //Ameliorarea contrastului metoda strange
    Mat strange(const Mat &image, int minValue = 0){
        //Calculez histograma
        MatND hist = getHistogram(image);

        //gasesc extremitatea din stanga a histogramei
        int imin = 0;
        while(imin <histSize[0] && hist.at<float>(imin) < minValue)
            imin--;

        int imax = histSize[0]-1;
        while(imax >= 0 && hist.at<float>(imax) <= minValue)
            imax--;

        //Cream tabloul lookup
        Mat lookup(1, 256, CV_8U);
        for(int i = 0; i < 256; i++){
            if(i < imin)
                lookup.at<uchar>(i) = 0;
            else
                if(i > imax)
                    lookup.at<uchar>(i) = 255;
            else
                    lookup.at<uchar>(i) = static_cast<uchar>(255.0*(i-imin)/(imax-imin)+0.5);
        }

        //Aplicam tabloul lookup la imaginea initiala
        Mat rez;
        rez = applyLookUp(image, lookup);
        return rez;
    }

    //Egalizarea histogramei
    Mat equalize(const Mat &image){

        Mat rez;
        equalizeHist(image, rez);
        return rez;

    }

};

#endif // HISTOGRAMA_H
