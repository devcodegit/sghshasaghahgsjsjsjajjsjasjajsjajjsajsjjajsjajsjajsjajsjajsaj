#ifndef SCONSTANTMENU_H
#define SCONSTANTMENU_H

#include <QWidget>
#include <QMap>

class QFrame;
class QVBoxLayout;

class SConstantMenu : public QWidget
{
    Q_OBJECT
public:
    explicit SConstantMenu(QWidget *parent = 0);
    void addItem(const QString &title, QWidget *preview_content = 0);

protected:
    virtual bool eventFilter(QObject *object, QEvent *event);

signals:

public slots:

private:
    QFrame *preview = 0;
    QVBoxLayout *itemLayout = 0;
    QMap<QFrame*, QWidget*> mapItemContent;


private:
    QFrame *createItem(const QString &title, bool hasIcon = false);
};

#endif // SCONSTANTMENU_H
