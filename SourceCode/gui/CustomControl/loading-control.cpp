#include "loading-control.h"
#include <QPainter>
#include <QLabel>

LoadingControl::LoadingControl(int sizeImg, int sizeTotal, bool bgLight, QWidget *parent) : QWidget(parent)
{
    mCurrentStep = 0;
    if (!mLoading) {
        mLoading = new QLabel(this);
        mLoading->setObjectName("ZFrameGiphy_Loading");
        mLoading->setAlignment(Qt::AlignCenter);
        mLoading->setFixedSize(sizeTotal,sizeTotal);
        mLoading->hide();
    }

    createLoading(40, sizeImg, 760, bgLight);

    mTimer.setInterval(mDelay);
    mTimer.setSingleShot(false);
    connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimer()));
    setFixedSize(sizeTotal, sizeTotal);
}

LoadingControl::~LoadingControl()
{

}

void LoadingControl::showLoading()
{
    if (mLoading) {
        mTimer.start();
        mLoading->show();
        mLoading->raise();
        show();
    }
}

void LoadingControl::hideLoading()
{
    if (mLoading) {
        mTimer.stop();
        mCurrentStep = 0;
        mLoading->lower();
        mLoading->hide();
        hide();
    }
}

void LoadingControl::onTimer()
{
    if (!visibleRegion().isEmpty()) {
        if (mLoading) {
            mLoading->setPixmap(pixmaps.at(mCurrentStep));
            mLoading->repaint();
        }
    }
    else {
        if (mTimer.isActive()) {
            mTimer.stop();
        }
    }
    mCurrentStep++;
    if (mCurrentStep >= mnStep) {
        mCurrentStep = 0;
    }
}

void LoadingControl::resizeEvent(QResizeEvent *ev)
{
    if (mLoading){
        mLoading->setFixedSize(this->size());
    }
}

void LoadingControl::paintEvent(QPaintEvent *ev)
{
    QWidget::paintEvent(ev);
    if (mLoading) {
        if (!mTimer.isActive()) {
            mTimer.start();
        }
    }
}

void LoadingControl::createLoading(int nStep, int size, int time, bool bgLight)
{
    mnStep = nStep;
    QPixmap pxLoading;
    if (bgLight) {
        pxLoading = QPixmap(":/Icon/Image/loading_blue_28x28.svg").scaled(size, size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    }
    else {
        pxLoading = QPixmap(":/Icon/Image/loading_white_28x28.svg").scaled(size, size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    }
    int step = 360/nStep;
    mDelay = time/nStep;
    QPixmap pxTemp = pxLoading;
    for (int i=0; i<nStep; i++) {
        pixmaps.append(pxTemp);
        QTransform trans;
        trans.translate(pxLoading.width()/2.0 , pxLoading.height()/2.0);
        trans.rotate(step*(i+1));
        trans.translate(-pxLoading.width()/2.0 , -pxLoading.height()/2.0);
        pxTemp = pxLoading.transformed(trans, Qt::SmoothTransformation);
    }
    pixmaps.append(pxTemp);
}

