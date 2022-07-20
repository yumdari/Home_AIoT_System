#include "opencv2/opencv.hpp"
#include "opencv2/highgui//highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{ 
    //트랙바 생성 및 크기 조절
    namedWindow("ControllWindow", WINDOW_NORMAL);
    resizeWindow("ControllWindow", 380, 300);

    //트랙바 기본 설정 값
    int LowH = 179;
    int HighH = 179;
    int LowS = 0;
    int HighS = 255;
    int LowV = 0;
    int HighV = 255;

    //트랙바 설정 및 최대값
    createTrackbar("LowH", "ControllWindow", &LowH, 179);
    createTrackbar("HighH", "ControllWindow", &HighH, 179);
    createTrackbar("LowS", "ControllWindow", &LowS, 255);
    createTrackbar("HighS", "ControllWindow", &HighS, 255);
    createTrackbar("LowV", "ControllWindow", &LowV, 255);
    createTrackbar("HighV", "ControllWindow", &HighV, 255);

    Mat  img_input,img_result, img_hsv;
    Mat frame; // OpenCV에서 가장 기본이 되는 Matrix 구조체(이미지를 읽어 해당 정보를 Mat형태로 변환)
    VideoCapture cap; // 동영상 불러오기
    cap.open(0); // 동영상 열기(Camera 열기) + 카메라번호(0(내장 우선))

    if (!cap.isOpened())
    {
        cout << "Error! Cannot open the camera" << endl;
        return -1;
    }
    for (;;)
    {   
        cap.read(img_input);
        //오류 확인
        if (img_input.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        //HSV 이미지로 변환
        cvtColor(img_input, img_hsv, COLOR_BGR2HSV);

        Mat S_mask, S_image;

        Scalar lower = Scalar(LowH, LowS, LowV);
        Scalar upper = Scalar(HighH, HighS, HighV);
 

        inRange(img_hsv, lower, upper, S_mask);  //이진화 됨
        bitwise_and(img_hsv, img_hsv, S_image, S_mask);

        //색 채우기
        Mat im_floodfill = S_mask.clone();
        floodFill(im_floodfill, cv::Point(0, 0), Scalar(255));

        Mat im_floodfill_inv;
        bitwise_not(im_floodfill, im_floodfill_inv);

        Mat im_out = (S_mask | im_floodfill_inv);

        //contour정보를 출력한다. (흑백,이진화 된 이미지만 적용)
        vector<vector<Point> > contours;
        findContours(im_floodfill_inv, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        //contour를 근사화한다.
        vector<Point2f> approx;
        img_result = img_input.clone();

        for (size_t i = 0; i < contours.size(); i++)
        {//검출한 형상(외각선)을 표현하기 위해 꼭지점 찾아서 선 연결하기
            approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.01, true);

            if (fabs(contourArea(Mat(approx))) > 1500)  //면적이 일정크기 이상이어야 한다.
            {
                int size = approx.size();
                
                //Contour를 근사화한 직선을 그린다.
                if (size % 2 == 0) {
                    line(img_result, approx[0], approx[approx.size() - 1], Scalar(0, 255, 0), 3);

                    for (int k = 0; k < size - 1; k++)
                        line(img_result, approx[k], approx[k + 1], Scalar(0, 255, 0), 3);

                    //점 표시 원 그리기
                    for (int k = 0; k < size; k++)
                        circle(img_result, approx[k], 3, Scalar(0, 0, 255));
                }
            }
        }
        imshow("im_floodfill_inv", im_floodfill_inv);
        imshow("result", img_result);
        if (waitKey(5) == 27) //ESC 키 누를 때 까지 대기
            break;
    }
    return 0;
}



