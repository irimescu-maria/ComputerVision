#ifndef CARACTERISTICI_H
#define CARACTERISTICI_H

#include <QtGui>
#include <QFileDialog>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class Caracteristici{
private:
    int threshold; //progul pentru a obtine o imagine binara

    Mat cruce;
    Mat romb;
    Mat patrat;
    Mat x;

    void applyThreshold(Mat& result){
         if(threshold>0){
             cv::threshold(result, result, threshold, 255, THRESH_BINARY);
         }
     }

 public:
     Mat getEdges(Mat &image){
         Mat result;
         morphologyEx(image, result, MORPH_GRADIENT, Mat());

         applyThreshold(result);

         return result;
     }

     Caracteristici(){
         threshold = 0;

         cruce = Mat(5, 5, CV_8U, Scalar(0));

         romb = Mat(5, 5, CV_8U, Scalar(1));
         patrat = Mat(5, 5, CV_8U, Scalar(1));
         x = Mat(5, 5, CV_8U, Scalar(0));

         //Element structural in forma de cruce
         for(int i=0; i<5; i++){
             cruce.at<uchar>(2,i) = 1;
             cruce.at<uchar>(i,2) = 1;
         }

         //Element structural in forma de romb
         romb.at<uchar>(0,0) = 0;
         romb.at<uchar>(0,1) = 0;
         romb.at<uchar>(1,0) = 0;
         romb.at<uchar>(4,4) = 0;
         romb.at<uchar>(3,4) = 0;
         romb.at<uchar>(4,3) = 0;
         romb.at<uchar>(4,0) = 0;
         romb.at<uchar>(4,1) = 0;
         romb.at<uchar>(3,0) = 0;
         romb.at<uchar>(0,4) = 0;
         romb.at<uchar>(0,3) = 0;
         romb.at<uchar>(1,4) = 0;

         //Element structural in forma de X
         for(int i = 0; i<5;i++){
             x.at<uchar>(i,i) = 1;
             x.at<uchar>(4-i, i) = 1;
         }

     }

     Mat getCorners(const Mat &poza){
         Mat rez;

         //Dilatam cu cruce
         dilate(poza, rez, cruce);

         //Erodam cu romb
         erode(rez, rez, romb);

         Mat rez2;
         //Dilatare cu X
         dilate(poza, rez2, x);

         //Erodare cu patrat
         erode(rez2, rez2, patrat);

         //Colturile se obtin prin diferentierea celor 2 imagini rezultate
         absdiff(rez2,rez,rez);

         applyThreshold(rez);

         return rez;
     }

     void drawOnImage(Mat& binary, Mat& image){

         Mat_<uchar>::const_iterator it = binary.begin<uchar>();
         Mat_<uchar>::const_iterator itend = binary.end<uchar>();

         for(int i = 0; it != itend; ++it, ++i){

             if(*it == 0) //daca pixelul curent este negru
                 circle(image, Point(i%image.step, i/image.step), 5, Scalar(255,0,0));
         }
     }
};

#endif // CARACTERISTICI_H
