#ifndef DROPDOWNWIDGET_H
#define DROPDOWNWIDGET_H

#include <QWidget>
#include <QList>

class QLabel;
class QVBoxLayout;
class QFrame;
class SvgWidget;

class DropdownWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DropdownWidget(QWidget *parent = 0);
    void addContent(const QString &titleContent);
    void setTitle(const QString &title);

protected:
    virtual bool eventFilter(QObject *object, QEvent *event);
    virtual void resizeEvent(QResizeEvent *event);

signals:

public slots:

private slots:
    void onDropdown();

private:
    QVBoxLayout *contentLayout  = 0;
    QLabel *title = 0;
    QFrame *titleFrame = 0, *contentFrame = 0;
    QList<QLabel*> listContent;
    bool isDropdownShow = false;
    SvgWidget *iconDropdown = 0;

};

#endif // DROPDOWNWIDGET_H
