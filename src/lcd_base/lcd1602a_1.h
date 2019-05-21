#pragma once

#include "lcd_widget_base.h"

struct LCDPhysicalSettings;
class LCD;
class QPainter;

class LCD1602A_1 : public LCDWidgetBase
{
	
	Q_OBJECT

public:
	LCD1602A_1(QWidget* parent = nullptr);
	LCDPhysicalSettings const& getSettings() const override;

protected:
	bool isDisplayOn() const override;
	void drawData(QPainter& painter) override;

private:
	void initDecorators();
	bool backlightState() const;

private slots:
	void updateDisplayConfig();

private:
	LCD* __lcd;
	LCDPhysicalSettings* __settings;
	bool* __backlight;
};
