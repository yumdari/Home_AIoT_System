#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>


#include <iostream>

using namespace std;
using namespace cv;

int main() {
	string fileName = "faces.jpeg"; // 파일 이름 + 확장자
	Mat img_input;
	VideoCapture cap(0, CAP_DSHOW);

	CascadeClassifier faceCascade;
	faceCascade.load("c:/opencv/build/etc/haarcascades/haarcascade_frontalface_default.xml");

	/* XML 파일 오픈 실패 시 */
	if (faceCascade.empty()) {
		cout << "XML file not opend" << endl;
	}

	/* 사각형 그리기 */
	while (1) {
		cap >> img_input;
		/* 파일 열기 및 3 channel BGR 파일로 변환 */
	//img_input = imread(fileName, IMREAD_COLOR);

	/* 파일 열기 실패 시 */
		if (img_input.empty())
		{
			cout << "Could not open or find the image" << std::endl;
		}

		vector<Rect> faces;
		/* input이미지에서 크기가 다른 object를 검출(detect)하는 함수 */
		faceCascade.detectMultiScale(img_input, faces, 1.1, 3);

		/* 만약 검출이 안되면 faces 벡터의 size 값이 0 */
		/* if faces.size() != 0 then takePicture() */
		//cout << "faces size : " << faces.size() << endl;
		for (int i = 0; i < faces.size(); i++) {
			rectangle(img_input, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
		}

		/* 이미지 출력 */
		imshow("image", img_input);
		if (waitKey(10) == 27) // ESC -> break;
			break;
	}

	return 0;
}