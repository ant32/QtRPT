#ifndef EXAMPLEDLG4_H
#define EXAMPLEDLG4_H

#include <QDialog>
#include "qtrpt.h"

namespace Ui {
class ExampleDlg4;
}

class ExampleDlg4 : public QDialog
{
    Q_OBJECT
    
public:
    explicit ExampleDlg4(QWidget *parent = 0);
    ~ExampleDlg4();
    
private:
    Ui::ExampleDlg4 *ui;
    QtRPT *report;

private slots:
    void print();
    void setValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage);

};

#endif // EXAMPLEDLG4_H
