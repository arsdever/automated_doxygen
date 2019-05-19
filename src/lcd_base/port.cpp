#include "port.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

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

QString Port::serialize() const
{
	QJsonObject port;
	for (Pin* pin : *this)
		port.insert(pin->getName(), pin->getSignal());

	return QJsonDocument(port).toJson();
}

void Port::deserialize(QString const& data)
{
	qDebug() << data;
	QJsonDocument port = QJsonDocument::fromJson(data.toLatin1());
	for (Pin* pin : *this)
	{
		if (port.object().contains(pin->getName()))
		{
			qDebug() << "Found pin by name " << pin->getName() << port.object().operator[](pin->getName()).toBool();
			pin->setSignal(port.object().operator[](pin->getName()).toBool());
		}
	}
}