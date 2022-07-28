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
    face_cascade_name = "C:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";	// �� �ν� �˰��� xml path
    if (!face_cascade.load(face_cascade_name)) { printf("--(!)Error loading face cascade\n"); return; };	// �� �ν� �˰��� open �Ұ� �� exception

    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY); // ���� ���� ��ȭ�� �� �� �ִ� �Լ�. �׷��̽����Ϸ� ��ȯ��
    equalizeHist(frame_gray, frame_gray);   // ������׷� ��Ȱȭ (������ �����ϰ� ��)

    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));    // ���󿡼� ã�����ϴ� ��ü ����

    //for (size_t idx = 0; idx < faces.size(); idx++)
    //if (faces.size()) {
        //*ptr = 1;
    for (size_t idx = 0; idx < faces.size(); idx++) {
        rectangle(frame, faces[idx].tl(), faces[idx].br(), Scalar(255, 0, 255), 3); // ���� ��ǥ�� ���� ��ǥ�� �簢���� �׸�
        *ps = 1;
        cout << "detected" << endl;
        (*pf)++;
    }
    imshow("window", frame);
}