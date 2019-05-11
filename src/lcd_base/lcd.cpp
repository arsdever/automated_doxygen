#include "lcd.h"
#include "lcd_controller.h"
#include "lcd_glass_panel.h"
#include "pin.h"
#include "../include/metric_macros.h"

#define PIN_DISTANCE (2.54 - PIN_WIDTH)

LCD::LCD(uint8_t w, uint8_t h, QWidget* parent)
	: QWidget(parent),
	__port(new Port),
	__glass_panel(new LCDGlassPanel(w, h, this)),
	__controller(new LCDController(w, h, *__port, __glass_panel, this))
{
	for (uint8_t i = 0; i < 16; ++i)
	{
		Pin* pin = new Pin(this);
		__port->push_back(pin);
		pin->move(i * NORMALIZE_X(PIN_DISTANCE + PIN_WIDTH) + NORMALIZE_X(8), 0);
	}

	connect(__port->at(LCDController::Pinout::E), SIGNAL(signalChanged(bool)), __controller, SLOT(portEnabled(bool)));
	connect(__controller, SIGNAL(writeChar(uint8_t, uint8_t, char)), __glass_panel, SLOT(writeChar(uint8_t, uint8_t, char)));

	setFixedSize(NORMALIZE_X(80), NORMALIZE_Y(36));
	__glass_panel->move(NORMALIZE_X(5.2), NORMALIZE_Y(10.75));
}

const Port& LCD::getPort() const
{
	return *__port;
}

Port& LCD::getPort()
{
	return *__port;
}
