#include <opencv2/opencv.hpp>
#include <random>
#include "../include/shape_recognition.hpp"
#include "../include/shape_generation.hpp"
#include <filesystem>
namespace fs = std::filesystem;

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

cv::Mat add_contours_to_image(const cv::Mat &shape)
{
    std::vector<std::vector<cv::Point>> contours = find_contours(shape);

    cv::Mat new_img = highlight_contours(shape, contours);

    return new_img;
}

cv::Mat load_image(std::string filePath)
{
    cv::Mat img = cv::imread(filePath, cv::IMREAD_GRAYSCALE);

    return img;
}

void save_image_to_file(cv::Mat img, std::string shapeName, Shape shape)
{
    std::string image_path = "images/" + shape_to_folder_name(shape) + "/" + shapeName + ".png";
    cv::imwrite(image_path, img);
}

std::string shape_to_folder_name(Shape shape)
{
    switch (shape)
    {
    case Shape::SQUARE:
        return "rectangles";
    case Shape::CIRCLE:
        return "circles";
    case Shape::TRIANGLE:
        return "triangles";
    default:
        return "unknown";
    }
}

std::vector<cv::Mat> load_images_from_folder(std::string folderPath)
{
    std::vector<cv::Mat> images{};
    for (const auto &entry : fs::recursive_directory_iterator(folderPath))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".png")
        {
            cv::Mat img = load_image(entry.path().string());
            images.push_back(img);
        }
    }
    return images;
}

void save_images_to_folder(std::vector<std::pair<cv::Mat, Shape>> images)
{
    for (const auto &[img, shape] : images)
    {
        std::string shapeName = shape_to_folder_name(shape) + std::to_string(shapes::generation::get_random_int(1, 1000));
        save_image_to_file(img, shapeName, shape);
    }
}