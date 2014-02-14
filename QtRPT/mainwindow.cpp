#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->btnShow, SIGNAL(clicked()), this, SLOT(showReport()));
}

void MainWindow::showReport() {
    QDialog *dlg = 0;
    if (ui->rBtn1->isChecked()) {
        dlg = new ExampleDlg1(this);
    }
    if (ui->rBtn2->isChecked()) {
        dlg = new ExampleDlg2(this);
    }
    if (ui->rBtn3->isChecked()) {
        dlg = new ExampleDlg3(this);
    }
    if (ui->rBtn4->isChecked()) {
        dlg = new ExampleDlg4(this);
    }
    if (ui->rBtn5->isChecked()) {
        dlg = new ExampleDlg5(this);
    }

    if (dlg != 0) {
        dlg->exec();
    }
    delete dlg;
}

MainWindow::~MainWindow() {
    delete ui;
}
