// ================================================================
// ===                   FACE RECOGNITION                       ===
// ================================================================

#include <opencv2/opencv.hpp>
#include "opencv2/highgui.hpp"
//#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

String face_cascade_name;
CascadeClassifier face_cascade;

void face_recognition(Mat frame, int* ps, int* pf)
{
    face_cascade_name = "C:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";	// 얼굴 인식 알고리즘 xml path
    if (!face_cascade.load(face_cascade_name)) { printf("--(!)Error loading face cascade\n"); return; };	// 얼굴 인식 알고리즘 open 불가 시 exception

    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY); // 색상 공간 변화를 줄 수 있는 함수. 그레이스케일로 변환함
    equalizeHist(frame_gray, frame_gray);   // 히스토그램 평활화 (영상을 선명하게 함)

    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));    // 영상에서 찾고자하는 객체 검출

    //for (size_t idx = 0; idx < faces.size(); idx++)
    //if (faces.size()) {
        //*ptr = 1;
    for (size_t idx = 0; idx < faces.size(); idx++) {
        rectangle(frame, faces[idx].tl(), faces[idx].br(), Scalar(255, 0, 255), 3); // 시작 좌표와 종료 좌표로 사각형을 그림
        *ps = 1;
        cout << "detected" << endl;
        (*pf)++;
    }
    imshow("window", frame);
}