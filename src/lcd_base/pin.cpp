#include "pin.h"
#include "../include/metric_macros.h"

#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUuid>

#define DRAG_DISTANCE 5

#define LOGICAL_HIGH QColor(202, 244, 65)
#define LOGICAL_LOW QColor(244, 172, 65)
#define LOGICAL_Z QColor(244, 223, 65)

#ifdef ZOOM_FACTOR
#define FONT_SIZE 12
#else
#define FONT_SIZE 8
#endif

Pin::Pin(QWidget * parent)
	: Pin(QString("pin_%1").arg(QUuid::createUuid().toString(QUuid::Id128)), parent)
{}

Pin::Pin(QString const& pin_name, QWidget* parent)
	: QWidget(parent),
	__signal(false),
	__name(pin_name),
	__hover(false)
{
	setAttribute(Qt::WA_NoSystemBackground);
	setCursor(Qt::PointingHandCursor);
	setFixedSize(NORMALIZE_X(PIN_WIDTH), NORMALIZE_Y(PIN_HEIGHT));
	setToolTip(__name);
}

bool Pin::getSignal() const { return __signal; }

void Pin::setSignal(bool value)
{
	if (__signal != value) {
		emit signalChanged(__signal = value);
		update();
	}
}

QString Pin::getName() const { return __name; }

void Pin::setName(QString const& pin_name) { __name = pin_name; }

void Pin::mouseReleaseEvent(QMouseEvent* event)
{
	Q_UNUSED(event);
	setSignal(!getSignal());
}

void Pin::enterEvent(QEvent* event)
{
	Q_UNUSED(event);
	__hover = true;
	update();
}

void Pin::leaveEvent(QEvent* event)
{
	Q_UNUSED(event);
	__hover = false;
	update();
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
	if(__hover)
		ptr.setBrush(QColor(247, 229, 96));
	else
		ptr.setBrush(QColor(244, 209, 66));
	ptr.drawPath(path);
	ptr.setPen(getSignal() ? Qt::darkGreen : Qt::darkRed);
	ptr.drawText(QRect(0, 0, NORMALIZE_X(PIN_WIDTH), NORMALIZE_Y(PIN_HEIGHT)), Qt::AlignCenter, QString(getSignal() ? '1' : '0'));
}
