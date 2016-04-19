#-------------------------------------------------
#
# Project created by QtCreator 2016-04-15T20:59:19
#
#-------------------------------------------------

QT       += core
QT       += qml quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CompagnonDeVoyage
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    synthesiswindow.cpp \
    synthesistab.cpp \
    activityitem.cpp \
    addnewitem.cpp

HEADERS  += mainwindow.h \
    synthesiswindow.h \
    synthesistab.h \
    activityitem.h \
    addnewitem.h

FORMS    += mainwindow.ui \
    synthesiswindow.ui

OTHER_FILES +=

RESOURCES += \
    travelTitleImage.qrc \
    icons.qrc \
    datafiles.qrc
