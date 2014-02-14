#ifndef EXAMPLEDLG2_H
#define EXAMPLEDLG2_H

#include <QDialog>
#include "qtrpt.h"

namespace Ui {
class ExampleDlg2;
}

class ExampleDlg2 : public QDialog
{
    Q_OBJECT
    
public:
    explicit ExampleDlg2(QWidget *parent = 0);
    ~ExampleDlg2();
    
private:
    Ui::ExampleDlg2 *ui;
    QtRPT *report;

private slots:
    void print();
    void setValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage);

};

#endif // EXAMPLEDLG2_H
