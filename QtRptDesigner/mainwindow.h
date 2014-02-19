/*
Name: QtRptDesigner
Version: 1.3.1
Programmer: Aleksey Osipov
e-mail: aliks-os@yandex.ru
2012-2014
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDomDocument>
#include <QItemDelegate>
#include <QListWidget>
#include <QFontComboBox>
#include "PageSettingDlg.h"
#include "ReportBand.h"
#include "tcontainerfield.h"
#include "aboutDlg.h"
#include "languagedlg.h"
#include "RepScrollArea.h"

namespace Ui {
    class MainWindow;
}

class EditorDelegate: public QItemDelegate
{
    Q_OBJECT

public:
    EditorDelegate(QObject *parent);
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const {
        Q_UNUSED(option);
        Q_UNUSED(index);
        return QSize(50,20);
    }
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

private slots:
    void commitAndCloseEditor();
    void editorClose_(QWidget *editor, QAbstractItemDelegate::EndEditHint hint);

signals:
    void editorClose(QItemDelegate *item);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *e);
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    QListWidget *listFrameStyle;
    QDomDocument *xmlDoc;    
    QTreeWidgetItem *rootItem;
    QWidget *widgetInFocus;
    TContainerField *newContField;
    TContainerField *cloneCont;
    QList<TContainerField *> *cloneContList;
    QList<TContainerField *> *newContList;
    QFontComboBox *cbFontName;
    QComboBox *cbFontSize;
    QComboBox *cbFrameWidth;
    bool newContMoving;
    QIcon icon;
    QString fileName;
    QMap<QObject *, QTreeWidgetItem *> map;
    QMenu *contMenu;


    QAction *actRepTitle;
    QAction *actReportSummary;
    QAction *actPageHeader;
    QAction *actPageFooter;
    QAction *actMasterData;
    QAction *actMasterFooter;
    QAction *actMasterHeader;
    QAction *separatorAct;

    enum { MaxRecentFiles = 5 };
    QAction *recentFileActs[MaxRecentFiles];

    void newFeildTreeItem(TContainerField *contField, ReportBand *widget);
    bool setXMLProperty(QDomElement *repElem, QWidget *widget);
    void selectItemInTree(QTreeWidgetItem *item);
    void showParamState();
    Command getCommand(QObject *obj);
    void execButtonCommand(Command command, QVariant value);
    QTreeWidgetItem *findItemInTree(Command command);
    void generateName(TContainerField *cont);
    void setParamTree(Command command, QVariant value = 0, bool child = false);
    void updateRecentFileActions();
    void setCurrentFile(const QString &fileName);

private slots:
    void showAbout();
    void openFile();
    void newReport();
    void saveReport();
    void showPageSetting();
    void clickOnTBtn();
    void addBand();
    void addField();
    void AddPicture();
    void setWidgetInFocus(bool inFocus);
    void delItemInTree(QTreeWidgetItem *);
    void selTree(QTreeWidgetItem *item, int);
    void itemChanged(QTreeWidgetItem *item, int column);
    void closeEditor();
    void changeTextFont();
    void contPos(QRect oldRect, QRect newRect);
    void clipBoard();
    void chooseColor();
    void showFrameStyle(QPoint pos);
    void setFrameStyle(QListWidgetItem * item);
    void changeFrameWidth();
    void showLanguage();
    void bandResing(int value);
    void reportPageChanged(int index);
    void newReportPage();
    void deleteReportPage();
    void alignFields();
    void openRecentFile();
    void closeProgram();
};

#endif // MAINWINDOW_H
