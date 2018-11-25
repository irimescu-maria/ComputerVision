#include <QCoreApplication>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    VideoCapture capture("C:/Users/Maria/Downloads/Video Of People Walking.mp4");

    if( !capture.isOpened() ){
        cout<<"Fisierul video nu poate fi rulat"<<endl;
        return -1;
    }

 //   double fps = capture.get(CAP_PROS_FPS);
    double fps = capture.get(25);
    cout<<"Frame-uri pe secunda : "<< fps<<endl;

    namedWindow("Clipul meu", WINDOW_NORMAL);
    resizeWindow("Clipul meu", 500, 300);

    while(1){
        Mat frame;

        if(!capture.read(frame)){
            cout<<"Nu se poate citi fisierul video"<< endl;
            break;
        }

        Mat poza = imread("C:/Users/Maria/Downloads/images.jpg");
        Mat pozaROI = frame(Rect(50, 5, poza.cols, poza.rows));
        addWeighted(pozaROI,1.0,poza,0.3,0.,pozaROI);

        imshow("Clipul meu", frame);
        if(waitKey(30) == 27){
            cout<<"Am incheiat clipul cu ESC"<< endl;
            waitKey(2000);
            break;
        }
    }
    return 0;
}
