#pragma once
#include <opencv2/opencv.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

//#define OUTPUT_VIDEO_NAME "out.avi"

using namespace std;
using namespace cv;

void object_detection(Mat frameOld);
void motion_detection(VideoCapture cap, Mat frame);
void face_recognition(Mat frame, int* ps, int* pf);	// face recognition header

int status = 0;
int* ps = &status;
int flag = 0;
int* pf = &flag;