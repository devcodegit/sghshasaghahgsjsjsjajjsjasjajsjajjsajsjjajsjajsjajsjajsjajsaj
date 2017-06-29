#ifndef BACKGROUNDMENUUTILS_H
#define BACKGROUNDMENUUTILS_H

#include <QPixmap>

#define BGMENU_PAD                  3
#define BGMENU_ARR_PAD              10

#define BGMENU_HOR_PAD              (BGMENU_PAD * 2)
#define BGMENU_VER_PAD              (BGMENU_PAD * 2) // Without arrow at top and bottom
#define BGMENU_WITH_ARR_VER_PAD     (BGMENU_PAD + BGMENU_ARR_PAD) // With arrow at top or bottom

enum class BgMenuArrowPosition
{
    None,
//    TopLeft,
//    TopRight,
//    BottomLeft,
    BottomRight,
};

class BackgroundMenuUtils
{
private:


public:
    BackgroundMenuUtils();

    /**
     * @brief Create background menu pixmap
     * @param w
     * @param h
     * @param arrowPos
     *      Currently supported only BottomRight position
     * @param posDelta
     * @return
     */
    static QPixmap createBackground(int w, int h,
                                 BgMenuArrowPosition arrowPos = BgMenuArrowPosition::None,
                                 int posDelta = 0);
};

#endif // BACKGROUNDMENUUTILS_H
