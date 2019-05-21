#include "lcd_widget_base.h"

#include <lcd_core.h>

#include <lcd_decorators.h>
#include <QMouseEvent>
#include <QPainter>

LCDWidgetBase::LCDWidgetBase(QWidget* parent)
	: QWidget(parent),
	__port(new Port),
	__controller(new LCDController(16, 2, *__port, this)),
	__uuid(QUuid::createUuid())
{
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlag(Qt::FramelessWindowHint);

	connect(__port->at(LCDController::Pinout::E), SIGNAL(signalChanged(bool)), __controller, SLOT(portEnabled(bool)));
	connect(__controller, SIGNAL(changed()), this, SLOT(update()));
}

const Port& LCDWidgetBase::getPort() const
{
	return *__port;
}

Port& LCDWidgetBase::getPort()
{
	return *__port;
}

LCDController const& LCDWidgetBase::getController() const
{
	return *__controller;
}

LCDController& LCDWidgetBase::getController()
{
	return *__controller;
}

void LCDWidgetBase::addDecorator(DecoratorBase* decor)
{
	__decorations.push_back(decor);
}

void LCDWidgetBase::decorate(QPainter& painter)
{
	for (DecoratorBase* decor : __decorations) decor->decorate(painter);
}

void LCDWidgetBase::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::HighQualityAntialiasing);
	painter.setPen(Qt::NoPen);
	decorate(painter);
	if (isDisplayOn())
		drawData(painter);

	QWidget::paintEvent(event);
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
