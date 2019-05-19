#include "lcd_widget_base.h"

#include <lcd_decorators.h>
#include <QMouseEvent>

LCDWidgetBase::LCDWidgetBase(QWidget* parent)
	: QWidget(parent),
	__uuid(QUuid::createUuid())
{
	setAttribute(Qt::WA_NoSystemBackground);
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlag(Qt::WindowSystemMenuHint);
	setWindowFlag(Qt::FramelessWindowHint);
}

void LCDWidgetBase::addDecorator(DecoratorBase* decor)
{
	__decorations.push_back(decor);
}

DecoratorBase* LCDWidgetBase::decoratorAt(uint32_t index)
{
	if (index < __decorations.size())
		return __decorations.at(index);

	return nullptr;
}

void LCDWidgetBase::decorate(QPainter& painter)
{
	for (DecoratorBase* decor : __decorations) decor->decorate(painter);
}

void LCDWidgetBase::mousePressEvent(QMouseEvent* event)
{
	setMouseTracking(true);
	__drag_started = event->pos();
	QWidget::mousePressEvent(event);
}

void LCDWidgetBase::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		move(event->pos() + pos() - __drag_started);
	}
	else
	{
		setMouseTracking(false);
	}
	QWidget::mouseMoveEvent(event);
}

void LCDWidgetBase::mouseReleaseEvent(QMouseEvent* event)
{
	setMouseTracking(true);
	QWidget::mouseReleaseEvent(event);
}
