#include <QCoreApplication>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int dp;
int minDist;
int param1;
int param2;
int minRadius;
int maxRadius;
Mat pozaNecolor, poza;
vector<Vec3f> cercuri;

void faraZero(){
    if(dp == 0)
        dp = 1;

    if(minDist == 0)
        minDist = 1;

    if(param1 == 0)
        param1 = 1;

    if(param2 == 0)
        param2 = 1;
}

void deseneazaCercuri(Mat& poza){
    HoughCircles(pozaNecolor,
                 cercuri,
                 HOUGH_GRADIENT,
                 dp,
                 minDist,
                 param1,
                 param2,
                 minRadius,
                 maxRadius);

    Mat copiePoza;
    poza.copyTo(copiePoza);

    //Desenam cercurile gasite
    for(size_t i = 0; i < cercuri.size(); i++){
        Point center(cvRound(cercuri[i][0]),
                     cvRound(cercuri[i][1]));

        int radius = cvRound(cercuri[i][2]);

        //centrul cercului
        putText(copiePoza,
                "x: " + to_string((int)cercuri[i][0]) + "y: "+ to_string((int)cercuri[i][1]),
                center,
                FONT_HERSHEY_SIMPLEX,
                0.5,
                Scalar(0, 0, 255),
                1,
                8,
                false);

        //cercul
        circle(copiePoza,
               center,
               radius,
               Scalar(0, 0, 255),
               3,
               8,
               0);
    }

    imshow("Control Hough", copiePoza);
}

void detecteazaCercuri(Mat& poza){

    namedWindow("Control Hough", WINDOW_AUTOSIZE);

    createTrackbar("dp", "Control Hough", &dp, 10);
    createTrackbar("minDist", "Control Hough", &minDist, 50);
    createTrackbar("param1", "Control Hough", &param1, 255);
    createTrackbar("param2", "Control Hough", &param2, 255);
    createTrackbar("minRadius", "Control Hough", &minRadius, 255);
    createTrackbar("maxRadius", "Control Hough", &maxRadius, 255);
    cvtColor(poza, pozaNecolor, COLOR_BGR2GRAY);

    GaussianBlur(pozaNecolor, pozaNecolor, Size(5,5), 2);
    faraZero();
    deseneazaCercuri(poza);

}

int main(int argc, char *argv[])
{
    VideoCapture cap(0); //open the default camera

    if(!cap.isOpened()){ // daca nu se deschide camera, incheiem programul
        cout<<"Camera web nu poate fi pornita."<<endl;
        return -1;
    }

    while(true){

        Mat frame;
        cap>>frame;
        detecteazaCercuri(frame);
        if(waitKey(30) >= 0)
            break;
    }

    waitKey(0);
    return 0;
}
