// Changelog:
//  22.07.22 - face recognite after motion detection 
//  22.07.21 - abbreviate face recognition 
//  22.07.20 - face recognition
//	22.07.19 - motion detection

#include <opencv2/opencv.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

void face_recognition(Mat frame, int*ptr);	// face recognition header

String face_cascade_name;
CascadeClassifier face_cascade;


// ================================================================
// ===                      MAIN FUNCTION                       ===
// ================================================================

int main(int argc, char** argv)
{
    face_cascade_name = "C:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";	// 얼굴 인식 알고리즘 xml path
    if (!face_cascade.load(face_cascade_name)) { printf("--(!)Error loading face cascade\n"); return -1; };	// 얼굴 인식 알고리즘 open 불가 시 exception

    VideoCapture cap(0, CAP_DSHOW);	// 내장 camera 설정
                                    // CAP_DSHOW : VideoCapture의 enum 중 하나로, 코드 실행하자마자 direct show
    // 각 픽셀 위치에 해당하는 BGR 값을 저장함
    Mat frameNew;
    Mat frameOld;   // 각 픽셀 위치에 해당하는 BGR 값을 저장함
    Mat frameDiff;  // 각 픽셀 위치에 해당하는 BGR 값을 저장함

    double min, max;
    int sensitivity = 130;	// 동작 감지 민감도
    int detectionCount = 0;

    int status = 0;
    int* ptr = &status;

    cap >> frameOld;	// 

    while (true)
    {
        cap >> frameNew;
        if (frameNew.empty())	// if input frame is empty, would break;
            break;

        // Calculates the per-element absolute difference
        // between two arrays or between an array and a scalar.
        absdiff(frameNew, frameOld, frameDiff);
        cvtColor(frameDiff, frameDiff, COLOR_BGR2GRAY);
        minMaxLoc(frameDiff, &min, &max);

        if ((max > sensitivity))
        {
            /*cout << "Motion detected. (Max: " << max << ")" << endl;*/

            // For PNG, it can be the compression level from 0 to 9.
            // A higher value means a smaller size and longer compression time.
            vector<int> compression_params;
            compression_params.push_back(IMWRITE_PNG_COMPRESSION);
            compression_params.push_back(3);
            //if (imwrite(format("detection_%03d.png", detectionCount++), frameNew, compression_params))
            if (status) {
                imwrite(format("detection_%03d.png", detectionCount++), frameNew, compression_params);
                status = 0;
            }

            if (frameNew.empty())	// if input frame is empty, would break;
            {
                printf(" --(!) No capd frame -- Break!");
                break;
            }

            face_recognition(frameNew, ptr);

            char c = (char)waitKey(10);
            if (c == 27) {
                break;
            }
        }
        frameNew.copyTo(frameOld);	// frameNew copy to frameOld

        if (waitKey(10) == 27)		// ESC -> break;
            break;
    }
    return 0;
}

// ================================================================
// ===                   FACE RECOGNITION                       ===
// ================================================================

void face_recognition(Mat frame, int*ptr)
{
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    //for (size_t idx = 0; idx < faces.size(); idx++)
	if (faces.size())
        *ptr = 1;
    cout << "detected" << endl;
}
