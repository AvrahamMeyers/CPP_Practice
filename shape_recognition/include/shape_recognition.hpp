#include <opencv2/opencv.hpp>

enum Shape
{
    SQUARE,
    TRIANGLE,
    CIRCLE
};

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

cv::Mat generate_basic_image();

cv::Mat load_image(std::string filepath);

std::vector<std::vector<cv::Point>> find_contours(cv::Mat img);

cv::Mat highlight_contours(cv::Mat img, std::vector<std::vector<cv::Point>> contours);

cv::Mat add_contours_to_image(const cv::Mat &shape);

cv::Point generate_point();

void add_new_point_to_points(std::vector<cv::Point> &points);

std::vector<cv::Point> get_triangle_points();

void generate_triangles();

int getRandomInt(int low, int high);