#-------------------------------------------------
#
# Project created by QtCreator 2012-05-21T15:13:27
#
#-------------------------------------------------

QT       += core gui xml script
greaterThan(QT_MAJOR_VERSION, 4){
    QT += widgets printsupport
    DEFINES += HAVE_QT5
}

TARGET = QtRPT1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qtrpt.cpp \
    exampledlg1.cpp \
    exampledlg3.cpp \
    exampledlg2.cpp \
    exampledlg4.cpp \
    exampledlg5.cpp

HEADERS  += mainwindow.h \
    qtrpt.h \
    exampledlg1.h \
    exampledlg3.h \
    exampledlg2.h \
    exampledlg4.h \
    exampledlg5.h

FORMS    += mainwindow.ui \
    exampledlg1.ui \
    exampledlg3.ui \
    exampledlg2.ui \
    exampledlg4.ui \
    exampledlg5.ui
