#ifndef EXAMPLEDLG5_H
#define EXAMPLEDLG5_H

#include <QDialog>
#include "qtrpt.h"

namespace Ui {
class ExampleDlg5;
}

class ExampleDlg5 : public QDialog
{
    Q_OBJECT
    
public:
    explicit ExampleDlg5(QWidget *parent = 0);
    ~ExampleDlg5();
    
private:
    Ui::ExampleDlg5 *ui;
    QtRPT *report;

private slots:
    void print();
    void setValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage);

};

#endif // EXAMPLEDLG5_H
