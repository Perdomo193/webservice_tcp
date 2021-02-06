QT -= gui
QT += core network
CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += -I/usr/include \
        -I/home/fuher/Qt/5.9.0/5.9/gcc_64/include

LIBS += -L/home/fuher/Qt/5.9.0/5.9/gcc_64/lib

LIBS += -L/home/fuher/Desktop/github/opencv/build/lib \
    -lopencv_core \
    -lopencv_imgcodecs \
    -lopencv_imgproc \
    -lopencv_highgui \

SOURCES += \
        main.cpp \
        server/ovtaskimage.cpp \
        server/tcpservervo.cpp \
        server/tcpsocketvo.cpp

TRANSLATIONS += \
    console-vo_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    server/ovtaskimage.h \
    server/tcpservervo.h \
    server/tcpsocketvo.h
