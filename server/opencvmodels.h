#ifndef OPENCVMODELS_H
#define OPENCVMODELS_H

#include <QObject>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class OpencvModels {

public:
    OpencvModels();
    static void applyGray(cv::Mat image, cv::Mat *output) {
        cv::Mat src_gray;
        cv::cvtColor(image, src_gray, cv::COLOR_BGR2GRAY);
        *output = src_gray;
    };
    static void applyCanny(cv::Mat image, cv::Mat *output) {
        int lowThreshold = 5;
        const int ratio = 3;
        const int kernel_size = 3;
        cv::Mat src_gray, detected_edges, dst;

        cv::cvtColor(image, src_gray, cv::COLOR_BGR2GRAY);
        cv::blur(src_gray, detected_edges, cv::Size(2,2));
        cv::Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

        dst = cv::Scalar::all(0);
        image.copyTo(dst, detected_edges);
        *output = dst;
    };
    static void applyCircles(cv::Mat image, cv::Mat *output) {
        cv::Mat src_gray;
        cv::cvtColor(image, src_gray, cv::COLOR_BGR2GRAY);
        cv::medianBlur(src_gray, src_gray, 5);
        std::vector<cv::Vec3f> circles;
        cv::HoughCircles(src_gray, circles, cv::HOUGH_GRADIENT, 1, src_gray.rows/2, 100, 30, 1, 30 );
        for( size_t i = 0; i < circles.size(); i++ ) {
            cv::Vec3i c = circles[i];
            cv::Point center = cv::Point(c[0], c[1]);
            circle(image, center, 1, cv::Scalar(0,100,100), 3, cv::LINE_AA);
            int radius = c[2];
            circle(image, center, radius, cv::Scalar(255,0,255), 3, cv::LINE_AA);
        }
        *output = image;
    };
    static void applyLines(cv::Mat image, cv::Mat *output) {

        cv::Mat src_gray, dst;
        cv::Canny( image, dst, 50, 200, 3 );
        cv::cvtColor( dst, src_gray, cv::COLOR_GRAY2BGR );

        std::vector<cv::Vec4i> lines;
        cv::HoughLinesP( dst, lines, 1, CV_PI/180, 80, 30, 10 );
        for( size_t i = 0; i < lines.size(); i++ ) {
            cv::line(src_gray, cv::Point(lines[i][0], lines[i][1]),
            cv::Point( lines[i][2], lines[i][3]), cv::Scalar(0,0,255), 3, 8 );
        }
        *output = src_gray;
    };

    static void drawCircle(cv::Mat image, cv::Point center, int radius);
    static void drawRectangle(cv::Mat image, cv::Point corner_1, cv::Point corner_2);
    static void drawTriangle(cv::Mat image, int cx, int cy, int base, int heigh);
    static void drawPentagone(cv::Mat image, int cx, int cy, int radio);

private:

};

#endif // OPENCVMODELS_H
