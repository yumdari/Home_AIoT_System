#include "opencv2/opencv.hpp"
#include "opencv2/highgui//highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{ 
    //Ʈ���� ���� �� ũ�� ����
    namedWindow("ControllWindow", WINDOW_NORMAL);
    resizeWindow("ControllWindow", 380, 300);

    //Ʈ���� �⺻ ���� ��
    int LowH = 179;
    int HighH = 179;
    int LowS = 0;
    int HighS = 255;
    int LowV = 0;
    int HighV = 255;

    //Ʈ���� ���� �� �ִ밪
    createTrackbar("LowH", "ControllWindow", &LowH, 179);
    createTrackbar("HighH", "ControllWindow", &HighH, 179);
    createTrackbar("LowS", "ControllWindow", &LowS, 255);
    createTrackbar("HighS", "ControllWindow", &HighS, 255);
    createTrackbar("LowV", "ControllWindow", &LowV, 255);
    createTrackbar("HighV", "ControllWindow", &HighV, 255);

    Mat  img_input,img_result, img_hsv;
    Mat frame; // OpenCV���� ���� �⺻�� �Ǵ� Matrix ����ü(�̹����� �о� �ش� ������ Mat���·� ��ȯ)
    VideoCapture cap; // ������ �ҷ�����
    cap.open(0); // ������ ����(Camera ����) + ī�޶��ȣ(0(���� �켱))

    if (!cap.isOpened())
    {
        cout << "Error! Cannot open the camera" << endl;
        return -1;
    }
    for (;;)
    {   
        cap.read(img_input);
        //���� Ȯ��
        if (img_input.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        //HSV �̹����� ��ȯ
        cvtColor(img_input, img_hsv, COLOR_BGR2HSV);

        Mat S_mask, S_image;

        Scalar lower = Scalar(LowH, LowS, LowV);
        Scalar upper = Scalar(HighH, HighS, HighV);
 

        inRange(img_hsv, lower, upper, S_mask);  //����ȭ ��
        bitwise_and(img_hsv, img_hsv, S_image, S_mask);

        //�� ä���
        Mat im_floodfill = S_mask.clone();
        floodFill(im_floodfill, cv::Point(0, 0), Scalar(255));

        Mat im_floodfill_inv;
        bitwise_not(im_floodfill, im_floodfill_inv);

        Mat im_out = (S_mask | im_floodfill_inv);

        //contour������ ����Ѵ�. (���,����ȭ �� �̹����� ����)
        vector<vector<Point> > contours;
        findContours(im_floodfill_inv, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        //contour�� �ٻ�ȭ�Ѵ�.
        vector<Point2f> approx;
        img_result = img_input.clone();

        for (size_t i = 0; i < contours.size(); i++)
        {//������ ����(�ܰ���)�� ǥ���ϱ� ���� ������ ã�Ƽ� �� �����ϱ�
            approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.01, true);

            if (fabs(contourArea(Mat(approx))) > 1500)  //������ ����ũ�� �̻��̾�� �Ѵ�.
            {
                int size = approx.size();
                
                //Contour�� �ٻ�ȭ�� ������ �׸���.
                if (size % 2 == 0) {
                    line(img_result, approx[0], approx[approx.size() - 1], Scalar(0, 255, 0), 3);

                    for (int k = 0; k < size - 1; k++)
                        line(img_result, approx[k], approx[k + 1], Scalar(0, 255, 0), 3);

                    //�� ǥ�� �� �׸���
                    for (int k = 0; k < size; k++)
                        circle(img_result, approx[k], 3, Scalar(0, 0, 255));
                }
            }
        }
        imshow("im_floodfill_inv", im_floodfill_inv);
        imshow("result", img_result);
        if (waitKey(5) == 27) //ESC Ű ���� �� ���� ���
            break;
    }
    return 0;
}



