#include "pin.h"
#include "../include/metric_macros.h"

#include <QPaintEvent>
#include <QPainter>

#define LOGICAL_HIGH QColor(202, 244, 65)
#define LOGICAL_LOW QColor(244, 172, 65)
#define LOGICAL_Z QColor(244, 223, 65)

Pin::Pin(QWidget* parent)
	: QWidget(parent),
		__signal(false)
{
	setAttribute(Qt::WA_NoSystemBackground);
}

void Pin::setSignal(bool value) {
	if (__signal != value) {
		emit signalChanged(__signal = value);
		update();
	}
}

bool Pin::getSignal() const { return __signal; }

void Pin::mouseReleaseEvent(QMouseEvent* event)
{
	Q_UNUSED(event);
	setSignal(!getSignal());
}

void Pin::paintEvent(QPaintEvent* event) {
	QPainter ptr(this);
	ptr.setRenderHint(QPainter::HighQualityAntialiasing);
	ptr.setPen(Qt::NoPen);
	ptr.setBrush(QColor(244, 209, 66));
	ptr.drawRect(0, 0, NORMALIZE_X(PIN_WIDTH), NORMALIZE_Y(PIN_HEIGHT));
	ptr.drawEllipse(QPointF(NORMALIZE_X(PIN_WIDTH) / 2, NORMALIZE_Y(PIN_HEIGHT)), NORMALIZE_X(PIN_WIDTH) / 2, NORMALIZE_X(PIN_WIDTH) / 2);
	ptr.setPen(getSignal() ? Qt::darkGreen : Qt::darkRed);
	ptr.drawText(QRect(0, 0, NORMALIZE_X(PIN_WIDTH), NORMALIZE_Y(PIN_HEIGHT)), Qt::AlignCenter, QString(getSignal() ? '1' : '0'));
}

void Port::mutePort()
{
	for (Pin* pin : *this)
		pin->blockSignals(true);
}

void Port::unmutePort()
{
	for (Pin* pin : *this)
		pin->blockSignals(false);
}