#include "exampledlg3.h"
#include "ui_exampledlg3.h"

ExampleDlg3::ExampleDlg3(QWidget *parent) : QDialog(parent), ui(new Ui::ExampleDlg3) {
    ui->setupUi(this);
    ui->edtFirstName->setText("Aleksey");
    ui->edtLastName->setText("Osipov");
    ui->edtEmail->setText("aliks-os@yandex.ru");
    connect(ui->btnUpdatePreview, SIGNAL(clicked()), this, SLOT(updatePreview()));

    QString fileName = "./examples_report/example3.xml";
    report = new QtRPT(this);
    if (report->loadReport(fileName) == false) {
        qDebug()<<"Report's file not found";
    }
    QObject::connect(report, SIGNAL(setValue(int&, QString&, QVariant&, int)),
                     this, SLOT(setValue(int&, QString&, QVariant&, int)));

    printer = new QPrinter;
    printer->setOutputFormat(QPrinter::PdfFormat);
    printer->setOrientation(QPrinter::Portrait);
    printer->setPaperSize(QPrinter::A4);
    printer->setFullPage(true);

    preview = new QPrintPreviewWidget(printer, this);
    ui->widget->layout()->addWidget(preview);
    connect(preview, SIGNAL(paintRequested(QPrinter*)), report, SLOT(printPreview(QPrinter*)));
    preview->show();
    preview->fitInView();

    updatePreview();
}

void ExampleDlg3::setValue(int &recNo, QString &paramName, QVariant &paramValue, int reportPage) {
    Q_UNUSED(recNo);
    Q_UNUSED(reportPage);
    if (paramName == "FirstName")
        paramValue = ui->edtFirstName->text();
    if (paramName == "LastName")
        paramValue = ui->edtLastName->text();
    if (paramName == "Email")
        paramValue = ui->edtEmail->text();
}

void ExampleDlg3::updatePreview() {
    preview->updatePreview();
}

ExampleDlg3::~ExampleDlg3() {
    delete ui;
}
