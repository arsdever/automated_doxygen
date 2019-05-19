#include "glass_case_decorator.h"

#include <QPainter>

#define CASE_COLOR QColor(48, 48, 48)
#define ROUNDNESS 7
#define LINE_WEIGHT 6
#define GRADIENT_DIFF 140
#define VAR_1 48

GlassCaseDecorator::GlassCaseDecorator(GlassCaseDecoratorOptions* opts)
	: DecoratorBase(opts) {}

void GlassCaseDecorator::decorate(QPainter& painter) const
{
	GlassCaseDecoratorOptions const* opts = dynamic_cast<GlassCaseDecoratorOptions const*>(options());
	if (opts == nullptr)
		return;
	
	QRectF orect = opts->__outer_area;
	QRectF irect = opts->__inner_area;
	irect.adjust(-orect.left(), -orect.top(), -orect.left(), -orect.top());
	orect.adjust(-orect.left(), -orect.top(), -orect.left(), -orect.top());
	QImage img(orect.size().toSize(), QImage::Format_ARGB32);
	QPainter border_drawer(&img);
	border_drawer.setBrush(Qt::transparent);
	border_drawer.setPen(Qt::NoPen);
	border_drawer.setRenderHint(QPainter::HighQualityAntialiasing);
	border_drawer.fillRect(orect, CASE_COLOR);
	border_drawer.setCompositionMode(QPainter::CompositionMode_Clear);
	border_drawer.drawEllipse(img.rect().topLeft(), ROUNDNESS, ROUNDNESS);
	border_drawer.drawEllipse(img.rect().topRight(), ROUNDNESS, ROUNDNESS);
	border_drawer.drawEllipse(img.rect().bottomLeft(), ROUNDNESS, ROUNDNESS);
	border_drawer.drawEllipse(img.rect().bottomRight(), ROUNDNESS, ROUNDNESS);
	border_drawer.drawRoundedRect(img.rect().left() - 2, VAR_1, 4, img.rect().height() - 2 * VAR_1, 2, 2);
	border_drawer.drawRoundedRect(img.rect().right() - 2, VAR_1, 4, img.rect().height() - 2 * VAR_1, 2, 2);
	border_drawer.drawRoundedRect(irect, ROUNDNESS, ROUNDNESS);
	border_drawer.setCompositionMode(QPainter::CompositionMode_SourceOver);
	QRectF bar1(VAR_1 / 2.0, (orect.height() - irect.height() - 2 * LINE_WEIGHT) / 4.0, orect.width() - VAR_1, LINE_WEIGHT);
	QRectF bar2(VAR_1 / 2.0, irect.bottom() + (orect.height() - irect.height() - 2 * LINE_WEIGHT) / 4.0, orect.width() - VAR_1, LINE_WEIGHT);
	QLinearGradient gradient;
	gradient.setStart(0, bar1.top());
	gradient.setFinalStop(0, bar1.bottom());
	gradient.setColorAt(0, CASE_COLOR.darker(GRADIENT_DIFF));
	gradient.setColorAt(1, CASE_COLOR.lighter(GRADIENT_DIFF));
	border_drawer.setBrush(gradient);
	border_drawer.drawRoundedRect(bar1, LINE_WEIGHT / 2, LINE_WEIGHT / 2);
	gradient.setStart(0, bar2.top());
	gradient.setFinalStop(0, bar2.bottom());
	gradient.setColorAt(0, CASE_COLOR.darker(GRADIENT_DIFF));
	gradient.setColorAt(1, CASE_COLOR.lighter(GRADIENT_DIFF));
	border_drawer.setBrush(gradient);
	border_drawer.drawRoundedRect(bar2, LINE_WEIGHT / 2, LINE_WEIGHT / 2);

	double cuts_x_1 = orect.width() / 8.0;
	double cuts_x_2 = (orect.width() - opts->__cut_area_size.width()) / 2.0;
	double cuts_x_3 = orect.width() * 7.0 / 8.0 - opts->__cut_area_size.width();
	double cuts_y_1 = -opts->__cut_area_size.height() / 2.0;
	double cuts_y_2 = orect.height() - opts->__cut_area_size.height() / 2.0;

	painter.save();

	painter.translate(opts->__outer_area.topLeft());
	painter.setCompositionMode(QPainter::CompositionMode_Clear);
	painter.setBrush(Qt::transparent);
	painter.setPen(Qt::NoPen);
	painter.drawRoundedRect(QRectF(cuts_x_1, cuts_y_1, opts->__cut_area_size.width(), opts->__cut_area_size.height()), opts->__cut_area_size.height() / 2.0, opts->__cut_area_size.height() / 2.0);
	painter.drawRoundedRect(QRectF(cuts_x_2, cuts_y_1, opts->__cut_area_size.width(), opts->__cut_area_size.height()), opts->__cut_area_size.height() / 2.0, opts->__cut_area_size.height() / 2.0);
	painter.drawRoundedRect(QRectF(cuts_x_3, cuts_y_1, opts->__cut_area_size.width(), opts->__cut_area_size.height()), opts->__cut_area_size.height() / 2.0, opts->__cut_area_size.height() / 2.0);
	painter.drawRoundedRect(QRectF(cuts_x_1, cuts_y_2, opts->__cut_area_size.width(), opts->__cut_area_size.height()), opts->__cut_area_size.height() / 2.0, opts->__cut_area_size.height() / 2.0);
	painter.drawRoundedRect(QRectF(cuts_x_2, cuts_y_2, opts->__cut_area_size.width(), opts->__cut_area_size.height()), opts->__cut_area_size.height() / 2.0, opts->__cut_area_size.height() / 2.0);
	painter.drawRoundedRect(QRectF(cuts_x_3, cuts_y_2, opts->__cut_area_size.width(), opts->__cut_area_size.height()), opts->__cut_area_size.height() / 2.0, opts->__cut_area_size.height() / 2.0);
	painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
	painter.drawImage(QPoint(0, 0), img, orect);

	painter.restore();
}