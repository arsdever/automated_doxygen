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

	const Port& getPort() const;
	Port& getPort();

	LCDPhysicalSettings const& getSettings() const override;
	void drawPCB(QPainter& painter) override;
	void drawPort(QPainter& painter) override;
	void drawDecorations(QPainter& painter) override;
	void drawScreen(QPainter& painter) override;

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	Port* __port;
	LCDController* __controller;
	LCD* __lcd;
	LCDPhysicalSettings* __settings;
};
