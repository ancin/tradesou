#-------------------------------------------------
#
# Project created by QtCreator 2012-10-29T17:07:58
#
#-------------------------------------------------

QT       += core gui webkit network xml sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tradesou
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    crawler.cpp \
    urlCatched.cpp \
    runScanner.cpp \
    formCatched.cpp

HEADERS  += mainwindow.h \
    crawler.h \
    urlCatched.h \
    runScanner.h \
    formCatched.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    images/save.png \
    images/paste.png \
    images/open.png \
    images/new.png \
    images/cut.png \
    images/copy.png \
    images/main.ico \
    images/crawler.ico \
    images/tradesou-logo.png

RESOURCES += \
    tradesou.qrc
