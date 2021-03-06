/*
Name: QtRptDesigner
Version: 1.3.1
Programmer: Aleksey Osipov
e-mail: aliks-os@yandex.ru
2012-2014
*/

#ifndef PAGESETTINGDLG_H
#define PAGESETTINGDLG_H

#include <QDialog>

namespace Ui {
    class PageSettingDlg;
}

struct PageSetting {
    float marginsLeft;
    float marginsRight;
    float marginsTop;
    float marginsBottom;
    float pageWidth;
    float pageHeight;
    int pageOrientation;
    int unit;
    QString unitName;
};

class PageSettingDlg : public QDialog
{
    Q_OBJECT

public:
    explicit PageSettingDlg(QWidget *parent = 0);
    ~PageSettingDlg();
    void showThis(PageSetting pageSetting);
    PageSetting pageSetting;

private:
    Ui::PageSettingDlg *ui;
    void saveSettings();

private slots:
    void changeOrientation();
    void on_sizeCombo_currentIndexChanged(int index);
    void on_unitCombo_currentIndexChanged(int index);
};

#endif // PAGESETTINGDLG_H
