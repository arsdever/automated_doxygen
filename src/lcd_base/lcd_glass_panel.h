#ifndef LCD_MODEL_H
#define LCD_MODEL_H

#include <QWidget>
#include <QList>
#include <stdint.h>

class Pin;
class QPaintEvent;
class LCDGlassPanelBlock5x8;

#define ZOOM_FACTOR 2
#define TO_INCH(mm) ((mm) * 0.0393700787)
#define NORMALIZE_X(value) (logicalDpiX() * (TO_INCH(value)))
#define NORMALIZE_Y(value) (logicalDpiY() * (TO_INCH(value)))

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

private slots:
	void pinSignalChanged();

private:
	int __width;
	int __height;
	QList<LCDGlassPanelBlock5x8*> __blocks;
};

#endif