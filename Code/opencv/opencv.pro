QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += widgets
INCLUDEPATH +="/usr/local/opencv/include/opencv4"
LIBS += -L"/usr/local/opencv/lib/"
LIBS += \
   -lopencv_core \
   -lopencv_features2d \
   -lopencv_highgui \
   -lopencv_imgcodecs \
   -lopencv_imgproc \
   -lopencv_video \
   -lopencv_videoio
CONFIG += c++17
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
