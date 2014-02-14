#ifndef EXAMPLEDLG3_H
#define EXAMPLEDLG3_H

#include <QDialog>
#include <QtPrintSupport>
#include "qtrpt.h"

namespace Ui {
class ExampleDlg3;
}

class ExampleDlg3 : public QDialog
{
    Q_OBJECT
    
public:
    explicit ExampleDlg3(QWidget *parent = 0);
    ~ExampleDlg3();
    
private:
    Ui::ExampleDlg3 *ui;
    QPrintPreviewWidget *preview;
    QPrinter *printer;
    QtRPT *report;

private slots:
    void updatePreview();
    void setValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage);
};

#endif // EXAMPLEDLG3_H
