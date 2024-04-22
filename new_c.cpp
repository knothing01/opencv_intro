#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat apply_effect(Mat frame, char effect) {
    Mat result;
    switch(effect) {
        case 'v':
            flip(frame, result, 0);
            break;
        case 'h':
            flip(frame, result, 1);
            break;
        case 'r':
            transpose(frame, result);
            flip(result, result, 1);
            break;
        case 'g':
            cvtColor(frame, result, COLOR_BGR2GRAY);
            break;
        case 'b':
            blur(frame, result, Size(15, 15));
            break;
        case 'm':
            medianBlur(frame, result, 15);
            break;
        default:
            result = frame.clone();
    }
    return result;
}

// Main function
int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Error: Cannot open webcam." << endl;
        return -1;
    }

    char active_effect = 0;
    Mat frame;
    string windowName = "Video";
    namedWindow(windowName);

    while (true) {
        cap >> frame;
        if (frame.empty())
            break;

        if (active_effect)
            frame = apply_effect(frame, active_effect);

        time_t now = time(0);
        tm *ltm = localtime(&now);
        char current_time[10];
        strftime(current_time, sizeof(current_time), "%H:%M:%S", ltm);

        putText(frame, "Effect: " + string(1, active_effect), Point(10, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
        putText(frame, "Time: " + string(current_time), Point(10, 70), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);

        imshow(windowName, frame);

        int key = waitKey(1);
        if (key == 'q')
            break;
        else if (key == 'v' || key == 'h' || key == 'r' || key == 'g' || key == 'b' || key == 'm')
            active_effect = static_cast<char>(key);
    }

    cap.release();
    destroyAllWindows();
    return 0;
}
