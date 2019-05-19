#pragma once

#include "decorators_global.h"
#include "decorator_base.h"

#include <QRect>

struct DECORATORS_EXPORT ScreenDecoratorOptions : public DecoratorOptions
{
	QRectF __glass;
	bool __backlight;
};

class DECORATORS_EXPORT ScreenDecorator : public DecoratorBase
{
public:
	ScreenDecorator(ScreenDecoratorOptions* opts = new ScreenDecoratorOptions);
	void decorate(QPainter& painter) const override;
};
