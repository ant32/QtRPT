#ifndef QLABELEX_H
#define QLABELEX_H

#include <QLabel>

class QLabelEx : public QLabel
{
    Q_OBJECT
public:
    QLabelEx(QWidget *parent = 0);
    QLabelEx(const QString &Text, QWidget *parent = 0);
    ~QLabelEx();
    void setHoverText(bool bHover);
private:
    bool m_bHover;
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mouseReleaseEvent(QMouseEvent *);
signals:
    void clicked();
};
#endif
