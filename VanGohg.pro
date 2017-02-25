#-------------------------------------------------
#
# Project created by QtCreator 2015-08-26T16:12:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VanGohg
TEMPLATE = app


SOURCES += src/main.cpp\
    src/mainwindow.cpp \
    src/hexstring.cpp \
    src/imageproc.cpp

HEADERS  += \
    src/mainwindow.hpp \
    src/hexstring.hpp \
    src/imageproc.hpp

FORMS    += ui/mainwindow.ui

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_ml
LIBS += -lopencv_video
LIBS += -lopencv_features2d
LIBS += -lopencv_calib3d
LIBS += -lopencv_objdetect
LIBS += -lopencv_flann

DISTFILES += \
    README.md
