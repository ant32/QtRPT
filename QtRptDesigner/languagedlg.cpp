/*
Name: QtRptDesigner
Version: 1.3.1
Programmer: Aleksey Osipov
e-mail: aliks-os@yandex.ru
2012-2014
*/

#include "languagedlg.h"
#include "ui_languagedlg.h"

LanguageDlg::LanguageDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LanguageDlg)
{
    ui->setupUi(this);
    this->setWindowTitle("Language QtRptDesigner");
    this->setFixedSize(485,148);

    QSettings settings(QCoreApplication::applicationDirPath()+"/setting.ini",QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    settings.beginGroup("language");
    QString language = settings.value("language").toString();
    QString measurement = settings.value("measurement").toString();
    settings.endGroup();
//    //loading active languge from qsettings ini file
//    //default value is not set because i'm reading the system language at start up

    if (language == "") //default system language
        ui->cmbLanguage->setCurrentIndex(0);

    else if (language == "en_US")//english united states
        ui->cmbLanguage->setCurrentIndex(1);

    else if (language == "ru_RU")//russian
        ui->cmbLanguage->setCurrentIndex(2);

    else if (language == "sr_RS")//serbian cyrilic
        ui->cmbLanguage->setCurrentIndex(3);

    else if (language == "sr_RS@latin")
        ui->cmbLanguage->setCurrentIndex(4);

    loadedIndex = ui->cmbLanguage->currentIndex();

//    // Load
    if (measurement == "")
        ui->cmbMeasurement->setCurrentIndex(0);

    else if (measurement == "cm")
        ui->cmbMeasurement->setCurrentIndex(0);

    else if (measurement == "Inch")
        ui->cmbMeasurement->setCurrentIndex(1);

    measurementIndex = ui->cmbMeasurement->currentIndex();
}

LanguageDlg::~LanguageDlg() {
    delete ui;
}

void LanguageDlg::on_btnOk_clicked() {
    QSettings settings(QCoreApplication::applicationDirPath()+"/setting.ini",QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    settings.beginGroup("language");
    if (ui->cmbLanguage->currentIndex() != loadedIndex) {
        switch(ui->cmbLanguage->currentIndex())
        {
        case 0://system default
            settings.setValue("language", "");
            break;
        case 1://american english
            settings.setValue("language", "en_US");
            break;
        case 2://russian
            settings.setValue("language", "ru_RU");
            break;
        case 3://serbian
            settings.setValue("language", "sr_RS");
            break;
        case 4://serbian latin
            settings.setValue("language", "sr_RS@latin");
            break;
        }
        QMessageBox::information(this,tr("Message QtRptDesigner"),tr("The language for this application has been changed. The change will take effect the next time the application is started"),QMessageBox::Ok);
    }
    switch(ui->cmbMeasurement->currentIndex())
    {
    case 0://cm
        settings.setValue("measurement", "cm");
        break;
    case 1://inch
        settings.setValue("measurement", "Inch");
        break;
    }
    settings.endGroup();
    this->close();
}

void LanguageDlg::on_btnCancel_clicked() {
    this->close();
}
