#include <opencv2/opencv.hpp>
#include <iostream>
#include <unistd.h>

int main() {
    // Buffer to hold the current directory
    char cwd[1024];

    // Get the current directory
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        // Print the current directory
        std::cout << "Current directory: " << cwd << std::endl;
    } else {
        std::cerr << "Error: Unable to get the current directory" << std::endl;
        return 1;
    }

    // Load the image
    cv::Mat image = cv::imread("src/1111.png");

    // Check if the image was loaded successfully
    if (image.empty()) {
        std::cerr << "Error: Unable to load image" << std::endl;
        return 1;
    }

    // Display the original image
    cv::imshow("Original Image", image);
    cv::waitKey(0);

    // Save the image as a new JPEG file
    std::string outputFilename = "output.jpg";
    bool success = cv::imwrite(outputFilename, image);

    // Check if the image was saved successfully
    if (!success) {
        std::cerr << "Error: Unable to save image" << std::endl;
        return 1;
    }

    std::cout << "Image saved as " << outputFilename << std::endl;

    return 0;
}
