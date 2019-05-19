#include "screen_decorator.h"

#include <QPainter>

#define BACKLIGHT_COLOR_ON QColor(135, 173, 51)
#define BACKLIGHT_COLOR_OFF QColor(19, 25, 7)

ScreenDecorator::ScreenDecorator(ScreenDecoratorOptions* opts)
	: DecoratorBase(opts) {}

void ScreenDecorator::decorate(QPainter& painter) const
{
	ScreenDecoratorOptions const* opts = dynamic_cast<ScreenDecoratorOptions const*>(options());
	if (opts == nullptr)
		return;

	QRectF rect = opts->__glass;
	rect.adjust(-rect.left() - 2, -rect.top() - 2, -rect.left() + 2, -rect.top() + 2);

	painter.save();

	painter.translate(opts->__glass.topLeft());
	painter.fillRect(rect, opts->__backlight ? BACKLIGHT_COLOR_ON : BACKLIGHT_COLOR_OFF);

	painter.restore();
}