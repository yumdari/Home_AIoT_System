/*********************************************************
				Heisanbug OpenCV Test
				2020.07.26
				VideoWriter를 이용한 동영상 저장하기
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
	//동영상, 웹캠, RTSP 영상을 불러올 수 있다.
	cv::VideoCapture videoCapture(0);
	cv::VideoWriter videoWriter;

	//영상을 불러오기 실패 시
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

	//영상 저장 셋팅 실패시
	if (!videoWriter.isOpened())
	{
		std::cout << "Can't write video !!! check setting" << std::endl;
		return -1;
	}


	//이미지를 window를 생성하여 보여줍니다.
	cv::namedWindow(VIDEO_WINDOW_NAME);

	//video 재생 시작
	while (true) {
		//VideoCapture로 부터 프래임을 받아온다
		videoCapture >> videoFrame;

		//캡쳐 화면이 없는 경우는 Video의 끝인 경우
		if (videoFrame.empty()) {
			std::cout << "Video END" << std::endl;
		}

		//받아온 Frame을 저장한다.
		videoWriter << videoFrame;
		idx++;
		//window에 frame 출력.
		//cv::imshow(VIDEO_WINDOW_NAME, videoFrame);

		//'ESC'키를 누르면 종료된다.
		//FPS를 이용하여 영상 재생 속도를 조절하여준다.
		if (cv::waitKey(1000 / videoFPS) == 27) {
			std::cout << "Stop video record" << std::endl;
			break;
		}
	}

	//생성하였던 윈도우를 제거합니다.
	cv::destroyWindow(VIDEO_WINDOW_NAME);

	return 0;
}