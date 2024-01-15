#include <opencv2/opencv.hpp>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

int main() {
    // Read your 16-bit image
    cv::Mat img = cv::imread("../../data/1681192260449_infrared_1.tif", cv::IMREAD_UNCHANGED);

    if (img.empty()) {
        std::cerr << "Error loading the image" << std::endl;
        return -1;
    }

    // Calculate histogram
    int histSize = 65536; // Number of bins for 16-bit image
    float range[] = { 0, 65536 };
    const float* histRange = { range };
    cv::Mat hist;

    cv::calcHist(&img, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange);

    // Convert the histogram to a format suitable for matplotlibcpp
    std::vector<double> histData(hist.begin<float>(), hist.end<float>());

    // Plot histogram using matplotlibcpp
    plt::plot(histData);
    plt::title("Histogram");
    plt::xlabel("Pixel Value");
    plt::ylabel("Frequency");
    plt::show();

    return 0;
}

