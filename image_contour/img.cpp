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

	//�̹��������� �ε��Ͽ� image�� ����
	img_input = imread("n.jpg", IMREAD_COLOR);
	if (img_input.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	//�׷��̽����� �̹����� ��ȯ
	cvtColor(img_input, img_gray, COLOR_BGR2GRAY);
	GaussianBlur(img_gray, img_gray, Size(5, 5), 0);

	//����ȭ �̹����� ��ȯ
	Mat binary_image;
	threshold(img_gray, img_gray, 225, 255, THRESH_BINARY_INV);

	//������ ���� 
	erode(img_gray, img_erode, Mat::ones(Size(3, 3), CV_8UC1), Point(-1, -1));
	dilate(img_gray, img_dilate, Mat::ones(Size(3, 3), CV_8UC1), Point(-1, -1));
	

	//contour������ ����Ѵ�. (���,����ȭ �� �̹����� ����)
	vector<vector<Point> > contours;
	//findContours(img_gray, contours, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	findContours(img_gray, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	//contour�� �ٻ�ȭ�Ѵ�.
	vector<Point2f> approx;
	img_result = img_input.clone();

	//���
	//imshow("contours", img_dilate);
	imshow("cc", img_erode);

	for (size_t i = 0; i < contours.size(); i++)
	{//������ ����(�ܰ���)�� ǥ���ϱ� ���� ������ ã�Ƽ� �� �����ϱ�
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.01, true);

		if (fabs(contourArea(Mat(approx))) > 100)  //������ ����ũ�� �̻��̾�� �Ѵ�.
		{

			int size = approx.size();
			
			////Contour�� �ٻ�ȭ�� ������ �׸���.
			if (size % 2 == 0) {
				line(img_result, approx[0], approx[approx.size() - 1], Scalar(0, 255, 0), 3);

				for (int k = 0; k < size - 1; k++)
					line(img_result, approx[k], approx[k + 1], Scalar(0, 255, 0), 3);
				//�� ǥ�� �� �׸���
				for (int k = 0; k < size; k++)
					circle(img_result, approx[k], 3, Scalar(0, 0, 255));
			}
		}
	}
	imshow("result", img_result);
	waitKey(0);

	return 0;
}