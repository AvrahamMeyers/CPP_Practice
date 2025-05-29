#pragma once

#include <opencv2/opencv.hpp>

constexpr int IMAGE_SIZE = 200;

cv::Mat generate_basic_image();

void generate_circle();

cv::Point generate_point();

void add_new_point_to_points(std::vector<cv::Point> &points);

std::vector<cv::Point> get_triangle_points();

void generate_triangles();

void generate_rectangles();

int get_random_int(int low, int high);
