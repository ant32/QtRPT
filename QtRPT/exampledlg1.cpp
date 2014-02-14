#include "exampledlg1.h"
#include "ui_exampledlg1.h"

ExampleDlg1::ExampleDlg1(QWidget *parent) : QDialog(parent), ui(new Ui::ExampleDlg1) {
    ui->setupUi(this);

    ui->dtp->setDate(QDate::currentDate());
    ui->edtCustomer->setText("Write customer here");
    ui->tableWidget->setRowCount(45);
    QObject::connect(ui->btnPrint, SIGNAL(clicked()), this, SLOT(print()));

    QTableWidgetItem *newItem;
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        newItem = new QTableWidgetItem("Goods "+QString::number(i));
        ui->tableWidget->setItem(i,0,newItem);

        newItem = new QTableWidgetItem(QString::number(i*10));
        ui->tableWidget->setItem(i,1,newItem);

        newItem = new QTableWidgetItem(QString::number(i*100));
        ui->tableWidget->setItem(i,2,newItem);

        newItem = new QTableWidgetItem(QString::number(i*1000));
        ui->tableWidget->setItem(i,3,newItem);
    }
}

void ExampleDlg1::setValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage) {
    Q_UNUSED(reportPage);
    if (paramName == "customer")
        paramValue = ui->edtCustomer->text();
    if (paramName == "date")
        paramValue = ui->dtp->date().toString();
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

void ExampleDlg1::setValueImage(int &recNo, QString &paramName, QImage &paramValue, int reportPage) {
    Q_UNUSED(recNo);
    Q_UNUSED(reportPage);
    if (paramName == "image") {
        QImage *image = new QImage(QCoreApplication::applicationDirPath()+"/qt.png");
        paramValue = *image;
    }
}

void ExampleDlg1::print() {
    QString fileName = "./examples_report/example1.xml";
    report = new QtRPT(this);
    report->setBackgroundImage(QPixmap("./qt_background_portrait.png"));
    report->recordCount << ui->tableWidget->rowCount();
    if (report->loadReport(fileName) == false) {
        qDebug()<<"Report's file not found";
    }
    QObject::connect(report, SIGNAL(setValue(int&, QString&, QVariant&, int)),
                     this, SLOT(setValue(int&, QString&, QVariant&, int)));
    QObject::connect(report, SIGNAL(setValueImage(int&, QString&, QImage&, int)),
                     this, SLOT(setValueImage(int&, QString&, QImage&, int)));
    //report->setCallbackFunc(getReportValue);
    report->printExec();
}

ExampleDlg1::~ExampleDlg1() {
    delete ui;
}
