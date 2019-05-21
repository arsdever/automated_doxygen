#include "lcd1602a_1.h"

#include "pin_widget.h"

#include <lcd_core.h>
#include <lcd_measurements.h>
#include <metric_macros.h>
#include <lcd_decorators.h>

#include <QPainter>

#define H_DOTS 5
#define V_DOTS 8
#define TURNED_OFF QColor(0,0,0,15)
#define TURNED_ON QColor(0,0,0,210)
#define SCREEN_HOLDER_CUT_WIDTH 10
#define SCREEN_HOLDER_CUT_HEIGHT 1.4

LCD1602A_1::LCD1602A_1(QWidget* parent)
	: LCDWidgetBase(parent),
	__lcd(new LCD(16, 2, &getController(), this)),
	__settings(new LCDPhysicalSettings{ .54, .6, .05, .05, 2.9, 5.15, .62, .7, 55.7, 11, 63.6, 14.5, 38.1,1 , 80, 36, 2.8, 75.4, 31.4, 8, 70.7, 23.8 }),
	__backlight(nullptr)
{
	double pin_distance = getSettings().__pinout_length / 15;
	for (uint8_t i = 0; i < 16; ++i)
	{
		PinWidget* pinw = new PinWidget(getPort().at(i), this);
		pinw->move(i * NORMALIZE_X(pin_distance) + NORMALIZE_X(getSettings().__pin_margin), 0);
	}
	setFixedSize(NORMALIZE_X(getSettings().__pcb_width), NORMALIZE_Y(getSettings().__pcb_height));
	connect(getPort().at(LCDController::Pinout::LEDM), SIGNAL(signalChanged(bool)), this, SLOT(updateDisplayConfig()));
	connect(getPort().at(LCDController::Pinout::LEDP), SIGNAL(signalChanged(bool)), this, SLOT(updateDisplayConfig()));
	initDecorators();
}

LCDPhysicalSettings const& LCD1602A_1::getSettings() const
{
	return *__settings;
}

bool LCD1602A_1::isDisplayOn() const
{
	return true;
}

void LCD1602A_1::drawData(QPainter& painter)
{
	painter.save();
	double x = NORMALIZE_X((getSettings().__pcb_width - getSettings().__viewport_width) / 2);
	double y = NORMALIZE_Y((getSettings().__pcb_height - getSettings().__viewport_height) / 2);
	painter.translate(x, y);
	double offsetX = NORMALIZE_X((getSettings().__viewport_width - getSettings().__blocks_width) / 2);
	double offsetY = NORMALIZE_Y((getSettings().__viewport_height - getSettings().__blocks_height) / 2);
	painter.translate(offsetX, offsetY);
	for (uint8_t r = 0; r < __lcd->rows(); ++r)
	{
		for (uint8_t c = 0; c < __lcd->columns(); ++c)
		{
			uint64_t symbol = __lcd->getBlock(c, r);

			for (uint8_t y = 0; y < 8; symbol >>= 8, ++y)
			{
				uint8_t line = symbol & 0xff;
				uint8_t x = 0;
				for (; x < 5; ++x, line >>= 1)
				{
					double pos_x_mm = (4 - x) * (getSettings().__pixel_width + getSettings().__pixel_h_spacing);
					double pos_x = NORMALIZE_X(pos_x_mm);
					double pos_y_mm = (7 - y) * (getSettings().__pixel_height + getSettings().__pixel_v_spacing);
					double pos_y = NORMALIZE_Y(pos_y_mm);
					double width = NORMALIZE_X(getSettings().__pixel_width);
					double height = NORMALIZE_Y(getSettings().__pixel_height);
					double block_offset_x = NORMALIZE_X(c * (getSettings().__block_width + getSettings().__block_h_spacing));
					double block_offset_y = NORMALIZE_Y(r * (getSettings().__block_height + getSettings().__block_v_spacing));
					QRectF pixel(pos_x + block_offset_x, pos_y + block_offset_y, width, height);
					if (line & 1)
						painter.fillRect(pixel, TURNED_ON);
					else
						painter.fillRect(pixel, TURNED_OFF);
				}
			}
		}
	}
	painter.restore();
}

void LCD1602A_1::initDecorators()
{
	GlassCaseDecoratorOptions* decor1 = new GlassCaseDecoratorOptions;
	decor1->__outer_area.setTopLeft(QPointF(NORMALIZE_X((getSettings().__pcb_width - getSettings().__border_width) / 2), NORMALIZE_Y((getSettings().__pcb_height - getSettings().__border_height) / 2)));
	decor1->__outer_area.setSize(QSizeF(NORMALIZE_X(getSettings().__border_width), NORMALIZE_Y(getSettings().__border_height)));
	decor1->__inner_area.setTopLeft(QPointF(NORMALIZE_X((getSettings().__pcb_width - getSettings().__viewport_width) / 2), NORMALIZE_Y((getSettings().__pcb_height - getSettings().__viewport_height) / 2)));
	decor1->__inner_area.setSize(QSizeF(NORMALIZE_X(getSettings().__viewport_width), NORMALIZE_Y(getSettings().__viewport_height)));
	decor1->__cut_area_size.setWidth(NORMALIZE_X(SCREEN_HOLDER_CUT_WIDTH));
	decor1->__cut_area_size.setHeight(NORMALIZE_Y(SCREEN_HOLDER_CUT_HEIGHT));
	PCBDecoratorOptions* decor2 = new PCBDecoratorOptions;
	decor2->__pcb_rect = rect();
	decor2->__holes_radius_x = NORMALIZE_X(getSettings().__pcb_hole_diameter / 2.0);
	decor2->__holes_radius_y = NORMALIZE_Y(getSettings().__pcb_hole_diameter / 2.0);
	decor2->__holes_distance_x = NORMALIZE_X(getSettings().__pcb_hole_h_distance);
	decor2->__holes_distance_y = NORMALIZE_Y(getSettings().__pcb_hole_v_distance);
	ScreenDecoratorOptions* decor3 = new ScreenDecoratorOptions;
	decor3->__glass.setTopLeft(QPointF(NORMALIZE_X((getSettings().__pcb_width - getSettings().__viewport_width) / 2), NORMALIZE_Y((getSettings().__pcb_height - getSettings().__viewport_height) / 2)));
	decor3->__glass.setSize(QSizeF(NORMALIZE_X(getSettings().__viewport_width), NORMALIZE_Y(getSettings().__viewport_height)));
	__backlight = &decor3->__backlight;
	addDecorator(new PCBDecorator(decor2));
	addDecorator(new ScreenDecorator(decor3));
	addDecorator(new GlassCaseDecorator(decor1));
}

bool LCD1602A_1::backlightState() const
{
	return !getPort().at(LCDController::LEDM)->getSignal() && getPort().at(LCDController::LEDP)->getSignal();
}

void LCD1602A_1::updateDisplayConfig()
{
	if (__backlight == nullptr)
		return;

	*__backlight = backlightState();
}
