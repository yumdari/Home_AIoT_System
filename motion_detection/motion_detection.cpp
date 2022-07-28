#include <opencv2/opencv.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

int face_recognition(Mat frame, int* ps, int* pf);	// face recognition header

void motion_detection(VideoCapture cap, Mat frameOld) {

    int status = 0;
    int* ps = &status;
    int flag = 0;
    int* pf = &flag;

	Mat frameNew;
	Mat frameDiff;  // 각 픽셀 위치에 해당하는 BGR 값을 저장함

	double min, max;
	int sensitivity = 170;	// 동작 감지 민감도
	int detectionCount = 0;

	cap >> frameNew;

	if (frameNew.empty())	// if input frame is empty, would break;
		return;

	absdiff(frameNew, frameOld, frameDiff); // 배경 영상과 현재 프레임 영상의 차이를 구함
	cvtColor(frameDiff, frameDiff, COLOR_BGR2GRAY); // 색상 공간 변화를 줄 수 있는 함수. 그레이스케일로 변환함 
	minMaxLoc(frameDiff, &min, &max);   // 주어진 행렬의 최솟값, 최댓값을 찾음

	if (frameNew.empty())	// if input frame is empty, would break;
	{
		printf(" --(!) No capd frame -- Break!");
		return;
	}

    if ((max > sensitivity))
    {
        /*cout << "Motion detected. (Max: " << max << ")" << endl;*/

        // For PNG, it can be the compression level from 0 to 9.
        // A higher value means a smaller size and longer compression time.
        vector<int> compression_params;
        compression_params.push_back(IMWRITE_PNG_COMPRESSION);	   //PNG 압축레벨 저장
        compression_params.push_back(3);
        //if (imwrite(format("detection_%03d.png", detectionCount++), frameNew, compression_params))
        if (status && (*pf) % 20 == 0) {
            imwrite(format("C:\\Users\\KCCI28\\Documents\\GitHub\\Reminder_Door\\motion_detection\\pictures\\detection_%03d.png", detectionCount++), frameNew, compression_params);


            status = 0;
            flag = 0;
        }



        face_recognition(frameNew, ps, pf);

        char c = (char)waitKey(10);
        if (c == 27) {
            return;
        }
    }
    frameNew.copyTo(frameOld);	// frameNew copy to frameOld
}
