#include <iostream>
#include <opencv2/opencv.hpp>

void detectAndDraw(cv::Mat& img, cv::CascadeClassifier& classifier, double scale = 1.3) {

    std::vector<cv::Scalar> colors = {
        cv::Scalar(255, 0, 0),   // Blue
        cv::Scalar(255, 128, 0), // Orange
        cv::Scalar(255, 255, 0), // Yellow
        cv::Scalar(0, 255, 0)    // Green
    };

  
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    cv::resize(gray, gray, cv::Size(), 1.0 / scale, 1.0 / scale);
    cv::equalizeHist(gray, gray);

    // DETECT OBJECTS IF ANY
    std::vector<cv::Rect> objects;
    classifier.detectMultiScale(
        gray,       
        objects,    
        1.1,       
        5,    //ngbh     
        0,         
        cv::Size(30, 30)
    );

    for (size_t i = 0; i < objects.size(); ++i) {
        cv::Rect r = objects[i];
        //filter out small detections
        if (r.width * r.height < 1000) //adjust this threshold as needed
            continue;
        cv::rectangle(img, cv::Point(cvRound(r.x * scale), cvRound(r.y * scale)),
                      cv::Point(cvRound((r.x + r.width - 1) * scale), cvRound((r.y + r.height - 1) * scale)),
                      colors[i % colors.size()], 2);
    }
}


int main() {
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Cannot open webcam." << std::endl;
        return -1;
    }

    cv::CascadeClassifier classifier;
    if (!classifier.load("/Users/michael/Desktop/mars/opn/haarcascade_frontalface_default.xml")) {
        std::cerr << "Error: Cannot load classifier." << std::endl;
        return -1;
    }

    cv::Mat frame;
    std::string window = "Face Recognition";

    while (true) {
        cap >> frame;
        if (frame.empty())
            break;

        detectAndDraw(frame, classifier);

        cv::imshow(window, frame);

        int key = cv::waitKey(1);
        if (key == 'q')
            break;
    }

    return 0;
}
