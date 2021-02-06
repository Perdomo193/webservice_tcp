#include "ovtaskimage.h"
#include <QDebug>
#include "opencvmodels.h"

OvTaskImage::OvTaskImage(QJsonObject params): params(params) {}
//cv::Mat src_gray;
//cv::Mat dst, detected_edges;

//int Threshold = 5;
//const int ratio = 3;
//const int kernel_size = 3;

void OvTaskImage::run() {
    QString path = params["path"].toString();
    QString name = params["name"].toString();
    QString exte = params["extension"].toString();
    QString acti = params["action"].toString();

    QString fileNameInput = path + '/' + name;
    QString fileNameOutput = fileNameInput + '-' + acti + '.' + exte;
    fileNameInput += "." + exte;
    image = cv::imread(fileNameInput.toLatin1().data());
    cv::Mat imaouput;

    if (acti == "gray") {
        OpencvModels::applyGray(image,&imaouput);
    } else if (acti == "canny") {
        OpencvModels::applyCanny(image,&imaouput);
    } else if (acti == "circle") {
        OpencvModels::applyCircles(image,&imaouput);
    } else if (acti == "lines") {
        OpencvModels::applyLines(image,&imaouput);
    }
    cv::imwrite(fileNameOutput.toLatin1().data(),imaouput);

    QJsonObject output;
    output.insert("user", params["user"]);
    output.insert("path", path);
    output.insert("name", name + "-" + acti);
    output.insert("extension", exte);
    QJsonDocument docOutput(output);
    emit Response(docOutput.toJson(QJsonDocument::Compact));
}
