#pragma once

#include <QWidget>

struct LCDPhysicalSettings;

class LCDWidgetBase : public QWidget
{
public:
	LCDWidgetBase(QWidget* parent) : QWidget(parent) {}

	virtual LCDPhysicalSettings const& getSettings() const = 0;
	virtual void drawPCB(QPainter& painter) = 0;
	virtual void drawPort(QPainter& painter) = 0;
	virtual void drawDecorations(QPainter& painter) = 0;
	virtual void drawScreen(QPainter& painter) = 0;
};

