#pragma once

#include <QWidget>

class LCDGlassPanel;
class QPaintEvent;

class LCDGlassPanelBlock5x8 : public QWidget
{
public:
	LCDGlassPanelBlock5x8(LCDGlassPanel* parent);
	
	void setSymbol(char symb);

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	LCDGlassPanel* __owner;
	uint64_t __symbol;
};

