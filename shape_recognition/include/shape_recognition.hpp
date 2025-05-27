#include <opencv2/opencv.hpp>

cv::Mat load_image(std::string filepath);
std::vector<std::vector<cv::Point>> find_contours(cv::Mat img);
cv::Mat highlight_contours(cv::Mat img, std::vector<std::vector<cv::Point>> contours);
void add_contours_to_image(std::string shapeName);
cv::Point generate_point();
void add_new_point_to_points(std::vector<cv::Point> &points);
std::vector<cv::Point> get_triangle_points();
void generate_triangles();

void print_hello();