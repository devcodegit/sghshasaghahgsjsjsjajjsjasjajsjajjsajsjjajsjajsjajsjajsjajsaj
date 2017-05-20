#ifndef SVGWIDGET_H
#define SVGWIDGET_H

#include <QSvgWidget>
#include <QMouseEvent>
#include <QFrame>

class SvgWidget : public QSvgWidget
{
    Q_OBJECT
public:
    explicit SvgWidget(QWidget *parent = 0, QString imageNormal = "", QString imageHover = "", QString styleFocus = "", QString imageDisabled = "");
    void setImageNormal(QString imageName);
    void setImageHover(QString imageName);
    void setImageDisable(QString imageName);

signals:
    void onClicked();
    void onLeave();
    void onEnter();
    void onDrag();

public slots:
    void setStyleNormal();
    void setStyleHover();
    void setDisabled(bool disabled);

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void focusInEvent(QFocusEvent *ev);
    virtual void focusOutEvent(QFocusEvent *ev);

private:
    QString imageNormal, imageHover;
    QString styleFocus;
    QString imageDisabled;
    bool m_isDisabled;
    int x1,y1;
    bool m_isMousePress;
    QFrame *frameFocus;
};

#endif // SVGWIDGET_H
