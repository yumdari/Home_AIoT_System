#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    VideoCapture cap(0);

    Mat frameNew;
    Mat frameOld;
    Mat frameDiff;

    double min, max;
    int sensitivity = 100;
    int detectionCount = 0;

    cap >> frameOld;

    while (true)
    {
        cap >> frameNew;
        if (frameNew.empty())
            break;

        // Calculates the per-element absolute difference
        // between two arrays or between an array and a scalar.
        absdiff(frameNew, frameOld, frameDiff);
        cvtColor(frameDiff, frameDiff, COLOR_BGR2GRAY);
        minMaxLoc(frameDiff, &min, &max);

        if (max > sensitivity)
        {
            cout << "Motion detected. (Max: " << max << ")" << endl;

            // For PNG, it can be the compression level from 0 to 9.
            // A higher value means a smaller size and longer compression time.
            vector<int> compression_params;
            compression_params.push_back(IMWRITE_PNG_COMPRESSION);
            compression_params.push_back(3);
                        if (imwrite(format("detection_%03d.png", detectionCount++), frameNew, compression_params))
                            cout << "Image saved." << endl;
                        else
                            cout << "Image not saved." << endl;

        }



        imshow("Motion Detectoion", frameDiff);

        frameNew.copyTo(frameOld);

        if (waitKey(10) == 27)
            break;
    }

    return 0;
}