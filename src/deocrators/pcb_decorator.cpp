#include "pcb_decorator.h"

#include <QPainter>

#define PCB_COLOR_CONTACT QColor(33, 122, 53)
#define PCB_COLOR_NO_CONTACT QColor(26, 81, 60)
#define PCB_NO_COLOR QColor(157, 145, 110)

PCBDecorator::PCBDecorator(PCBDecoratorOptions* opts)
	: DecoratorBase(opts) {}

void PCBDecorator::decorate(QPainter& painter) const
{
	PCBDecoratorOptions const* opts = dynamic_cast<PCBDecoratorOptions const*>(options());
	if (opts == nullptr)
		return;

	painter.save();

	painter.fillRect(opts->__pcb_rect, PCB_COLOR_CONTACT);

	painter.setBrush(PCB_NO_COLOR);
	painter.setCompositionMode(QPainter::CompositionMode::CompositionMode_SourceOver);
	double hole_x = opts->__holes_distance_x / 2;
	double hole_y = opts->__holes_distance_y / 2;
	painter.translate(opts->__pcb_rect.width() / 2, opts->__pcb_rect.height() / 2);
	painter.drawEllipse(QPointF(-hole_x, hole_y), opts->__holes_radius_x + 5, opts->__holes_radius_y + 5);
	painter.drawEllipse(QPointF(-hole_x, -hole_y), opts->__holes_radius_x + 5, opts->__holes_radius_y + 5);
	painter.drawEllipse(QPointF(hole_x, hole_y), opts->__holes_radius_x + 5, opts->__holes_radius_y + 5);
	painter.drawEllipse(QPointF(hole_x, -hole_y), opts->__holes_radius_x + 5, opts->__holes_radius_y + 5);
	painter.setCompositionMode(QPainter::CompositionMode::CompositionMode_Clear);
	painter.drawEllipse(QPointF(-hole_x, hole_y), opts->__holes_radius_x, opts->__holes_radius_y);
	painter.drawEllipse(QPointF(-hole_x, -hole_y), opts->__holes_radius_x, opts->__holes_radius_y);
	painter.drawEllipse(QPointF(hole_x, hole_y), opts->__holes_radius_x, opts->__holes_radius_y);
	painter.drawEllipse(QPointF(hole_x, -hole_y), opts->__holes_radius_x, opts->__holes_radius_y);

	painter.restore();
}