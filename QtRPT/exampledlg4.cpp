#include "exampledlg4.h"
#include "ui_exampledlg4.h"

ExampleDlg4::ExampleDlg4(QWidget *parent) : QDialog(parent), ui(new Ui::ExampleDlg4) {
    ui->setupUi(this);

    ui->tableWidget->setRowCount(20);
    QObject::connect(ui->btnPrint, SIGNAL(clicked()), this, SLOT(print()));

    QTableWidgetItem *newItem;
    int quant; int price; int sum;
    for (int i = 1; i < ui->tableWidget->rowCount()+1; ++i) {
        newItem = new QTableWidgetItem("Goods "+QString::number(i));
        ui->tableWidget->setItem(i-1,0,newItem);

        if (i == 3 || i == 5 || i == 7) quant = -i*10;
        else quant = i*10;

        newItem = new QTableWidgetItem(QString::number(quant));
        ui->tableWidget->setItem(i-1,1,newItem);

        price = i*100;
        newItem = new QTableWidgetItem(QString::number(price));
        ui->tableWidget->setItem(i-1,2,newItem);

        sum = quant * price;
        newItem = new QTableWidgetItem(QString::number(sum));
        ui->tableWidget->setItem(i-1,3,newItem);
    }
}

void ExampleDlg4::setValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage) {
    Q_UNUSED(reportPage);
    if (paramName == "NN")
        paramValue = recNo+1;
    if (paramName == "Goods") {
        if (ui->tableWidget->item(recNo,0) == 0) return;
        paramValue = ui->tableWidget->item(recNo,0)->text();
    }
    if (paramName == "Quantity") {
        if (ui->tableWidget->item(recNo,1) == 0) return;
        paramValue = ui->tableWidget->item(recNo,1)->text();
    }
    if (paramName == "Price") {
        if (ui->tableWidget->item(recNo,2) == 0) return;
        paramValue = ui->tableWidget->item(recNo,2)->text();
    }
    if (paramName == "Sum") {
        if (ui->tableWidget->item(recNo,3) == 0) return;
        paramValue = ui->tableWidget->item(recNo,3)->text();
    }
}

void ExampleDlg4::print() {
    QString fileName = "./examples_report/example4.xml";
    report = new QtRPT(this);
    report->recordCount << ui->tableWidget->rowCount();
    if (report->loadReport(fileName) == false) {
        qDebug()<<"Report's file not found";
    }
    QObject::connect(report, SIGNAL(setValue(int&, QString&, QVariant&, int)),
                     this, SLOT(setValue(int&, QString&, QVariant&, int)));
    report->printExec();

}

ExampleDlg4::~ExampleDlg4() {
    delete ui;
}
