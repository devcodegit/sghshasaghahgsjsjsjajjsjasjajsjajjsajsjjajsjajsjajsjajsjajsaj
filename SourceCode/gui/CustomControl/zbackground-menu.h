#ifndef ZBACKGROUNDMENU_H
#define ZBACKGROUNDMENU_H

#include "background_menu_utils.h"

#include <QLabel>

class ZBackgroundMenu : public QLabel
{
    Q_OBJECT
public:
    explicit ZBackgroundMenu(const int &width = 0,
                             const int &height = 0,
                             QWidget *parent = 0,
                             BgMenuArrowPosition arrowPos = BgMenuArrowPosition::None,
                             int posDelta = 0);
    void setWidth(const int &width);
    void setHeight(const int &height);
    void setSize(const int &width, const int &height);
signals:

public slots:

private:
    QPixmap drawBackground(const int &w, const int &h);

private:
    BgMenuArrowPosition _arrowPos;
    int _posDelta;
    QLabel *_plbBackground;
};

#endif // ZBACKGROUNDMENU_H
