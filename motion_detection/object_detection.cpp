#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int, char**)
{
	int rectangle = 0;
	Mat img_input, img_result, img_gray, img_erode, img_dilate;
	Mat frame; // OpenCV���� ���� �⺻�� �Ǵ� Matrix ����ü(�̹����� �о� �ش� ������ Mat���·� ��ȯ)
	VideoCapture cap; // ������ �ҷ�����
	cap.open(0); // ������ ����(Camera ����) + ī�޶��ȣ(0(���� �켱))
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
		//�׷��̽����� �̹����� ��ȯ
		cvtColor(img_input, img_gray, COLOR_BGR2GRAY);
		GaussianBlur(img_gray, img_gray, Size(5, 5), 0, 0);
		//����ȭ �̹����� ��ȯ
		threshold(img_gray, img_gray, 200, 255, THRESH_BINARY);

		//������ ���� (�������� ��� ����������
		erode(img_gray, img_erode, Mat::ones(Size(5, 5), CV_8UC1), Point(-1, -1));
		dilate(img_erode, img_dilate, Mat::ones(Size(5, 5), CV_8UC1), Point(-1, -1));
		//�������� ���� ������ ����
		dilate(img_dilate, img_dilate, Mat::ones(Size(5, 5), CV_8UC1), Point(-1, -1));
		erode(img_dilate, img_erode, Mat::ones(Size(5, 5), CV_8UC1), Point(-1, -1));

		//���� �� ä���
		Mat im_floodfill = img_erode.clone();
		floodFill(im_floodfill, Point(0, 0), Scalar(255));
		Mat im_floodfill_inv;
		bitwise_not(im_floodfill, im_floodfill_inv);
		Mat im_out = (img_erode | im_floodfill_inv);

		//contour�� ã�´�.
		vector<vector<Point> > contours;
		findContours(im_out, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		//contour�� �ٻ�ȭ�Ѵ�.
		vector<Point2f> approx;
		img_result = img_input.clone();

		for (size_t i = 0; i < contours.size(); i++)
		{//������ ����(�ܰ���)�� ǥ���ϱ� ���� ������ ã�Ƽ� �� �����ϱ�
			approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.01, true);
			if (fabs(contourArea(Mat(approx))) > 1000)
			{
				int size = approx.size();
				if (size % 2 == 0) {
					line(img_result, approx[0], approx[approx.size() - 1], Scalar(0, 255, 0), 3);
					for (int k = 0; k < size - 1; k++)
						line(img_result, approx[k], approx[k + 1], Scalar(0, 255, 0), 3);
					//�� ǥ�� �� �׸���
					for (int k = 0; k < size; k++)
						circle(img_result, approx[k], 3, Scalar(0, 0, 255));
				}
				if (size > 4)//������ �� ���� 
					rectangle = 1;    //�簢���̸� ++
				else
					rectangle = 0;
			}
		}
		imshow("result", img_result);	//�� ���� 
		imshow("im_out", im_out);
		if (waitKey(5) == 27) //ESC Ű ���� �� ���� ���
			break;
	}
	return 0;
}