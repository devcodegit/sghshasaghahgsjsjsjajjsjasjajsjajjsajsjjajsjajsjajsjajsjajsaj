#include "background_menu_utils.h"

#include <QPainter>

#define SIZE_CORNER             8
#define SIDE_IMG                QString(":/Icon/Image/bg_popup_middle.png")
#define CORNER_IMG              QString(":/Icon/Image/bg_popup_corner.png")
#define ARROW_IMG               QString(":/Icon/Image/bg_popup_arrow.png")

BackgroundMenuUtils::BackgroundMenuUtils()
{

}

QPixmap BackgroundMenuUtils::createBackground(int w, int h, BgMenuArrowPosition arrowPos, int posDelta)
{
    QImage imgSide(SIDE_IMG);
    QImage imgCorner(CORNER_IMG);
    QImage imgArrow(ARROW_IMG);

    int padding = imgSide.height();

    int paddingTop = padding;
    int paddingBottom = (arrowPos == BgMenuArrowPosition::BottomRight) ?
                imgArrow.height() : padding;
    int paddingLeft = padding;
    int paddingRight = padding;

    //
    // Delta = Arrow size - Side size
    // Delta will be 0 if edge doesn't have arrow
    int deltaBottom = paddingBottom - padding;

    QImage image(w, h, QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    // Create painter
    QPainter painter(&image);

    // Draw white background
    int radius = SIZE_CORNER - paddingTop + 1;
    int horPadding = paddingLeft + paddingRight;
    int verPadding = paddingTop + paddingBottom;
    int bgW = w - horPadding;
    int bgH = h - verPadding;
    painter.setBrush(QBrush(Qt::white));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(paddingTop, paddingTop, bgW, bgH, radius, radius);

    int nRepeat = 0;
    QTransform trans;
    trans.rotate(90);

    // Draw top left corner
    painter.drawImage(0, 0, imgCorner);

    // Draw top line
    nRepeat = w - SIZE_CORNER - 1;
    for (int x = SIZE_CORNER; x <= nRepeat; ++x) {
        painter.drawImage(x, 0, imgSide);
    }

    // Draw top right corner
    imgCorner = imgCorner.transformed(trans);
    painter.drawImage(w - SIZE_CORNER, 0, imgCorner);

    // Draw right line
    imgSide = imgSide.transformed(trans);
    nRepeat = h - SIZE_CORNER - 1 - deltaBottom;
    for (int y = SIZE_CORNER; y <= nRepeat; ++y) {
        painter.drawImage(w - paddingRight, y, imgSide);
    }

    // Draw bottom right corner
    imgCorner = imgCorner.transformed(trans);
    painter.drawImage(w - SIZE_CORNER, nRepeat + 1, imgCorner);

    // Draw bottom line
    imgSide = imgSide.transformed(trans);
    nRepeat = w - SIZE_CORNER - 1;
    for (int x = SIZE_CORNER; x <= nRepeat; ++x) {
        painter.drawImage(x, h - paddingBottom, imgSide);
    }

    // Draw bottom left corner
    imgCorner = imgCorner.transformed(trans);
    painter.drawImage(0, h - SIZE_CORNER - deltaBottom, imgCorner);

    // Draw left line
    imgSide = imgSide.transformed(trans);
    nRepeat = h - SIZE_CORNER - deltaBottom - 1;
    for (int y = SIZE_CORNER; y <= nRepeat; ++y) {
        painter.drawImage(0, y, imgSide);
    }

    switch (arrowPos)
    {
    case BgMenuArrowPosition::BottomRight:
        painter.drawImage(bgW - (posDelta + imgArrow.width()), bgH + 3, imgArrow);
        break;
    }

    return QPixmap::fromImage(image);
}

