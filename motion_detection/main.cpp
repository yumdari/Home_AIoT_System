//  Changelog:
//  22.07.26 - devide code(main, functions, header)
//  22.07.25 - optimizate code
//  22.07.22 - integrate into the whole code
//           - combine motion detection with face recognition
//           - modify image capture interval
//           
//  22.07.21 - abbreviate face recognition 
//  22.07.20 - face recognition
//	22.07.19 - motion detection

#include "motion_detection.h"

// ================================================================
// ===                      MAIN FUNCTION                       ===
// ================================================================

int main(int argc, char** argv)
{
    
    VideoCapture cap(0, CAP_DSHOW);	// 내장 camera 설정
                                    // CAP_DSHOW : VideoCapture의 enum 중 하나로, 코드 실행하자마자 direct show
    //VideoWriter videoWriter;

    float videoFPS = cap.get(CAP_PROP_FPS);
    int videoWidth = cap.get(CAP_PROP_FRAME_WIDTH);
    int videoHeight = cap.get(CAP_PROP_FRAME_HEIGHT);

    Mat frame;   // 각 픽셀 위치에 해당하는 BGR 값을 저장함

    cap >> frame;
   
    while (true)
    {
        //videoWriter << frameNew;
        object_detection(frame);
        motion_detection(cap, frame);
        if (waitKey(10) == 27)		// ESC -> break;
            break;
    }
    return 0;
}

