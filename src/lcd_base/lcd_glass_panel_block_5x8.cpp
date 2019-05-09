#include "lcd_glass_panel_block_5x8.h"
#include "lcd_glass_panel.h"

#include <QPainter>

#define H_DOTS (double)5
#define V_DOTS (double)8
#define PIXEL_WIDTH (.54 *  (ZOOM_FACTOR))
#define PIXEL_HEIGHT (.6 *  (ZOOM_FACTOR))
#define PIXEL_MARGIN (.05 * (ZOOM_FACTOR))
#define TURNED_OFF QColor(0,0,0,48)
#define TURNED_ON QColor(0,0,0,210)

LCDGlassPanelBlock5x8::LCDGlassPanelBlock5x8(LCDGlassPanel* parent)
	: QWidget(parent),
	__owner(parent),
	__symbol(0)
{
	double w = NORMALIZE_X(PIXEL_WIDTH * H_DOTS + PIXEL_MARGIN * (H_DOTS - 1));
	double h = NORMALIZE_Y(PIXEL_HEIGHT * V_DOTS + PIXEL_MARGIN * (V_DOTS - 1));
	setFixedSize(QSizeF(w, h).toSize());
}

void LCDGlassPanelBlock5x8::setSymbol(char symbol)
{ 
	__symbol = __owner->getSymbol(symbol);
}

void LCDGlassPanelBlock5x8::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QPainter ptr(this);
	ptr.setRenderHint(QPainter::HighQualityAntialiasing);
	uint64_t magic = __symbol;
	for (uint8_t y = 0; y < 8; magic >>= 8, ++y)
	{
		uint8_t line = magic & 0xff;
		uint8_t x = 0;
		for (; x < 5; ++x, line >>= 1)
		{
			double pos_x_mm = (4 - x) * (PIXEL_WIDTH + PIXEL_MARGIN);
			double pos_x = NORMALIZE_X(pos_x_mm);
			double pos_y_mm = (7 - y) * (PIXEL_HEIGHT + PIXEL_MARGIN);
			double pos_y = NORMALIZE_Y(pos_y_mm);
			double width = NORMALIZE_X(PIXEL_WIDTH);
			double height = NORMALIZE_Y(PIXEL_HEIGHT);
			QRectF pixel(pos_x, pos_y, width, height);
			if (line & 1) 
				ptr.fillRect(pixel, TURNED_ON);
			else
				ptr.fillRect(pixel, TURNED_OFF);
		}
	}
}