#include "pin.h"

Pin::Pin(QObject* parent)
	: Pin(QUuid::createUuid(), parent) {}

Pin::Pin(QUuid uuid, QObject* parent)
	: QObject(parent),
	__name(uuid.toString()),
	__signal(false) {}

bool Pin::getSignal() const { return __signal; }

void Pin::setSignal(bool value)
{
	if (__signal != value) {
		emit signalChanged(__signal = value);
	}
}

QString Pin::getName() const { return __name; }

void Pin::setName(QString const& pin_name) { __name = pin_name; }