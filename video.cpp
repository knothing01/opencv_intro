#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    // Open the video file
    VideoCapture cap("src/2222.mov");
    if (!cap.isOpened()) {
        std::cerr << "Error opening video file\n";
        return -1;
    }

    namedWindow("Video", WINDOW_NORMAL);

    while (true) {
        Mat frame;
        cap >> frame;

        if (frame.empty()) {
            std::cout << "End of video\n";
            break;
        }

        imshow("Video", frame);


        if (waitKey(30) == 'q') {
            break;
        }
    }


    cap.release();
    destroyAllWindows();

    return 0;
}
