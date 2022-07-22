#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int, char**)
{
	int rectangle = 0;
	Mat img_input, img_result, img_gray, img_erode, img_dilate;
	Mat frame; // OpenCV에서 가장 기본이 되는 Matrix 구조체(이미지를 읽어 해당 정보를 Mat형태로 변환)
	VideoCapture cap; // 동영상 불러오기
	cap.open(0); // 동영상 열기(Camera 열기) + 카메라번호(0(내장 우선))
	if (!cap.isOpened()) {
		cout << "Error! Cannot open the camera" << endl;
		return -1;
	}
	for (;;) {
		cap.read(img_input);
		if (img_input.empty()) {
			cerr << "ERROR! blank frame grabbed\n";
			break;
		}
		//그레이스케일 이미지로 변환
		cvtColor(img_input, img_gray, COLOR_BGR2GRAY);
		GaussianBlur(img_gray, img_gray, Size(5, 5), 0, 0);
		//이진화 이미지로 변환
		threshold(img_gray, img_gray, 200, 255, THRESH_BINARY);

		//노이즈 제거 (열림연산 배경 노이즈제거
		erode(img_gray, img_erode, Mat::ones(Size(5, 5), CV_8UC1), Point(-1, -1));
		dilate(img_erode, img_dilate, Mat::ones(Size(5, 5), CV_8UC1), Point(-1, -1));
		//닫힘연산 내부 노이즈 제거
		dilate(img_dilate, img_dilate, Mat::ones(Size(5, 5), CV_8UC1), Point(-1, -1));
		erode(img_dilate, img_erode, Mat::ones(Size(5, 5), CV_8UC1), Point(-1, -1));

		//내부 색 채우기
		Mat im_floodfill = img_erode.clone();
		floodFill(im_floodfill, Point(0, 0), Scalar(255));
		Mat im_floodfill_inv;
		bitwise_not(im_floodfill, im_floodfill_inv);
		Mat im_out = (img_erode | im_floodfill_inv);

		//contour를 찾는다.
		vector<vector<Point> > contours;
		findContours(im_out, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		//contour를 근사화한다.
		vector<Point2f> approx;
		img_result = img_input.clone();

		for (size_t i = 0; i < contours.size(); i++)
		{//검출한 형상(외곽선)을 표현하기 위해 꼭지점 찾아서 선 연결하기
			approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.01, true);
			if (fabs(contourArea(Mat(approx))) > 1000)
			{
				int size = approx.size();
				if (size % 2 == 0) {
					line(img_result, approx[0], approx[approx.size() - 1], Scalar(0, 255, 0), 3);
					for (int k = 0; k < size - 1; k++)
						line(img_result, approx[k], approx[k + 1], Scalar(0, 255, 0), 3);
					//점 표시 원 그리기
					for (int k = 0; k < size; k++)
						circle(img_result, approx[k], 3, Scalar(0, 0, 255));
				}
				if (size > 4)//위에서 본 상자 
					rectangle = 1;    //사각형이면 ++
				else
					rectangle = 0;
			}
		}
		imshow("result", img_result);	//선 검출 
		imshow("im_out", im_out);
		if (waitKey(5) == 27) //ESC 키 누를 때 까지 대기
			break;
	}
	return 0;
}