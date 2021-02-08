#include "ovtaskimage.h"
#include <QDebug>
#include "opencvmodels.h"

OvTaskImage::OvTaskImage(QJsonObject params): params(params) {}

void OvTaskImage::run() {
    QString path = params["path"].toString();
    QString name = params["name"].toString();
    QString exte = params["extension"].toString();
    QString acti = params["action"].toString();

    QString fileNameInput = path + '/' + name;
    QString fileNameOutput = fileNameInput + '-' + acti + '.' + exte;
    fileNameInput += "." + exte;

    image = cv::imread(fileNameInput.toLatin1().data());
    bool status = false;

    cv::Mat imaouput;
    if (image.cols > 0 and image.rows > 0) {
        if (acti == "gray") {
            OpencvModels::applyGray(image,&imaouput);
        } else if (acti == "canny") {
            OpencvModels::applyCanny(image,&imaouput);
        } else if (acti == "circle") {
            OpencvModels::applyCircles(image,&imaouput);
        } else if (acti == "lines") {
            OpencvModels::applyLines(image,&imaouput);
        } else if (acti == "drectangle") {
            OpencvModels::drawRectangle(image,cv::Point(params["c_1"].toInt(),params["c_2"].toInt()),cv::Point(params["c_3"].toInt(),params["c_4"].toInt()));
        } else if (acti == "dtriangle") {
            OpencvModels::drawTriangle(image,params["c_1"].toInt(),params["c_2"].toInt(),params["c_3"].toInt(),params["c_4"].toInt());
        } else if (acti == "dhexagon") {
            OpencvModels::drawPentagone(image,params["c_1"].toInt(),params["c_2"].toInt(),params["c_3"].toInt());
        } else if (acti == "dcircle") {
            OpencvModels::drawCircle(image,cv::Point(params["c_1"].toInt(),params["c_2"].toInt()),params["c_3"].toInt());
        }
        if ((image.cols > 0 && image.rows >0) || (imaouput.cols > 0 && imaouput.rows > 0)) status = true;
    }

    QJsonObject output;
    if (status) {
        if (imaouput.rows > 0 and imaouput.cols > 0) {
            cv::imwrite(fileNameOutput.toLatin1().data(),imaouput);
        } else {
            cv::imwrite(fileNameOutput.toLatin1().data(),image);
        }
        output.insert("user", params["user"]);
        output.insert("path", path);
        output.insert("name", name + "-" + acti);
        output.insert("extension", exte);
    } else {
        output.insert("error", "No process image");
        output.insert("path", params["path"]);
    }

    QJsonDocument docOutput(output);
    emit Response(docOutput.toJson(QJsonDocument::Compact));
}
