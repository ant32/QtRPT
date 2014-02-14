#ifndef EXAMPLEDLG1_H
#define EXAMPLEDLG1_H

#include <QDialog>
#include "qtrpt.h"

namespace Ui {
class ExampleDlg1;
}

class ExampleDlg1 : public QDialog
{
    Q_OBJECT
    
public:
    explicit ExampleDlg1(QWidget *parent = 0);
    ~ExampleDlg1();
    
private:
    Ui::ExampleDlg1 *ui;
    QtRPT *report;

private slots:
    void print();
    void setValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage);
    void setValueImage(int &recNo, QString &paramName, QImage &paramValue, int reportPage);

};

#endif // EXAMPLEDLG1_H
