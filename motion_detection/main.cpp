// Changelog:
//  22.07.22 - face recognition after motion detection 
//           - modify image capture interval
//  22.07.21 - abbreviate face recognition 
//  22.07.20 - face recognition
//	22.07.19 - motion detection

#include <opencv2/opencv.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#define OUTPUT_VIDEO_NAME "out.avi"

using namespace std;
using namespace cv;

void face_recognition(Mat frame, int*ps, int*pf);	// face recognition header

String face_cascade_name;
CascadeClassifier face_cascade;


// ================================================================
// ===                      MAIN FUNCTION                       ===
// ================================================================

int main(int argc, char** argv)
{
    face_cascade_name = "C:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";	// �� �ν� �˰��� xml path
    if (!face_cascade.load(face_cascade_name)) { printf("--(!)Error loading face cascade\n"); return -1; };	// �� �ν� �˰��� open �Ұ� �� exception

    VideoCapture cap(0, CAP_DSHOW);	// ���� camera ����
                                    // CAP_DSHOW : VideoCapture�� enum �� �ϳ���, �ڵ� �������ڸ��� direct show
    VideoWriter videoWriter;

    float videoFPS = cap.get(CAP_PROP_FPS);
    int videoWidth = cap.get(CAP_PROP_FRAME_WIDTH);
    int videoHeight = cap.get(CAP_PROP_FRAME_HEIGHT);

    int rectangle = 0;
    Mat img_input, img_result, img_gray, img_erode, img_dilate;

    // �� �ȼ� ��ġ�� �ش��ϴ� BGR ���� ������
    Mat frameNew;
    Mat frameOld;   // �� �ȼ� ��ġ�� �ش��ϴ� BGR ���� ������
    Mat frameDiff;  // �� �ȼ� ��ġ�� �ش��ϴ� BGR ���� ������

    double min, max;
    int sensitivity = 170;	// ���� ���� �ΰ���
    int detectionCount = 0;

    int status = 0;
    int* ps = &status;
    int flag = 0;
    int* pf = &flag;

    cap >> frameOld;	// 
   
    while (true)
    {
        cap >> frameNew;
        videoWriter << frameNew;

        if (frameNew.empty())	// if input frame is empty, would break;
            break;


        //�׷��̽����� �̹����� ��ȯ
        cvtColor(frameNew, img_gray, COLOR_BGR2GRAY);
        GaussianBlur(img_gray, img_gray, Size(5, 5), 0, 0);
        //����ȭ �̹����� ��ȯ
        threshold(img_gray, img_gray, 200, 255, THRESH_BINARY);

        //������ ���� (�������� ��� ����������
        erode(img_gray, img_erode, Mat::ones(Size(5, 5), CV_8UC1), Point(-1, -1));
        dilate(img_erode, img_dilate, Mat::ones(Size(5, 5), CV_8UC1), Point(-1, -1));
        //�������� ���� ������ ����
        dilate(img_dilate, img_dilate, Mat::ones(Size(5, 5), CV_8UC1), Point(-1, -1));
        erode(img_dilate, img_erode, Mat::ones(Size(5, 5), CV_8UC1), Point(-1, -1));

        //���� �� ä���
        Mat im_floodfill = img_erode.clone();
        floodFill(im_floodfill, Point(0, 0), Scalar(255));
        Mat im_floodfill_inv;
        bitwise_not(im_floodfill, im_floodfill_inv);
        Mat im_out = (img_erode | im_floodfill_inv);

        //contour�� ã�´�.
        vector<vector<Point> > contours;
        findContours(im_out, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        //contour�� �ٻ�ȭ�Ѵ�.
        vector<Point2f> approx;
        img_result = frameNew.clone();
        /////////////////
        for (size_t i = 0; i < contours.size(); i++)
        {//������ ����(�ܰ���)�� ǥ���ϱ� ���� ������ ã�Ƽ� �� �����ϱ�
            approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.01, true);
            if (fabs(contourArea(Mat(approx))) > 1000)
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
                if (size > 4)//������ �� ���� 
                    rectangle = 1;    //�簢���̸� ++
                else
                    rectangle = 0;
            }
        }
        imshow("result", img_result);	//�� ���� 
        imshow("im_out", im_out);

        absdiff(frameNew, frameOld, frameDiff);
        cvtColor(frameDiff, frameDiff, COLOR_BGR2GRAY);
        minMaxLoc(frameDiff, &min, &max);

        if ((max > sensitivity))
        {
            /*cout << "Motion detected. (Max: " << max << ")" << endl;*/

            // For PNG, it can be the compression level from 0 to 9.
            // A higher value means a smaller size and longer compression time.
            vector<int> compression_params;
            compression_params.push_back(IMWRITE_PNG_COMPRESSION);	   //PNG ���෹�� ����
            compression_params.push_back(3);
            //if (imwrite(format("detection_%03d.png", detectionCount++), frameNew, compression_params))
            if (status&&(*pf)%20==0) {
                imwrite(format("C:\\Users\\KCCI28\\Documents\\GitHub\\Reminder_Door\\motion_detection\\pictures\\detection_%03d.png", detectionCount++), frameNew, compression_params);
                
               
                status = 0;
                flag = 0;
            }

            if (frameNew.empty())	// if input frame is empty, would break;
            {
                printf(" --(!) No capd frame -- Break!");
                break;
            }

            face_recognition(frameNew, ps, pf);

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

void face_recognition(Mat frame, int*ps, int * pf)
{
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    //for (size_t idx = 0; idx < faces.size(); idx++)
    //if (faces.size()) {
        //*ptr = 1;
    for (size_t idx = 0; idx < faces.size(); idx++){
    rectangle(frame, faces[idx].tl(), faces[idx].br(), Scalar(255, 0, 255), 3);
    *ps = 1;
        cout << "detected" << endl;
        (*pf)++;
    }
    imshow("window", frame);
}