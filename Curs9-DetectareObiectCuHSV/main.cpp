#include <QCoreApplication>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>



using namespace  std;
using namespace cv;


int iLowH, iHighH; // HUE(0 - 179)
int iLowS, iHighS; // Sat(0 - 255)
int iLowV, iHighV; // Val(0 - 255)

Mat poza;

void trackBars(){
    namedWindow("Control", WINDOW_AUTOSIZE);

    //Create trackbars in "Control" window
    createTrackbar("LowH", "Control", &iLowH, 179);
    createTrackbar("HighH", "Control", &iHighH, 179);

    createTrackbar("LowS", "Control", &iLowS, 255);
    createTrackbar("HighS", "Control", &iHighS, 255);

    createTrackbar("LowV", "Control", &iLowV, 255);
    createTrackbar("HighV", "Control", &iHighV, 255);
    cout<<"iLowH = "<<iLowH<<endl;
}

void faraZero(){


    if(iLowH == 0){
        iLowH = 1;
    }

    if(iLowS == 0)
        iLowS = 1;

    if(iLowV == 0)
        iLowV = 1;

    if(iHighH == 0)
        iHighH = 1;

    if(iHighS == 0)
        iHighS = 1;

    if(iHighV == 0)
        iHighV = 1;
}

void cautaObiectInPoza(){

    while(true){
        faraZero();
        Mat imgHSV, imgThresholded;
        cvtColor(poza, imgHSV, COLOR_BGR2HSV);

        inRange(imgHSV,
                Scalar(iLowH, iLowS, iLowV),
                Scalar(iHighH, iHighS, iHighV),
                imgThresholded);

        //aplicam deschidere pentru a elimina obiectele mici din fundal
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
        dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));

        //aplicam inchidere pentru a elinima obiectele mici din prim plan
        dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
        namedWindow("Cauta obiect", WINDOW_AUTOSIZE);
        imshow("Cauta obiect", imgThresholded);
        if(waitKey(50) > 0){
            break;
        }
    }
}

int main(){

    poza = imread("C:/Users/Maria/Downloads/Donuts.jpg");

    trackBars();
    cautaObiectInPoza();
}
