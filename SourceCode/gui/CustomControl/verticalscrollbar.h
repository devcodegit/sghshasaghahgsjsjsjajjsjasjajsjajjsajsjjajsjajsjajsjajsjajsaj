#ifndef VERTICALSCROLLBAR_H
#define VERTICALSCROLLBAR_H

#include <QFrame>

class QScrollBar;

class VerticalScrollbar : public QFrame
{
    Q_OBJECT
public:
    explicit VerticalScrollbar(QWidget *parent, QScrollBar *sampleScrollbar);
    void setSpace(int from, int to);
    void setStyleBg();
    void setWidthBg(int _width);
    void setWidth(int _width);
    void setMinHeight(int height_min);
    void setMargin(int margin);
    void update(bool show);
    void update();
    bool isMax(int diff = 0);
    bool isMin(int diff = 0);
    int getDiff(bool fromMaxNotMin = true);
    int getValue();

signals:
    void rangeChanged(int min, int max);
    void valueChanged(int value);
    void onMouseRelease();
    void onMousePress();

public slots:
    void setRange(int min, int max);
    void setValue(int value);

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void enterEvent(QEvent *);
    virtual void leaveEvent(QEvent *);
    virtual bool eventFilter(QObject *obj, QEvent *ev);

private:
    QFrame *thumb;
    int from, to;
    int widthBg;
    int height, height_min, _width;
    int margin;
    int min, max;
    int value;
    int lastPos;
    bool isHidden;
    bool isForceState;
#ifdef Q_OS_MAC
    bool isMousePress;
#endif
    void recalcHeight();
};

#endif // VERTICALSCROLLBAR_H
