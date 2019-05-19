#pragma once

#include "lcd_widget_base.h"

class Port;
class LCD;
struct LCDPhysicalSettings;
class LCDController;
class QPaintEvent;

class BC1604A : public LCDWidgetBase
{
public:
	BC1604A(QWidget* parent = nullptr);

	void initDecorators();

	const Port& getPort() const;
	Port& getPort();

	LCDPhysicalSettings const& getSettings() const override;
	void drawPort(QPainter& painter);
	void drawData(QPainter& painter);
	bool backlightState() const;

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	Port* __port;
	LCDController* __controller;
	LCD* __lcd;
	LCDPhysicalSettings* __settings;
	bool* __backlight;
};
