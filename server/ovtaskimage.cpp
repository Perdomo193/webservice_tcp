#include "ovtaskimage.h"
#include <QDebug>

OvTaskImage::OvTaskImage(QJsonObject params): params(params) {}

void OvTaskImage::run() {
    QString path = params["path"].toString();
    QString name = params["name"].toString();
    QString exte = params["extension"].toString();
    QString acti = params["action"].toString();

    QString fileNameInput = path + name;
    QString fileNameOutput = fileNameInput + acti + '.' + exte;
    fileNameInput += "." + exte;

    image = cv::imread(fileNameInput.toLatin1().data());
    cv::Mat ima_gray;
    cv::cvtColor(image, ima_gray, cv::COLOR_BGR2GRAY);
    cv::imwrite(fileNameOutput.toLatin1().data(),ima_gray);

    QJsonObject output;
    output.insert("user", params["user"]);
    output.insert("path", path);
    output.insert("name", name + "-" + acti);
    output.insert("extension", exte);
    QJsonDocument docOutput(output);
    emit Response(docOutput.toJson(QJsonDocument::Compact));
}
