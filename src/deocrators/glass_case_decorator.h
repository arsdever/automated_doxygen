#pragma once

#include "decorators_global.h"
#include "decorator_base.h"

#include <QRect>

struct DECORATORS_EXPORT GlassCaseDecoratorOptions : public DecoratorOptions
{
	QRectF __outer_area;
	QRectF __inner_area;
	QSizeF __cut_area_size;
};

class DECORATORS_EXPORT GlassCaseDecorator : public DecoratorBase
{
public:
	GlassCaseDecorator(GlassCaseDecoratorOptions* opts = new GlassCaseDecoratorOptions);
	void decorate(QPainter& painter) const override;
};
