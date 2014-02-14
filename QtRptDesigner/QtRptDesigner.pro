#-------------------------------------------------
#
# Project created by QtCreator 2012-03-29T16:09:02
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4){
    QT += widgets
    DEFINES += HAVE_QT5
}

TARGET = QtRptDesigner
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    PageSettingDlg.cpp \
    ReportBand.cpp \
    tcontainerfield.cpp \
    ../CommonFiles/qlabelex.cpp \
    ../CommonFiles/tcontainer.cpp \
    EditFldDlg.cpp \
    aboutDlg.cpp \
    languagedlg.cpp \
    FldPropertyDlg.cpp \
    RepScrollArea.cpp

HEADERS  += mainwindow.h \
    PageSettingDlg.h \
    ReportBand.h \
    tcontainerfield.h \
    ../CommonFiles/qlabelex.h \
    ../CommonFiles/tcontainer.h \
    EditFldDlg.h \
    aboutDlg.h \
    languagedlg.h \
    FldPropertyDlg.h \
    RepScrollArea.h

FORMS    += mainwindow.ui \
    PageSettingDlg.ui \
    ReportBand.ui \
    EditFldDlg.ui \
    languagedlg.ui \
    FldPropertyDlg.ui \
    RepScrollArea.ui

RESOURCES += \
    images.qrc

TRANSLATIONS += i18n/QtRprtDesigner_ru_RU.ts
TRANSLATIONS += i18n/QtRprtDesigner_sr_RS.ts
TRANSLATIONS += i18n/QtRprtDesigner_sr_RS@latin.ts

 #win32:INCLUDEPATH += "../CommonFiles/"
 #unix:INCLUDEPATH += "/home/user/extra headers"
