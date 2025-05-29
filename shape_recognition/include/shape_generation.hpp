#ifndef SHAPE_GENERATION_HPP
#define SHAPE_GENERATION_HPP

#include <opencv2/opencv.hpp>

cv::Mat generate_basic_image();

void generate_circle();

cv::Point generate_point();

void add_new_point_to_points(std::vector<cv::Point> &points);

std::vector<cv::Point> get_triangle_points();

void generate_triangles();

void generate_rectangles();

int getRandomInt(int low, int high);
#endif