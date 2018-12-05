#ifndef WATERSHEDSEGMENTER_H
#define WATERSHEDSEGMENTER_H

#include <QMainWindow>
#include <QtGui>
#include <QFileDialog>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class WatershedSegmenter{
private:
    Mat markers; //imagine marker

public:

    void setMarkers(Mat& markerImage){
        markerImage.convertTo(markers, CV_32S);
    }

    Mat process(Mat &image){

        //aplicam algoritmul watersjed
        watershed(image, markers);

        return markers;
    }

    //Intoarcem rezultatul sun fomra unei imagini
    Mat getSegmentation(){
        Mat rez;
        markers.convertTo(rez, CV_32S);
        return rez;
    }

    Mat getWatersheds(){
        Mat rez;
        markers.convertTo(rez, CV_8U, 255, 255);
        return rez;
    }
};

#endif // WATERSHEDSEGMENTER_H
