#ifndef HORIZONTALSCROLLBAR_H
#define HORIZONTALSCROLLBAR_H

#include <QFrame>

class QScrollBar;

class HorizontalScrollBar : public QFrame
{
    Q_OBJECT
public:
    explicit HorizontalScrollBar(QWidget *parent, QScrollBar *sampleScrollBar );
    void setSpace(int from, int to);
    void setHeight(int height);
    void setMinWidth(int width_min);
    void setMargin(int margin);
    void update(bool show);
    void update();
    bool isMin(int diff = 0);
    bool isMax(int diff = 0);
    int getDiff(bool fromMaxNotMin = true);
    int getValue();

signals:
    void rangeChange(int min, int max);
    void valueChange(int value);

public slots:
    void setRange(int min, int max);
    void setValue(int value);

protected:
    virtual void mousePressEvent(QMouseEvent *ev);
    virtual void mouseReleaseEvent(QMouseEvent *ev);
    virtual void mouseMoveEvent(QMouseEvent *ev);

private:
    int from, to;
    int width, width_min, height;
    int margin;
    int min, max;
    int value;
    int lastPos;
    bool isHidden;
    void recalcWidth();
};

#endif // HORIZONTALSCROLLBAR_H
