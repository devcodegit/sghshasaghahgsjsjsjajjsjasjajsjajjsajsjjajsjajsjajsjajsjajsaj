#include "smainwindow.h"
#include "SourceCode/uiconst.h"

#include <QFrame>
#include <QVBoxLayout>

SMainWindow::SMainWindow(QWidget *parent) : SWidget(parent)
{
    setMinimumSize(800,600);
    _pvLayout = new QVBoxLayout(this);
    _pvLayout->setSpacing(0);
    _pvLayout->setMargin(0);
    _pvLayout->setAlignment(Qt::AlignTop);
    createHeader();
    createMidle();
}

void SMainWindow::resizeEvent(QResizeEvent *ev)
{
    Q_UNUSED(ev);
    updateSize();
}

void SMainWindow::createHeader()
{
    if (!_pHeader)
    {
        _pHeader = new QFrame();
        _pHeader->setObjectName("HeaderMainWindow");
        _pHeader->setFixedHeight(SIZE_HEIGHT_HEADER);
        _pvLayout->addWidget(_pHeader, 1);
    }
}

void SMainWindow::createMidle()
{
    if (!_pMidle)
    {
        _pMidle = new QFrame();
        _pMidle->setObjectName("MidleMainWindow");
        _pvLayout->addWidget(_pMidle, 1);
    }

    if (!_pMidleOption)
    {
        _pMidleOption = new QFrame(_pMidle);
        _pMidleOption->move(0,0);
        _pMidleOption->setObjectName("MidleStyleOption");
        _pMidleOption->setFixedWidth(SIZE_WIDTH_OPTION);
        _pMidleOption->setFixedHeight(_pMidle->height());
    }

    if (!_pMidleSearch)
    {
        _pMidleSearch = new QFrame(_pMidle);
        _pMidleSearch->move(SIZE_WIDTH_OPTION, 0);
        _pMidleSearch->setFixedHeight(SIZE_HEIGHT_SEARCH);
        _pMidleSearch->setFixedWidth(_pMidle->width() - _pMidleOption->width());
    }

    if (!_pMidleResult)
    {
        _pMidleResult = new QFrame(_pMidle);
        _pMidleResult->move(SIZE_WIDTH_OPTION, SIZE_HEIGHT_SEARCH);
        _pMidleResult->setFixedSize(_pMidle->width() - _pMidleOption->width(),
                                    _pMidle->height() - _pMidleSearch->height());
    }
}

void SMainWindow::updateSize()
{
    if (_pMidleOption)
    {
        _pMidleOption->setFixedHeight(_pMidle->height());
    }

    if (_pMidleSearch)
    {
        _pMidleSearch->setFixedWidth(_pMidle->width() - SIZE_WIDTH_OPTION);
    }

    if (_pMidleResult)
    {
        _pMidleResult->setFixedSize(_pMidle->width() - _pMidleOption->width(),
                                    _pMidle->height() - _pMidleSearch->height());
    }
}
