#include <QCoreApplication>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void contururiCamera(Mat& frame, Mat& contururi){
    cvtColor(frame, contururi, COLOR_BGR2GRAY);
    GaussianBlur(contururi, contururi, Size(7, 7), 1.5, 1.5);
    Canny(contururi, contururi, 0, 30, 3);
    imshow("Contururi camera", contururi);
}

int main(int argc, char *argv[])
{
    VideoCapture cap(0); //open the default camera

    if(!cap.isOpened()){ // daca nu se deschide camera, incheiem programul
        cout<<"Camera web nu poate fi pornita."<<endl;
        return -1;
    }

    Mat camera;
    namedWindow("Redare camera", WINDOW_AUTOSIZE);
    while(true){

        Mat frame;
        cap>>frame;
        contururiCamera(frame, camera);
        if(waitKey(30) >= 0)
            break;
    }

    waitKey(0);
    return 0;
}
