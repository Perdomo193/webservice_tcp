#include "opencvmodels.h"
#include <QDebug>

OpencvModels::OpencvModels() {}

void OpencvModels::drawCircle(cv::Mat image, cv::Point center, int radius) {
    cv::circle(image, center, radius, cv::Scalar(230,100,120), 4);
};

void OpencvModels::drawRectangle(cv::Mat image, cv::Point corner_1, cv::Point corner_2) {
    cv::rectangle(image, corner_1, corner_2, cv::Scalar(255,50,40), 4);
};

void OpencvModels::drawTriangle(cv::Mat image, int cx, int cy, int base, int heigh) {
    cv::Point c1(cx-static_cast<int>(base/2),cy-static_cast<int>(heigh/2));
    cv::Point c2(cx,cy+static_cast<int>(heigh/2));
    cv::Point c3(cx+static_cast<int>(base/2),cy-static_cast<int>(heigh/2));

    std::vector<cv::Point> contour{c1,c2,c3};
    int npts = cv::Mat(contour).rows;
    const cv::Point *pts = (const cv::Point*) cv::Mat(contour).data;
    cv::polylines(image, &pts, &npts, 1, true, cv::Scalar(255, 0, 0), 3);
};

void OpencvModels::drawPentagone(cv::Mat image, int cx, int cy, int apotema) {
    int h = static_cast<int>(std::sqrt(0.75 * std::pow(apotema,2)));

    cv::Point c1(cx-apotema,cy);
    cv::Point c2(cx-static_cast<int>(apotema/2),cy-h);
    cv::Point c3(cx+static_cast<int>(apotema/2),cy-h);
    cv::Point c4(cx+apotema,cy);
    cv::Point c5(cx+static_cast<int>(apotema/2),cy+h);
    cv::Point c6(cx-static_cast<int>(apotema/2),cy+h);

    std::vector<cv::Point> contour{c1,c2,c3,c4,c5,c6};

    int npts = cv::Mat(contour).rows;
    const cv::Point *pts = (const cv::Point*) cv::Mat(contour).data;
    cv::polylines(image, &pts, &npts, 1, true, cv::Scalar(255, 0, 0),3);
};

