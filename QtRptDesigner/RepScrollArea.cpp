/*
Name: QtRptDesigner
Version: 1.3.1
Programmer: Aleksey Osipov
e-mail: aliks-os@yandex.ru
2012-2014
*/

#include "RepScrollArea.h"
#include "ui_RepScrollArea.h"
#include <QSettings>
#include <QPainter>

RepScrollArea::RepScrollArea(QWidget *parent) :
                            QScrollArea(parent), ui(new Ui::RepScrollArea) {
    ui->setupUi(this);
    m_mainWindow = parent;
    ui->repWidget->setObjectName("repWidget");
    repWidget = ui->repWidget;

    // load settings.
    QSettings settings(QCoreApplication::applicationDirPath()+"/setting.ini",QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    settings.beginGroup("language");
    QString measurement = settings.value("measurement").toString();
    settings.endGroup();
    if (measurement == "cm" || measurement == ""){
        pageSetting.unit = 40;
        pageSetting.unitName = "cm";
        pageSetting.marginsLeft     = 40;
        pageSetting.marginsRight    = 40;
        pageSetting.marginsTop      = 40;
        pageSetting.marginsBottom   = 40;
        pageSetting.pageWidth       = 840;
        pageSetting.pageHeight      = 1188;
    }else if (measurement == "Inch"){
        pageSetting.unit = 100;
        pageSetting.unitName = "Inch";
        pageSetting.marginsLeft     = 25;
        pageSetting.marginsRight    = 25;
        pageSetting.marginsTop      = 25;
        pageSetting.marginsBottom   = 25;
        pageSetting.pageWidth       = 850;
        pageSetting.pageHeight      = 1100;
    }
    pageSetting.pageOrientation = 0;

    this->setMouseTracking(true);
    this->installEventFilter(parent);
    ui->repWidget->setMouseTracking(true);
    ui->repWidget->installEventFilter(parent);
    ui->horRuler->installEventFilter(this);
    ui->verRuler->installEventFilter(this);

    //Menu for band
    bandMenu = new QMenu(this);
    this->setVisible(true);
    setPaperSize();
}

void RepScrollArea::setPaperSize() {
    ui->repWidget->setMinimumWidth(pageSetting.pageWidth);
    ui->repWidget->setMinimumHeight(pageSetting.pageHeight);
    ui->leftMarginsSpacer->changeSize(pageSetting.marginsLeft+26,
                                      ui->leftMarginsSpacer->sizeHint().height(),
                                      QSizePolicy::Fixed,
                                      QSizePolicy::Fixed);
    ui->verticalLayout_10->invalidate();
    ui->topMarginsSpacer->changeSize(ui->topMarginsSpacer->sizeHint().width(),pageSetting.marginsTop,QSizePolicy::Fixed,QSizePolicy::Fixed);
    ui->verticalLayout_52->invalidate();

    QList<ReportBand *> allReportBand = ui->repWidget->findChildren<ReportBand *>();
    qSort(allReportBand.begin(), allReportBand.end(), compareBandType);
    int top_ = pageSetting.marginsTop;
    for (int j=0; j<allReportBand.size(); j++) {
        ReportBand *widget = qobject_cast<ReportBand *>(allReportBand.at(j));
        widget->setGeometry(pageSetting.marginsLeft,
                            top_,
                            (pageSetting.pageWidth - pageSetting.marginsLeft - pageSetting.marginsRight ),
                            widget->height());
        top_ += widget->geometry().height()+5;
    }
}

QList<QWidget *> RepScrollArea::getReportItems() {
    return ui->repWidget->findChildren<QWidget *>();
}

void RepScrollArea::clearReport() {
    qDeleteAll(ui->repWidget->findChildren<ReportBand*>());
}

bool RepScrollArea::allowField() {
    QList<ReportBand *> allReportBand = ui->repWidget->findChildren<ReportBand *>();
    if (allReportBand.size() == 0) return false;
    else return true;
}

void RepScrollArea::paintGrid() {
    if(!isShowGrid) return;
    int x_=pageSetting.marginsLeft+pageSetting.unit;
    int y_=pageSetting.marginsTop;
    QPainter painter(ui->repWidget);
    painter.setPen(QColor(240, 240, 240, 255));
    painter.drawRect(pageSetting.marginsLeft,pageSetting.marginsTop,
                     ui->repWidget->width()-pageSetting.marginsRight-pageSetting.marginsLeft,
                     ui->repWidget->height()-pageSetting.marginsTop-pageSetting.marginsBottom);

    while ( x_ < ui->repWidget->width()-pageSetting.marginsRight ) {
        if (x_/(pageSetting.unit/2)%2==0) {
            //painter.setPen(Qt::DotLine);
        } else {
            //painter.setPen(Qt::SolidLine);
            //painter.setPen(Qt::blue);
        }
        painter.drawLine(x_,pageSetting.marginsTop,x_,ui->repWidget->height()-pageSetting.marginsTop);
        x_ = x_+pageSetting.unit;
    }

    while ( y_ < ui->repWidget->height()-pageSetting.marginsTop ) {
        if (y_/(pageSetting.unit/2)%2==0) {
            //painter.setPen(Qt::SolidLine);
            //painter.setPen(Qt::blue);
        } else {
            //painter.setPen(Qt::DotLine);
        }
        painter.setOpacity(0.5);
        painter.drawLine(pageSetting.marginsLeft,y_,ui->repWidget->width()-pageSetting.marginsRight,y_);
        y_ = y_+pageSetting.unit;
    }
}

void RepScrollArea::showGrid(bool value) {
    QSettings settings(QCoreApplication::applicationDirPath()+"/setting.ini",QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    settings.setValue("ShowGrid", value);
    this->isShowGrid = value;
    ui->repWidget->repaint();
}

void RepScrollArea::paintHorRuler() {
    QPainter painter(ui->horRuler);
    int x_=0 ;
    while ( x_ < ui->horRuler->width() ) {
        x_ = x_+pageSetting.unit/2;
        if (x_/(pageSetting.unit/2)%2==0) {
            const QString rt = QString::number(x_/pageSetting.unit);
            painter.drawText(x_,15,rt);
        } else {
            painter.drawText(x_,15,"-");
        }
    }
}

void RepScrollArea::paintVerRuler() {
    QPainter painter(ui->verRuler);
    int y_ =0 ;
    painter.rotate(-90);
    while ( y_ < ui->verRuler->height() ) {
        y_ = y_+pageSetting.unit/2;
        if (y_/(pageSetting.unit/2)%2==0) {
            const QString rt = QString::number(y_/pageSetting.unit);
            painter.drawText(-y_,15,rt);
        } else {
            painter.drawText(-y_,15,"-");
        }
    }
}

ReportBand *RepScrollArea::m_addBand(QString bandName, BandType type, int m_height) {
    QTreeWidgetItem *item = new QTreeWidgetItem(rootItem);
    icon.addPixmap(QPixmap(QString::fromUtf8(":/images/bands.png")), QIcon::Normal, QIcon::On);
    item->setIcon(0,icon);
    item->setText(0,bandName);
    item->setSelected(true);
    rootItem->addChild(item);

    ReportBand *reportBand = new ReportBand(ui->repWidget, type, item);
    reportBand->itemInTree = item;
    reportBand->setMenu(bandMenu);
    connect(reportBand, SIGNAL(delBand(QTreeWidgetItem *)), m_mainWindow, SLOT(delItemInTree(QTreeWidgetItem *)));

    QRect r = reportBand->geometry();
    if (m_height != 0)
        r.setHeight(m_height+reportBand->titleHeight);
    r.setLeft(pageSetting.marginsLeft);
    r.setWidth(pageSetting.pageWidth - pageSetting.marginsLeft - pageSetting.marginsRight);
    reportBand->setGeometry(r);

    correctBandGeom();

    connect(reportBand, SIGNAL(endResizing(QRect)), this, SLOT(bandResing(QRect)));
    connect(reportBand, SIGNAL(inFocus(bool)), m_mainWindow, SLOT(setWidgetInFocus(bool)));
    actField->setEnabled(allowField());
    return reportBand;
}

//Корректируем расположение бэндов после вставки, удаления
void RepScrollArea::correctBandGeom(QWidget *rep) {
    int top_ = pageSetting.marginsTop;
    QList<ReportBand *> allReportBand = ui->repWidget->findChildren<ReportBand *>();
    if (allReportBand.size() != 0)
        qSort(allReportBand.begin(), allReportBand.end(), compareBandType);

    for (int j=0; j<allReportBand.size(); j++) {
        ReportBand *widget = qobject_cast<ReportBand *>(allReportBand.at(j));
        if (widget == rep) continue;
        widget->move(pageSetting.marginsLeft, top_);
        top_ += widget->height()+5;
    }
}

bool RepScrollArea::eventFilter(QObject *obj, QEvent *e) {
    /*if(obj==ui->repWidget && e->type()==QEvent::Paint) {
        paintGrid();
        return true;
    }*/
    if(obj==ui->horRuler && e->type()==QEvent::Paint) {
        paintHorRuler();
        return true;
    }
    if(obj==ui->verRuler && e->type()==QEvent::Paint) {
        paintVerRuler();
        return true;
    }
    return QWidget::eventFilter(obj,e);
}

void RepScrollArea::bandResing(QRect rect) {
    ReportBand *reportBand = qobject_cast<ReportBand *>(sender());
    QList<ReportBand *> allReportBand = ui->repWidget->findChildren<ReportBand *>();
    qSort(allReportBand.begin(), allReportBand.end(), compareBandType);
    int top_ = rect.y()+rect.height()+5;

    for (int j=0; j<allReportBand.size(); j++) {
        ReportBand *widget = qobject_cast<ReportBand *>(allReportBand.at(j));
        if (widget->bandType <= reportBand->bandType) continue;
        widget->setGeometry(pageSetting.marginsLeft,
                            top_,
                            (pageSetting.pageWidth - pageSetting.marginsLeft - pageSetting.marginsRight ),
                            widget->height());
        top_ += widget->geometry().height()+5;
    }

    int _h = reportBand->geometry().height() - reportBand->titleHeight;
    emit bandResing(_h);
}

RepScrollArea::~RepScrollArea() {
    delete ui;
}

int compareBandType(ReportBand *p1, ReportBand *p2) {
    return p1->bandType < p2->bandType;
}
