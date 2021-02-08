#ifndef OVTASKIMAGE_H
#define OVTASKIMAGE_H

#include <QRunnable>
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class OvTaskImage : public QObject, public QRunnable {
    Q_OBJECT
public:
    OvTaskImage(QJsonObject params);

signals:
    void Response(QByteArray data);

protected:
    void run();
    QJsonObject params;
    cv::Mat image;
};

#endif // OVTASKIMAGE_H
