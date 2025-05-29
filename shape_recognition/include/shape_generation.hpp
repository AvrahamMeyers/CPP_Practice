#pragma once

#include <opencv2/opencv.hpp>
#include <random>

constexpr int IMAGE_SIZE = 200;

namespace shapes::generation
{

    cv::Mat generate_basic_image();

    void generate_circle();

    cv::Point generate_point();

    cv::Point generate_point_in_range(int low, int high);

    void add_new_point_to_points(std::vector<cv::Point> &points);

    std::vector<cv::Point> get_triangle_points();

    std::vector<cv::Mat> generate_triangles();

    std::vector<cv::Mat> generate_rectangles();

    int get_random_int(int low, int high);

    double get_random_double(double low, double high);

    std::mt19937 &get_shared_generator();
}