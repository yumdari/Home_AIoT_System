#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int, char**)
{
	Mat img_input, img_result, img_gray;
	Mat img_dilate;
	Mat img_erode;

	//이미지파일을 로드하여 image에 저장
	img_input = imread("n.jpg", IMREAD_COLOR);
	if (img_input.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	//그레이스케일 이미지로 변환
	cvtColor(img_input, img_gray, COLOR_BGR2GRAY);
	GaussianBlur(img_gray, img_gray, Size(5, 5), 0);

	//이진화 이미지로 변환
	Mat binary_image;
	threshold(img_gray, img_gray, 225, 255, THRESH_BINARY_INV);

	//노이즈 제거 
	erode(img_gray, img_erode, Mat::ones(Size(3, 3), CV_8UC1), Point(-1, -1));
	dilate(img_gray, img_dilate, Mat::ones(Size(3, 3), CV_8UC1), Point(-1, -1));
	

	//contour정보를 출력한다. (흑백,이진화 된 이미지만 적용)
	vector<vector<Point> > contours;
	//findContours(img_gray, contours, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	findContours(img_gray, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	//contour를 근사화한다.
	vector<Point2f> approx;
	img_result = img_input.clone();

	//출력
	//imshow("contours", img_dilate);
	imshow("cc", img_erode);

	for (size_t i = 0; i < contours.size(); i++)
	{//검출한 형상(외각선)을 표현하기 위해 꼭지점 찾아서 선 연결하기
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.01, true);

		if (fabs(contourArea(Mat(approx))) > 100)  //면적이 일정크기 이상이어야 한다.
		{

			int size = approx.size();
			
			////Contour를 근사화한 직선을 그린다.
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
	imshow("result", img_result);
	waitKey(0);

	return 0;
}