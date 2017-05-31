#ifndef LEFTPANEL_H
#define LEFTPANEL_H

#include <QFrame>

class QSvgWidget;
class QLabel;
class QVBoxLayout;

class LeftPanelItem : public QFrame
{
    Q_OBJECT
public:
    enum {
        ID_HOME,
        ID_MANAGEMENT,
        ID_SETTING
    };
    explicit LeftPanelItem(QWidget *parent = 0);
    void setTitle(const QString &title);
    void setIcon(const QString &svgIcon, QSize size);
    void setId(int id);
signals:
    void clicked();
protected:
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void enterEvent(QEvent *);
    virtual void leaveEvent(QEvent *);
private:
    QSvgWidget *icon;
    QLabel *title;
    int id;

};


class LeftPanel : public QWidget
{
    Q_OBJECT
public:
    explicit LeftPanel(QWidget *parent = 0);
    void addItem(const QString &svgIcon, const QString &title, int id);

signals:

public slots:
private:
    QVBoxLayout *mainLayout = 0;
};

#endif // LEFTPANEL_H
