#-------------------------------------------------
#
# Project created by QtCreator 2017-03-29T09:02:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++11

CONFIG+=thread

TARGET = simulate
TEMPLATE = app



SOURCES += main.cpp\
    algo.cpp \
    colle.cpp \
    stm32spi.cpp \
    spi.cpp \
    gpio.cpp \
    collect_singal_set.cpp \
    OperateCP2110.cpp \
    pci.cpp \
    global.cpp \
    fileoperate.cpp \
    screencpp/alamdlg.cpp \
    screencpp/alamdlg2.cpp \
    screencpp/alamdlg3.cpp \
    screencpp/alamdlg4.cpp \
    screencpp/algorithmdld3.cpp \
    screencpp/algorithmdlg.cpp \
    screencpp/algorithmdlg2.cpp \
    screencpp/calibrationdlg.cpp \
    screencpp/calibrationparameterdlg.cpp \
    screencpp/calibrationparameterdlg2.cpp \
    screencpp/demodulationdlg.cpp \
    screencpp/iddlg.cpp \
    screencpp/iddlg2.cpp \
    screencpp/interfaceandcommunicationdlg.cpp \
    screencpp/interfaceandcommunicationdlg2.cpp \
    screencpp/keyboarddlg.cpp \
    screencpp/lddlg.cpp \
    screencpp/lddlg2.cpp \
    screencpp/logindlg.cpp \
    screencpp/logindlg1.cpp \
    screencpp/mainwindow.cpp \
    screencpp/picture_sheetdlg.cpp \
    screencpp/plsdlg.cpp \
    screencpp/referencecurvedlg.cpp \
    screencpp/referencecurvedlg2.cpp \
    screencpp/referencecurvedlg3.cpp \
    screencpp/spectrumselfregulatedlg.cpp \
    screencpp/spectrumselfregulatedlg1.cpp \
    screencpp/spectrumselfregulatedlg2.cpp \
    screencpp/spectrumselfregulatedlg3.cpp \
    screencpp/spectrumselfregulatedlg4.cpp \
    screencpp/verifydlg.cpp \
    screencpp/verifydlg2.cpp \
    screencpp/plotterdlg.cpp

HEADERS  += \
    algo.h \
    colle.h \
    global.h \
    include.h \
    stm32spi.h \
    collect_singal_set.h \
    include/Types.h \
    include/SLABHIDtoUART.h \
    include/SLABCP2110.h \
    include/SLABCP2114.h \
    include/CP2114_Common.h \
    OperateCP2110.h \
    pci.h \
    fileoperate.h \
    screeninclu/alamdlg.h \
    screeninclu/alamdlg2.h \
    screeninclu/alamdlg3.h \
    screeninclu/alamdlg4.h \
    screeninclu/algorithmdld3.h \
    screeninclu/algorithmdlg.h \
    screeninclu/algorithmdlg2.h \
    screeninclu/calibrationdlg.h \
    screeninclu/calibrationparameterdlg.h \
    screeninclu/calibrationparameterdlg2.h \
    screeninclu/demodulationdlg.h \
    screeninclu/iddlg.h \
    screeninclu/iddlg2.h \
    screeninclu/interfaceandcommunicationdlg.h \
    screeninclu/interfaceandcommunicationdlg2.h \
    screeninclu/keyboarddlg.h \
    screeninclu/lddlg.h \
    screeninclu/lddlg2.h \
    screeninclu/logindlg.h \
    screeninclu/logindlg1.h \
    screeninclu/mainwindow.h \
    screeninclu/picture_sheetdlg.h \
    screeninclu/plsdlg.h \
    screeninclu/referencecurvedlg.h \
    screeninclu/referencecurvedlg2.h \
    screeninclu/referencecurvedlg3.h \
    screeninclu/spectrumselfregulatedlg.h \
    screeninclu/spectrumselfregulatedlg1.h \
    screeninclu/spectrumselfregulatedlg2.h \
    screeninclu/spectrumselfregulatedlg3.h \
    screeninclu/spectrumselfregulatedlg4.h \
    screeninclu/verifydlg.h \
    screeninclu/verifydlg2.h \
    screeninclu/plotterdlg.h

FORMS    += \
    screenui/alamdlg.ui \
    screenui/alamdlg2.ui \
    screenui/alamdlg3.ui \
    screenui/alamdlg4.ui \
    screenui/algorithmdld3.ui \
    screenui/algorithmdlg.ui \
    screenui/algorithmdlg2.ui \
    screenui/calibrationdlg.ui \
    screenui/calibrationparameterdlg.ui \
    screenui/calibrationparameterdlg2.ui \
    screenui/demodulationdlg.ui \
    screenui/iddlg.ui \
    screenui/iddlg2.ui \
    screenui/interfaceandcommunicationdlg.ui \
    screenui/interfaceandcommunicationdlg2.ui \
    screenui/keyboarddlg.ui \
    screenui/lddlg.ui \
    screenui/lddlg2.ui \
    screenui/logindlg.ui \
    screenui/logindlg1.ui \
    screenui/mainwindow.ui \
    screenui/picture_sheetdlg.ui \
    screenui/plsdlg.ui \
    screenui/referencecurvedlg.ui \
    screenui/referencecurvedlg2.ui \
    screenui/referencecurvedlg3.ui \
    screenui/spectrumselfregulatedlg.ui \
    screenui/spectrumselfregulatedlg1.ui \
    screenui/spectrumselfregulatedlg2.ui \
    screenui/spectrumselfregulatedlg3.ui \
    screenui/spectrumselfregulatedlg4.ui \
    screenui/verifydlg.ui \
    screenui/verifydlg2.ui \
    screenui/plotterdlg.ui

unix:!macx: LIBS += -L$$PWD/../../../../opt/Linux/gcc-linaro-arm-linux-gnueabihf-4.7-2013.04-20130415_linux/arm-linux-gnueabihf/lib/ -lslabhidtouart

INCLUDEPATH += $$PWD/../../../../opt/Linux/gcc-linaro-arm-linux-gnueabihf-4.7-2013.04-20130415_linux/arm-linux-gnueabihf/include
DEPENDPATH += $$PWD/../../../../opt/Linux/gcc-linaro-arm-linux-gnueabihf-4.7-2013.04-20130415_linux/arm-linux-gnueabihf/include

unix:!macx: LIBS += -L$$PWD/../../../../opt/Linux/gcc-linaro-arm-linux-gnueabihf-4.7-2013.04-20130415_linux/arm-linux-gnueabihf/lib/ -lusb-1.0

INCLUDEPATH += $$PWD/../../../../opt/Linux/gcc-linaro-arm-linux-gnueabihf-4.7-2013.04-20130415_linux/arm-linux-gnueabihf/include
DEPENDPATH += $$PWD/../../../../opt/Linux/gcc-linaro-arm-linux-gnueabihf-4.7-2013.04-20130415_linux/arm-linux-gnueabihf/include

INCLUDEPATH +=/usr/local/qwt-6.1.3/include

#qwt
LIBS += -lqwt

