/*
Name: QtRptDesigner
Version: 1.3.1
Programmer: Aleksey Osipov
e-mail: aliks-os@yandex.ru
2012-2014
*/

#include "aboutDlg.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QDesktopServices>
#include <QUrl>

AboutDlg::AboutDlg(QWidget *parent) : QDialog(parent) {
    this->setWindowTitle(tr("About QtRptDesiner"));
    QSize MaxSize(300, 200);
    QSize MinSize(300, 200);
    setMaximumSize(MaxSize);
    setMinimumSize(MinSize);

    QRect gry = geometry();
    gry.moveCenter(qApp->desktop()->availableGeometry().center());
    setGeometry(gry);

    QPushButton *btnOK = new QPushButton(this);
    btnOK->setText("OK");
    connect(btnOK, SIGNAL(clicked()), this, SLOT(close()));

    QLabel *lab1 = new QLabel(this);
    lab1->setPixmap(QPixmap(":/images/MQueryLogo.png"));
    QString lbl = "<h2><b><p style='color:#0033FF'>"+QApplication::applicationName()+"</p></b></h2>"+
                  tr("Version: ")+QApplication::applicationVersion()+"<br>"+
                  tr("Programmer: Aleksey Osipov")+"<br>"+
                  "E-mail: aliks-os@yandex.ru"+"<br>"+
                  "<a href='https://sourceforge.net/projects/qtrpt/'>https://sourceforge.net/projects/qtrpt/</a>"+"<br>"+
                  tr("2012-2014 years");
    QLabel *lab2 = new QLabel(lbl, this);
    connect(lab2, SIGNAL(linkActivated(const QString)), this, SLOT(openLink(const QString)));

    QHBoxLayout *hLayout2 = new QHBoxLayout;
    hLayout2->addWidget(lab1);
    hLayout2->addWidget(lab2);
    hLayout2->addStretch();

    QHBoxLayout *hLayout1 = new QHBoxLayout;
    //hLayout->addSpacerItem(spacer1);
    hLayout1->addStretch();
    hLayout1->addWidget(btnOK);
    //hLayout->addSpacerItem(spacer2);
    hLayout1->addStretch();

    QVBoxLayout *vLayout = new QVBoxLayout;
    //vLayout->addSpacerItem(spacer3);
    vLayout->addLayout(hLayout2);
    vLayout->addStretch();
    vLayout->addLayout(hLayout1);
    this->setLayout(vLayout);
}

void AboutDlg::openLink(const QString url) {
    QDesktopServices::openUrl(QUrl(url));
}
