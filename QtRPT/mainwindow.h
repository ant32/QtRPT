#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qtrpt.h"
#include "exampledlg1.h"
#include "exampledlg2.h"
#include "exampledlg3.h"
#include "exampledlg4.h"
#include "exampledlg5.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //static void getReportValue(int &recNo, QString &paramName, QVariant &paramValue);


private:
    Ui::MainWindow *ui;


private slots:
    void showReport();

};

#endif // MAINWINDOW_H
