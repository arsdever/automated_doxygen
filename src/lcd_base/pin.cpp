#include "pin.h"

#include <QPaintEvent>
#include <QPainter>

Pin::Pin(QWidget* parent)
	: QWidget(parent),
		__signal(false)
{
	setAttribute(Qt::WA_NoSystemBackground);
}

void Pin::setSignal(bool value) {
	if (__signal != value) {
		emit signalChanged(__signal = value);
	}
}

bool Pin::getSignal() const { return __signal; }

void Pin::paintEvent(QPaintEvent* event) {
	QPainter ptr(this);
	ptr.setRenderHint(QPainter::HighQualityAntialiasing);
	ptr.setPen(Qt::NoPen);
	ptr.setBrush(QColor(244, 209, 66));
	ptr.drawRect(0, 0, 10, 15);
	ptr.drawEllipse(QRect(0,10,10,10));
}