#ifndef COLORDETECTOR_H
#define COLORDETECTOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;
class ColorDetector{
private:
    //distanta prag
    int minDist;

    //culoarea de detectat
    Vec3b target;

    //imaginea alb-negru rezultata
    Mat rez;

    //Calculam distanta Manhattan de la culoarea tinta
    int getDistance(Vec3b color){
        return abs(color[0]-target[0])+abs(color[1]-target[1])+abs(color[2]-target[2]);
           }

    //Calculam distanta Euclidiana
    int getDistanceEuclid(Vec3b color){
        return sqrt(((color[0]-target[0])*(color[0]-target[0]))+((color[1]-target[1])*(color[1]-target[1]))+((color[2]-target[2])*(color[2]-target[2])));
    }
public:
    //constructor
    ColorDetector(){
        minDist = 100;
        target[0] = target[1]=target[2]=0;
    }

    //Metode set si get

    //Setarea pragului distanta.
    void setColorDistanceThreshold(int distance){
        if(distance < 0)
            distance = 0;
        minDist = distance;
    }

    //Intoarce valoarea pragului distanta
    int getColorDistanceThreshold(){
        return minDist;
    }

    //Setez culoarea de detectat
    void setTargetColor(uchar red, uchar green, uchar blue){
        target[0] = blue;
        target[1] = green;
        target[2] = red;
    }

    //Setez culoarea de detectat
    void setTargetColor(Vec3b color){
        target = color;
    }

    Vec3b getTargetColor(){
        return target;
    }

    //Proceseaza imaginea. Intoarce o imagine alb-negru cu un singur canal
    Mat process(Mat &image){
        rez.create(image.rows, image.cols, CV_8U);

        //folosim iteratori
        Mat_<Vec3b>::const_iterator it = image.begin<Vec3b>();
        Mat_<Vec3b>::const_iterator itend = image.end<Vec3b>();
        Mat_<uchar>::iterator itout = rez.begin<uchar>();

        //pentru fiecare pixel
        for( ; it != itend; ++it, ++itout){

            //calculam distanta de la culoarea pixelului la culoarea tinta
            if(getDistance(*it) < minDist){
                *itout = 255; // alb
                cout<<getDistance(*it);
            }
            else
                *itout = 0; //negru
        }
        return rez;
    }

    Mat processEuclid(Mat &image){
        rez.create(image.rows, image.cols, CV_8U);

        //folosim iteratori
        Mat_<Vec3b>::const_iterator it = image.begin<Vec3b>();
        Mat_<Vec3b>::const_iterator itend = image.end<Vec3b>();
        Mat_<uchar>::iterator itout = rez.begin<uchar>();

        //pentru fiecare pixel
        for( ; it != itend; ++it, ++itout){

            //calculam distanta de la culoarea pixelului la culoarea tinta
            if(getDistanceEuclid(*it) < minDist){
                *itout = 255; // alb
            }
            else
                *itout = 0; //negru
        }
        return rez;
    }
};

#endif // COLORDETECTOR_H
