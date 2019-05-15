#include "pin.h"
#include "../include/metric_macros.h"

#include <QPaintEvent>
#include <QPainter>

#define LOGICAL_HIGH QColor(202, 244, 65)
#define LOGICAL_LOW QColor(244, 172, 65)
#define LOGICAL_Z QColor(244, 223, 65)

#ifdef ZOOM_FACTOR
#if (ZOOM_FACTOR == 1)
#define FONT_SIZE 8
#else
#define FONT_SIZE 12
#endif
#else
#define FONT_SIZE 8
#endif

Pin::Pin(QWidget* parent)
	: QWidget(parent),
		__signal(false)
{
	setAttribute(Qt::WA_NoSystemBackground);
	setCursor(Qt::PointingHandCursor);
	setFixedSize(NORMALIZE_X(PIN_WIDTH), NORMALIZE_Y(PIN_HEIGHT));
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

void Pin::paintEvent(QPaintEvent* event)
{
	QPainter ptr(this);
	QPainterPath path;
	QFont font("Calibri", FONT_SIZE, QFont::Bold, false);
	ptr.setRenderHint(QPainter::HighQualityAntialiasing);
	ptr.setFont(font);
	path.moveTo(0, 0);
	path.lineTo(0, NORMALIZE_Y(PIN_HEIGHT));
	path.arcTo(QRectF(0, NORMALIZE_Y(PIN_HEIGHT) - NORMALIZE_Y(PIN_WIDTH), NORMALIZE_X(PIN_WIDTH), NORMALIZE_Y(PIN_WIDTH)), 180, 180);
	path.lineTo(NORMALIZE_X(PIN_WIDTH), 0);
	path.closeSubpath();
	ptr.setPen(Qt::NoPen);
	ptr.setBrush(QColor(244, 209, 66));
	ptr.drawPath(path);
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