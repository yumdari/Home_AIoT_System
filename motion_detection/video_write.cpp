/*********************************************************
				Heisanbug OpenCV Test
				2020.07.26
				VideoWriter�� �̿��� ������ �����ϱ�
				Alta software developer
**********************************************************/

//C++ header file 
#include <iostream>

//opencv header file include
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"


#define VIDEO_PATH "vtest.avi"
#define WEBCAM_NUM 0
//https://www.wowza.com/html/mobile.html
#define RTSP_URL "rtsp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mov"

#define OUTPUT_VIDEO_NAME "out.avi"

#define VIDEO_WINDOW_NAME "video"


//project main function
int main(int argc, char** argv) {

	//opencv videocapture class
	//������, ��ķ, RTSP ������ �ҷ��� �� �ִ�.
	cv::VideoCapture videoCapture(0);
	cv::VideoWriter videoWriter;

	//������ �ҷ����� ���� ��
	if (!videoCapture.isOpened()) {
		std::cout << "Can't open video !!!" << std::endl;
		return -1;
	}

	//OpenCV Mat class
	cv::Mat videoFrame;


	float videoFPS = videoCapture.get(cv::CAP_PROP_FPS);
	int videoWidth = videoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
	int videoHeight = videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);

	std::cout << "Video Info" << std::endl;
	std::cout << "video FPS : " << videoFPS << std::endl;
	std::cout << "video width : " << videoWidth << std::endl;
	std::cout << "video height : " << videoHeight << std::endl;

	int idx = 0;
	//OpenCV VideoWriter setting
	//codec info
	//https://thebook.io/006939/ch04/01/04-02/
	if ((idx % 1000) == 0) {
		videoWriter.open(OUTPUT_VIDEO_NAME, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
			videoFPS, cv::Size(videoWidth, videoHeight), true);
	}

	//���� ���� ���� ���н�
	if (!videoWriter.isOpened())
	{
		std::cout << "Can't write video !!! check setting" << std::endl;
		return -1;
	}


	//�̹����� window�� �����Ͽ� �����ݴϴ�.
	cv::namedWindow(VIDEO_WINDOW_NAME);

	//video ��� ����
	while (true) {
		//VideoCapture�� ���� �������� �޾ƿ´�
		videoCapture >> videoFrame;

		//ĸ�� ȭ���� ���� ���� Video�� ���� ���
		if (videoFrame.empty()) {
			std::cout << "Video END" << std::endl;
		}

		//�޾ƿ� Frame�� �����Ѵ�.
		videoWriter << videoFrame;
		idx++;
		//window�� frame ���.
		//cv::imshow(VIDEO_WINDOW_NAME, videoFrame);

		//'ESC'Ű�� ������ ����ȴ�.
		//FPS�� �̿��Ͽ� ���� ��� �ӵ��� �����Ͽ��ش�.
		if (cv::waitKey(1000 / videoFPS) == 27) {
			std::cout << "Stop video record" << std::endl;
			break;
		}
	}

	//�����Ͽ��� �����츦 �����մϴ�.
	cv::destroyWindow(VIDEO_WINDOW_NAME);

	return 0;
}