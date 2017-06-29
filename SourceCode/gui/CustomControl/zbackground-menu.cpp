#include "zbackground-menu.h"
#include "background_menu_utils.h"

ZBackgroundMenu::ZBackgroundMenu(const int &width, const int &height, QWidget *parent,
                                 BgMenuArrowPosition arrowPos,
                                 int posDelta) : QLabel(parent)
{
    _arrowPos = arrowPos;
    _posDelta = posDelta;

    int w_new = width;
    int h_new = height;
    if (w_new % 2 != 0) w_new++;
    if (h_new % 2 != 0) h_new++;

    setFixedSize(w_new, h_new);
    setContentsMargins(0,0,0,0);
    setObjectName("ZBackgroundMenu");

    _plbBackground = new QLabel(this);
    _plbBackground->setFixedSize(w_new, h_new);
    _plbBackground->move(0,0);
    _plbBackground->setObjectName("ZBackgroundMenuBackground");
    _plbBackground->setPixmap(drawBackground(w_new, h_new));
}

void ZBackgroundMenu::setWidth(const int &width)
{
    int w_new = width;
    if (w_new % 2 != 0) w_new++;
    setFixedWidth(w_new);
    _plbBackground->setFixedWidth(w_new);
}

void ZBackgroundMenu::setHeight(const int &height)
{
    int h_new = height;
    if (h_new % 2 != 0) h_new++;
    setFixedHeight(h_new);
    _plbBackground->setFixedHeight(h_new);
}

void ZBackgroundMenu::setSize(const int &width, const int &height)
{
    setWidth(width);
    setHeight(height);
    _plbBackground->setPixmap(drawBackground(_plbBackground->width(), _plbBackground->height()));
}

QPixmap ZBackgroundMenu::drawBackground(const int &w, const int &h)
{
    return BackgroundMenuUtils::createBackground(w, h, _arrowPos, _posDelta);
}

