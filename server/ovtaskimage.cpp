#include "ovtaskimage.h"
#include <QDebug>

OvTaskImage::OvTaskImage(QJsonObject params): params(params) {}
cv::Mat src_gray;
cv::Mat dst, detected_edges;

int lowThreshold = 5;
const int ratio = 3;
const int kernel_size = 3;

void OvTaskImage::run() {
    QString path = params["path"].toString();
    QString name = params["name"].toString();
    QString exte = params["extension"].toString();
    QString acti = params["action"].toString();

    QString fileNameInput = path + '/' + name;
    QString fileNameOutput = fileNameInput + '-' + acti + '.' + exte;
    fileNameInput += "." + exte;
    image = cv::imread(fileNameInput.toLatin1().data());
    cv::cvtColor(image, src_gray, cv::COLOR_BGR2GRAY);

    if (acti == "gray") {
        cv::imwrite(fileNameOutput.toLatin1().data(),src_gray);
    } else if (acti == "canny") {
        cv::cvtColor(image, src_gray, cv::COLOR_BGR2GRAY);
        cv::blur(src_gray, detected_edges, cv::Size(2,2));
        cv::Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
        dst = cv::Scalar::all(0);
        image.copyTo(dst, detected_edges);
        cv::imwrite(fileNameOutput.toLatin1().data(),dst);
    } else if (acti == "circle") {
        medianBlur(src_gray, src_gray, 5);
        std::vector<cv::Vec3f> circles;
        HoughCircles(src_gray, circles, cv::HOUGH_GRADIENT, 1, src_gray.rows/2, 100, 30, 1, 30 );
        for( size_t i = 0; i < circles.size(); i++ ) {
            cv::Vec3i c = circles[i];
            cv::Point center = cv::Point(c[0], c[1]);
            circle(image, center, 1, cv::Scalar(0,100,100), 3, cv::LINE_AA);
            int radius = c[2];
            circle(image, center, radius, cv::Scalar(255,0,255), 3, cv::LINE_AA);
        }
        cv::imwrite(fileNameOutput.toLatin1().data(),image);
    } else if (acti == "lines") {
        cv::Canny( image, dst, 50, 200, 3 );
        cv::cvtColor( dst, src_gray, cv::COLOR_GRAY2BGR );

        std::vector<cv::Vec4i> lines;
        HoughLinesP( dst, lines, 1, CV_PI/180, 80, 30, 10 );
        for( size_t i = 0; i < lines.size(); i++ ) {
            cv::line(src_gray, cv::Point(lines[i][0], lines[i][1]),
            cv::Point( lines[i][2], lines[i][3]), cv::Scalar(0,0,255), 3, 8 );
        }
        cv::imwrite(fileNameOutput.toLatin1().data(),src_gray);
    }

    QJsonObject output;
    output.insert("user", params["user"]);
    output.insert("path", path);
    output.insert("name", name + "-" + acti);
    output.insert("extension", exte);
    QJsonDocument docOutput(output);
    emit Response(docOutput.toJson(QJsonDocument::Compact));
}
