#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int, char**)
{
	Mat img_input, img_result, img_gray, img_temp;
	Mat frame; // OpenCV���� ���� �⺻�� �Ǵ� Matrix ����ü(�̹����� �о� �ش� ������ Mat���·� ��ȯ)
	VideoCapture cap; // ������ �ҷ�����
	cap.open(0); // ������ ����(Camera ����) + ī�޶��ȣ(0(���� �켱))

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

		//�׷��̽����� �̹����� ��ȯ
		cvtColor(img_input, img_gray, COLOR_BGR2GRAY);
		GaussianBlur(img_gray, img_gray, Size(5, 5), 0);


		//����ȭ �̹����� ��ȯ
		adaptiveThreshold(img_gray, img_temp,
			255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 225, 5);
		//threshold(img_gray, img_temp, 130, 255, THRESH_BINARY_INV);


		//������ ���� 
		Mat img_dilate;
		Mat img_erode;
		dilate(img_temp, img_dilate, Mat::ones(Size(3, 3), CV_8UC1), Point(-1, -1));
		erode(img_temp, img_erode, Mat::ones(Size(3, 3), CV_8UC1), Point(-1, -1));

		//contour�� ã�´�.
		vector<vector<Point> > contours;
		findContours(img_temp, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

		imshow("img_erode", img_erode);

		//contour�� �ٻ�ȭ�Ѵ�.
		vector<Point2f> approx;
		img_result = img_input.clone();

		for (size_t i = 0; i < contours.size(); i++)
		{//������ ����(�ܰ���)�� ǥ���ϱ� ���� ������ ã�Ƽ� �� �����ϱ�
			approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.08, true);

			if (fabs(contourArea(Mat(approx))) > 1500)  //������ ����ũ�� �̻��̾�� �Ѵ�.
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
			}
		}
		imshow("result", img_result);	//�� ���� 
		if (waitKey(5) == 27) //ESC Ű ���� �� ���� ���
			break;
	}

	return 0;
}