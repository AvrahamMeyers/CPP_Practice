#include <opencv2/opencv.hpp>
#include <random>
#include "../include/shape_recognition.hpp"

void generate_circle()
{
    int width = 200, height = 200;
    cv::Mat img(height, width, CV_8UC1, cv::Scalar(0));

    // Draw a white circle
    cv::circle(img, cv::Point(100, 100), 40, cv::Scalar(255), -1); // filled circle

    // Save image
    cv::imwrite("circle.png", img);
}

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

void add_contours_to_image(std::string shapeName)
{
    std::string image_path = "images/" + shapeName + ".png";

    cv::Mat shape = load_image(image_path);

    std::vector<std::vector<cv::Point>> contours = find_contours(shape);

    cv::Mat new_img = highlight_contours(shape, contours);

    cv::imwrite("images/new_" + shapeName + ".png", new_img);
}

int generate_random_number(int low, int high)
{
    // TODO: implement random generator for given range
}

cv::Point generate_point()
{
    static std::random_device rd;                        // Seed
    static std::mt19937 gen(rd());                       // Mersenne Twister engine
    static std::uniform_int_distribution<> dist(1, 200); // Range [1, 10]

    int x = dist(gen);
    int y = dist(gen);
    cv::Point point(x, y);

    return point;
}

void add_new_point_to_points(std::vector<cv::Point> &points)
{
    cv::Point point = generate_point();
    while (std::find(points.begin(), points.end(), point) != points.end())
    {
        point = generate_point();
    }
    points.push_back(point);
}

std::vector<cv::Point> get_triangle_points()
{
    std::vector<cv::Point> points{};

    while (points.size() < 3)
    {
        add_new_point_to_points(points);
    }
    return points;
}

void generate_triangles()
{
    for (int i = 0; i < 10; ++i)
    {
        int width = 200, height = 200;
        cv::Mat img(height, width, CV_8UC1, cv::Scalar(0));
        std::vector<cv::Point> triangle = get_triangle_points();

        cv::fillConvexPoly(img, triangle, cv::Scalar(255));

        std::string filename = "triangle_" + std::to_string(i);

        cv::imwrite("images/" + filename + ".png", img);
    }
}

void generate_rectangles()
{
    for (int i = 0; i < 10; ++i)
    {
        // TODO: implement generate rectangle logic
    }
}

void print_hello()
{
    printf("hello world");
}
