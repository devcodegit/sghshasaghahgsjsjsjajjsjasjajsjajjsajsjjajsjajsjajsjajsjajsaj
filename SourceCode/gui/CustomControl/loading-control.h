#ifndef LOADINGCONTROL_H
#define LOADINGCONTROL_H

#include <QWidget>
#include <QTimer>

class QLabel;

class LoadingControl : public QWidget
{
    Q_OBJECT

public:
    explicit LoadingControl(int sizeImg, int sizeTotal, bool bgLight = true, QWidget *parent = 0);
    ~LoadingControl();

    void showLoading();
    void hideLoading();

public slots:
    void onTimer();

protected:
    virtual void resizeEvent(QResizeEvent *ev);
    virtual void paintEvent(QPaintEvent *ev);

private:
    void createLoading(int nStep, int mSize, int time, bool bgLight);

    QLabel *mLoading = NULL;
    QTimer mTimer;

    QList<QPixmap> pixmaps;
    int mnStep;
    int mDelay;
    int mCurrentStep;
};

#endif // LOADINGCONTROL_H
