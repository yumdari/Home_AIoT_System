#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int, char**)
{
	Mat img_input, img_result, img_gray, img_temp;
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
		// check if we succeeded
		if (img_input.empty()) {
			cerr << "ERROR! blank frame grabbed\n";
			break;
		}

		//그레이스케일 이미지로 변환
		cvtColor(img_input, img_gray, COLOR_BGR2GRAY);
		GaussianBlur(img_gray, img_gray, Size(5, 5), 0);


		//이진화 이미지로 변환
		adaptiveThreshold(img_gray, img_temp,
			255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 225, 5);
		//threshold(img_gray, img_temp, 130, 255, THRESH_BINARY_INV);


		//노이즈 제거 
		Mat img_dilate;
		Mat img_erode;
		dilate(img_temp, img_dilate, Mat::ones(Size(3, 3), CV_8UC1), Point(-1, -1));
		erode(img_temp, img_erode, Mat::ones(Size(3, 3), CV_8UC1), Point(-1, -1));

		//contour를 찾는다.
		vector<vector<Point> > contours;
		findContours(img_temp, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

		imshow("img_erode", img_erode);

		//contour를 근사화한다.
		vector<Point2f> approx;
		img_result = img_input.clone();

		for (size_t i = 0; i < contours.size(); i++)
		{//검출한 형상(외각선)을 표현하기 위해 꼭지점 찾아서 선 연결하기
			approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.08, true);

			if (fabs(contourArea(Mat(approx))) > 1500)  //면적이 일정크기 이상이어야 한다.
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
			}
		}
		imshow("result", img_result);	//선 검출 
		if (waitKey(5) == 27) //ESC 키 누를 때 까지 대기
			break;
	}

	return 0;
}