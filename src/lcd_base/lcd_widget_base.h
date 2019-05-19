#pragma once

#include <QWidget>
#include <QUuid>

struct LCDPhysicalSettings;
class LCDController;
class DecoratorBase;
class Port;

class QPaintEvent;
class QMouseEvent;

class LCDWidgetBase : public QWidget
{
public:
	LCDWidgetBase(QWidget* parent);

	virtual inline QUuid const& getUuid() const { return __uuid; }

	Port const& getPort() const;
	Port& getPort();

	LCDController const& getController() const;
	LCDController& getController();

protected:
	virtual LCDPhysicalSettings const& getSettings() const = 0;
	virtual void drawData(QPainter& painter) = 0;
	virtual bool isDisplayOn() const = 0;
	void addDecorator(DecoratorBase* decor);
	void decorate(QPainter& painter);

	void paintEvent(QPaintEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);

private:
	QUuid __uuid;
	Port* __port;
	QList<DecoratorBase*> __decorations;
	LCDController* __controller;
	QPoint __drag_started;
};

