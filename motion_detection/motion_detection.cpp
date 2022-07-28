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
	Mat frameDiff;  // �� �ȼ� ��ġ�� �ش��ϴ� BGR ���� ������

	double min, max;
	int sensitivity = 170;	// ���� ���� �ΰ���
	int detectionCount = 0;

	cap >> frameNew;

	if (frameNew.empty())	// if input frame is empty, would break;
		return;

	absdiff(frameNew, frameOld, frameDiff); // ��� ����� ���� ������ ������ ���̸� ����
	cvtColor(frameDiff, frameDiff, COLOR_BGR2GRAY); // ���� ���� ��ȭ�� �� �� �ִ� �Լ�. �׷��̽����Ϸ� ��ȯ�� 
	minMaxLoc(frameDiff, &min, &max);   // �־��� ����� �ּڰ�, �ִ��� ã��

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
        compression_params.push_back(IMWRITE_PNG_COMPRESSION);	   //PNG ���෹�� ����
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
