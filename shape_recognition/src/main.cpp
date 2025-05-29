#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include "../include/shape_recognition.hpp"
#include "../include/shape_generation.hpp"

void generate_shapes()
{
    int width = 200, height = 200;
    cv::Mat img(height, width, CV_8UC1, cv::Scalar(0)); // All black background

    std::vector<cv::Point> square = {
        cv::Point(50, 50),
        cv::Point(50, 150),
        cv::Point(150, 150),
        cv::Point(150, 50)};
    cv::fillConvexPoly(img, square, cv::Scalar(255));
    // Save image
    cv::imwrite("images/square.png", img);
}

int main()
{
    printf("hello\n");

    int randomInt = 6;

    printf("random int: %d\n", randomInt);

    return 0;
}