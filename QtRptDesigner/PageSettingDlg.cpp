/*
Name: QtRptDesigner
Version: 1.3.1
Programmer: Aleksey Osipov
e-mail: aliks-os@yandex.ru
2012-2014
*/

#include "PageSettingDlg.h"
#include "ui_PageSettingDlg.h"
#include <QSettings>

PageSettingDlg::PageSettingDlg(QWidget *parent) : QDialog(parent), ui(new Ui::PageSettingDlg) {
    ui->setupUi(this);

    // load settings.
    QSettings settings(QCoreApplication::applicationDirPath()+"/setting.ini",QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    settings.beginGroup("language");
    QString measurement = settings.value("measurement").toString();
    settings.endGroup();
    if (measurement == "cm" || measurement == ""){
        pageSetting.unit = 40;
        pageSetting.unitName = "cm";
    }else if (measurement == "Inch"){
        pageSetting.unit = 100;
        pageSetting.unitName = "Inch";
    }
    connect(ui->rLandscape, SIGNAL(clicked()), this, SLOT(changeOrientation()));
    connect(ui->rPortrait, SIGNAL(clicked()), this, SLOT(changeOrientation()));
}

void PageSettingDlg::showThis(PageSetting pageSetting) {
    ui->edtLeft->setText(QString::number(pageSetting.marginsLeft/pageSetting.unit));
    ui->edtRight->setText(QString::number(pageSetting.marginsRight/pageSetting.unit));
    ui->edtTop->setText(QString::number(pageSetting.marginsTop/pageSetting.unit));
    ui->edtBottom->setText(QString::number(pageSetting.marginsBottom/pageSetting.unit));
    ui->edtWidth->setText(QString::number(pageSetting.pageWidth/pageSetting.unit));
    ui->edtHeight->setText(QString::number(pageSetting.pageHeight/pageSetting.unit));
    if (pageSetting.unitName.isEmpty() || pageSetting.unitName == "cm")
        ui->unitCombo->setCurrentIndex(0);
    else //inch
        ui->unitCombo->setCurrentIndex(1);
    if (pageSetting.pageOrientation == 0) ui->rPortrait->setChecked(true);
    if (pageSetting.pageOrientation == 1) ui->rLandscape->setChecked(true);
    if (ui->rLandscape->isChecked())
        ui->lblOrientation->setPixmap(QPixmap(QString::fromUtf8(":/images/landscape.png")));
    if (ui->rPortrait->isChecked())
        ui->lblOrientation->setPixmap(QPixmap(QString::fromUtf8(":/images/portrait.png")));
    if (exec() == QDialog::Accepted) {
        saveSettings();
    }
}

void PageSettingDlg::changeOrientation() {
    QString str = ui->edtHeight->text();
    ui->edtHeight->setText(ui->edtWidth->text());
    ui->edtWidth->setText(str);
    if (ui->rLandscape->isChecked())
        ui->lblOrientation->setPixmap(QPixmap(QString::fromUtf8(":/images/landscape.png")));
    if (ui->rPortrait->isChecked())
        ui->lblOrientation->setPixmap(QPixmap(QString::fromUtf8(":/images/portrait.png")));
}

void PageSettingDlg::saveSettings() {
    if (ui->unitCombo->currentIndex() == 0){
        pageSetting.unit      = 40;
        pageSetting.unitName  = "cm";
    }else{//inch
        pageSetting.unit      = 100;
        pageSetting.unitName  = "Inch";
    }
    pageSetting.marginsLeft   = ui->edtLeft->text().toFloat()*pageSetting.unit;
    pageSetting.marginsRight  = ui->edtRight->text().toFloat()*pageSetting.unit;
    pageSetting.marginsTop    = ui->edtTop->text().toFloat()*pageSetting.unit;
    pageSetting.marginsBottom = ui->edtBottom->text().toFloat()*pageSetting.unit;
    pageSetting.pageWidth     = ui->edtWidth->text().toFloat()*pageSetting.unit;
    pageSetting.pageHeight    = ui->edtHeight->text().toFloat()*pageSetting.unit;
    if (ui->rLandscape->isChecked())
        pageSetting.pageOrientation = 1;
    if (ui->rPortrait->isChecked())
        pageSetting.pageOrientation = 0;
}

void PageSettingDlg::on_sizeCombo_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "A4"){
        ui->unitCombo->setCurrentIndex(0);
        ui->edtWidth->setText("21.0");
        ui->edtHeight->setText("29.7");
    } else if (arg1 == "Letter"){
        ui->unitCombo->setCurrentIndex(1);
        ui->edtWidth->setText("8.5");
        ui->edtHeight->setText("11");
    }
}

PageSettingDlg::~PageSettingDlg() {
    delete ui;
}
