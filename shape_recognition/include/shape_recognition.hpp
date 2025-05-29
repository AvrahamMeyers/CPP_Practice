#pragma once
#include <opencv2/opencv.hpp>

enum Shape
{
    SQUARE,
    TRIANGLE,
    CIRCLE
};

std::string shape_to_folder_name(Shape shape);

std::vector<std::vector<cv::Point>> find_contours(cv::Mat img);

cv::Mat highlight_contours(cv::Mat img, std::vector<std::vector<cv::Point>> contours);

cv::Mat add_contours_to_image(const cv::Mat &shape);

cv::Mat load_image(std::string filePath);

void save_image_to_file(cv::Mat img, std::string shapeName, Shape shape);

std::vector<cv::Mat> load_images_from_folder(std::string folderPath);

void save_images_to_folder(std::vector<std::pair<cv::Mat, Shape>> images);