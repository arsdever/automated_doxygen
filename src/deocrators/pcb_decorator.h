#pragma once

#include "decorators_global.h"
#include "decorator_base.h"

#include <QRectF>

struct DECORATORS_EXPORT PCBDecoratorOptions : public DecoratorOptions
{
	QRectF __pcb_rect;
	double __holes_radius_x;
	double __holes_radius_y;
	double __holes_distance_x;
	double __holes_distance_y;
};

class DECORATORS_EXPORT PCBDecorator : public DecoratorBase
{
public:
	PCBDecorator(PCBDecoratorOptions* opts = new PCBDecoratorOptions);
	void decorate(QPainter& painter) const override;
};

