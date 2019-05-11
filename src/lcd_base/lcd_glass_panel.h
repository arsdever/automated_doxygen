#ifndef LCD_MODEL_H
#define LCD_MODEL_H

#include <QWidget>
#include <QList>
#include "../include/metric_macros.h"

class Pin;
class QPaintEvent;
class LCDGlassPanelBlock5x8;

class LCDGlassPanel : public QWidget
{

	Q_OBJECT

public:
	LCDGlassPanel(int width, int height, QWidget* parent = nullptr);
	~LCDGlassPanel();


	uint64_t getSymbol(char symb);

protected:
	virtual QPoint calculatePinPosition(int i);
	virtual uint64_t getCustomSymbol(char symb);

protected:
	void paintEvent(QPaintEvent* event);

public slots:
	void writeChar(uint8_t x, uint8_t y, char ch);
	void shiftToLeft();
	void shiftToRight();

private slots:
	void pinSignalChanged();

private:
	int __width;
	int __height;
	QList<LCDGlassPanelBlock5x8*> __blocks;
};

#endif