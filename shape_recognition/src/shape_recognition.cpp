#include <opencv2/opencv.hpp>
#include <random>
#include "../include/shape_recognition.hpp"
#include "../include/shape_generation.hpp"

cv::Mat load_image(std::string filepath)
{
    cv::Mat img = cv::imread(filepath, cv::IMREAD_GRAYSCALE);

    return img;
}

std::vector<std::vector<cv::Point>> find_contours(cv::Mat img)
{
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

    return contours;
}

cv::Mat highlight_contours(cv::Mat img, std::vector<std::vector<cv::Point>> contours)
{
    for (const auto &inner : contours)
    {
        for (cv::Point point : inner)
        {
            img.at<uchar>(point.y, point.x) = 128;
        }
    }
    return img;
}

void save_image_to_file(cv::Mat img, std::string shapeName, Shape shape)
{
    std::string image_path = "images/" + shape_to_folder_name(shape) + "/" + shapeName + ".png";
    cv::imwrite(image_path, img);
}

cv::Mat add_contours_to_image(const cv::Mat &shape)
{
    std::vector<std::vector<cv::Point>> contours = find_contours(shape);

    cv::Mat new_img = highlight_contours(shape, contours);

    return new_img;
}
