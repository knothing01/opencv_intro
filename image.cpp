#include <opencv2/opencv.hpp>
#include <iostream>
#include <unistd.h>

int main() {
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::cout << "Current directory: " << cwd << std::endl;
    } else {
        std::cerr << "Error: Unable to get the current directory" << std::endl;
        return 1;
    }

    cv::Mat image = cv::imread("src/1111.png");

    if (image.empty()) {
        std::cerr << "Error: Unable to load image" << std::endl;
        return 1;
    }
    
    cv::imshow("Original Image", image);
    cv::waitKey(0);

    std::string outputFilename = "output.jpg";
    bool success = cv::imwrite(outputFilename, image);

    if (!success) {
        std::cerr << "Error: Unable to save image" << std::endl;
        return 1;
    }

    std::cout << "Image saved as " << outputFilename << std::endl;

    return 0;
}
