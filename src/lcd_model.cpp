#include "lcd_model.h"

#include <QPainter>
#include <QPaintEvent>

LCDModel::LCDModel(int width, int height, QWidget *parent)
    : QWidget(parent),
      __font("Consolas"),
      __metrics(__font),
      __width(width),
      __height(height)
{
    setFixedSize(__width * __metrics.width('0') + (__width + 1) * __font.letterSpacing(), __height * __metrics.height() + (__height + 1) * __metrics.lineSpacing());
    __font.setLetterSpacing(QFont::AbsoluteSpacing, 5);
}

void LCDModel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(234, 254, 214));
    int x = __font.letterSpacing();
    int y = __metrics.lineSpacing();
    for (int i = 0; i < __width; ++i, x += __metrics.width('0') + __font.letterSpacing())
    {
        for (int j = 0; j < __height; ++j, y += __metrics.height() + __metrics.lineSpacing())
        {
            painter.fillRect(QRect(x, y, __metrics.width('0'), __metrics.height()), QColor(195, 230, 185));
        }
    }
}