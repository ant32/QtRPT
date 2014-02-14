#include "exampledlg2.h"
#include "ui_exampledlg2.h"

ExampleDlg2::ExampleDlg2(QWidget *parent) : QDialog(parent), ui(new Ui::ExampleDlg2) {
    ui->setupUi(this);
    QObject::connect(ui->btnPrint, SIGNAL(clicked()), this, SLOT(print()));
    ui->table1->setRowCount(20);
    ui->table2->setRowCount(10);

    QTableWidgetItem *newItem;
    for (int i = 0; i < ui->table1->rowCount(); ++i) {
        newItem = new QTableWidgetItem("DS1: "+QString::number(i+1));
        ui->table1->setItem(i,0,newItem);
    }
    for (int i = 0; i < ui->table2->rowCount(); ++i) {
        newItem = new QTableWidgetItem("DS2: "+QString::number(i+1));
        ui->table2->setItem(i,0,newItem);
    }
}

void ExampleDlg2::print() {
    QString fileName = "./examples_report/example2.xml";
    report = new QtRPT(this);
    report->recordCount << ui->table1->rowCount();
    report->recordCount << ui->table2->rowCount();
    if (report->loadReport(fileName) == false) {
        qDebug()<<"Report's file not found";
    }
    QObject::connect(report, SIGNAL(setValue(int&, QString&, QVariant&, int)),
                     this, SLOT(setValue(int&, QString&, QVariant&, int)));
    report->printExec();

}

void ExampleDlg2::setValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage) {
    if (paramName == "value") {
        if (reportPage == 0) {
            if (ui->table1->item(recNo,0) == 0) return;
            paramValue = ui->table1->item(recNo,0)->text();
        }
        if (reportPage == 1) {
            if (ui->table2->item(recNo,0) == 0) return;
            paramValue = ui->table2->item(recNo,0)->text();
        }
    }
}

ExampleDlg2::~ExampleDlg2() {
    delete ui;
}
