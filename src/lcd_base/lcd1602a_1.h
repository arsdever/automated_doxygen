#pragma once

#include "lcd_widget_base.h"

class Port;
class LCD;
struct LCDPhysicalSettings;
class LCDController;
class QPaintEvent;

class LCD1602A_1 : public LCDWidgetBase
{
public:
	LCD1602A_1(QWidget* parent = nullptr);

	void initDecorators();
	bool backlightState() const;

	const Port& getPort() const;
	Port& getPort();

	LCDPhysicalSettings const& getSettings() const override;
	void drawPort(QPainter& painter);
	void drawData(QPainter& painter);

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	Port* __port;
	LCDController* __controller;
	LCD* __lcd;
	LCDPhysicalSettings* __settings;
	bool* __backlight;
};
