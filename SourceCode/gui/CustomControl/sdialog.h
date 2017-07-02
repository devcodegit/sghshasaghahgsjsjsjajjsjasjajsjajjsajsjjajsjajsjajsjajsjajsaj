#ifndef SDIALOG_H
#define SDIALOG_H

#include <QWidget>

class QFrame;
class QLabel;
class SvgWidget;

class SDialog : public QWidget
{
    Q_OBJECT
public:
    explicit SDialog(QWidget *parent = 0);
    void setParent(QWidget *parent);
    void setContent(QWidget *content);
    void setWindowTitle(const QString &title);
    void updateContentSize(QSize size);
    void enableResize(bool enable);

protected:
    virtual bool eventFilter(QObject *object, QEvent *event);
    virtual void resizeEvent(QResizeEvent *event);

signals:

public slots:

private:
    QFrame *background = 0;
    QFrame *content = 0;
    QWidget *parent = 0;
    QLabel *titleBar = 0;
    SvgWidget *closeButton = 0;
    bool _enableResize = false;
    QWidget *currentContent = 0;
};

#endif // SDIALOG_H
