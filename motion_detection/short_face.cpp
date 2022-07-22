#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>


#include <iostream>

using namespace std;
using namespace cv;

int main() {
	string fileName = "faces.jpeg"; // ���� �̸� + Ȯ����
	Mat img_input;
	VideoCapture cap(0, CAP_DSHOW);

	CascadeClassifier faceCascade;
	faceCascade.load("c:/opencv/build/etc/haarcascades/haarcascade_frontalface_default.xml");

	/* XML ���� ���� ���� �� */
	if (faceCascade.empty()) {
		cout << "XML file not opend" << endl;
	}

	/* �簢�� �׸��� */
	while (1) {
		cap >> img_input;
		/* ���� ���� �� 3 channel BGR ���Ϸ� ��ȯ */
	//img_input = imread(fileName, IMREAD_COLOR);

	/* ���� ���� ���� �� */
		if (img_input.empty())
		{
			cout << "Could not open or find the image" << std::endl;
		}

		vector<Rect> faces;
		/* input�̹������� ũ�Ⱑ �ٸ� object�� ����(detect)�ϴ� �Լ� */
		faceCascade.detectMultiScale(img_input, faces, 1.1, 3);

		/* ���� ������ �ȵǸ� faces ������ size ���� 0 */
		/* if faces.size() != 0 then takePicture() */
		//cout << "faces size : " << faces.size() << endl;
		for (int i = 0; i < faces.size(); i++) {
			rectangle(img_input, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
		}

		/* �̹��� ��� */
		imshow("image", img_input);
		if (waitKey(10) == 27) // ESC -> break;
			break;
	}

	return 0;
}