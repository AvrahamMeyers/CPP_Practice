#include <opencv2/opencv.hpp>
#include <random>
#include "../include/shape_generation.hpp"

namespace shape::generation
{

    cv::Mat generate_basic_image()
    {
        cv::Mat img(IMAGE_SIZE, IMAGE_SIZE, CV_8UC1, cv::Scalar(0));

        return img;
    }

    void generate_circle()
    {
        cv::Mat img = generate_basic_image();

        // Draw a white circle
        cv::circle(img, cv::Point(100, 100), 40, cv::Scalar(255), -1); // filled circle

        // Save image
        cv::imwrite("circle.png", img);
    }

    cv::Point generate_point()
    {
        return generate_point_in_range(1, IMAGE_SIZE);
    }

    cv::Point generate_point_in_range(int low, int high)
    {
        int x = get_random_int(low, high);
        int y = get_random_int(low, high);

        return cv::Point(x, y);
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

    std::vector<cv::Mat> generate_triangles()
    {
        std::vector<cv::Mat> images{};
        for (int i = 0; i < 10; ++i)
        {
            cv::Mat img = generate_basic_image();
            std::vector<cv::Point> triangle = get_triangle_points();

            cv::fillConvexPoly(img, triangle, cv::Scalar(255));

            images.push_back(img);
        }

        return images;
    }

    std::vector<cv::Mat> generate_rectangles()
    {
        std::vector<cv::Mat> images{};
        for (int i = 0; i < 10; ++i)
        {
            double percentage = get_random_double(0.0, 1.0);
            int distance_from_edge = IMAGE_SIZE / percentage;
            int low = distance_from_edge, high = IMAGE_SIZE - distance_from_edge;

            cv::Mat img = generate_basic_image();

            cv::Point corner = generate_point_in_range(low, high);

            int max_x = IMAGE_SIZE - corner.x;
            int max_y = IMAGE_SIZE - corner.y;

            int x_dim = get_random_int(1, max_x);
            int y_dim = get_random_int(1, max_y);

            cv::Point opp_corner = cv::Point(corner.x + x_dim, corner.y + y_dim);

            cv::rectangle(img, cv::Rect(corner, opp_corner), cv::Scalar(255), -1);

            images.push_back(img);
        }
        return images;
    }

    int get_random_int(int low, int high)
    {
        std::uniform_int_distribution<> dist(low, high);
        return dist(get_shared_generator());
    }

    double get_random_double(double low, double high)
    {
        std::uniform_real_distribution dist(low, high);
        return dist(get_shared_generator());
    }

    std::mt19937 &get_shared_generator()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }
}