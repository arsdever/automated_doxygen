#pragma once

#include <QWidget>
#include <QUuid>

struct LCDPhysicalSettings;
class DecoratorBase;

class LCDWidgetBase : public QWidget
{
public:
	LCDWidgetBase(QWidget* parent);

	virtual inline QUuid const& getUuid() const { return __uuid; }

	virtual LCDPhysicalSettings const& getSettings() const = 0;

protected:
	void addDecorator(DecoratorBase* decor);
	DecoratorBase* decoratorAt(uint32_t index);
	void decorate(QPainter& painter);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);

private:
	QUuid __uuid;
	QList<DecoratorBase*> __decorations;
	QPoint __drag_started;
};

