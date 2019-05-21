#include "pin.h"

#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

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

QByteArray Pin::serialize() const
{
	QJsonObject obj;
	obj.insert("type", "pin");
	QJsonObject pin_data;
	pin_data.insert("name", getName());
	pin_data.insert("state", getSignal());
	obj.insert("data", pin_data);
	QJsonDocument doc(obj);
	qDebug() << "serializing " << doc.toJson();
	return doc.toJson();
}

void Pin::deserialize(QByteArray const& data)
{
	qDebug() << "deserializing " << data;
	QJsonDocument doc = QJsonDocument::fromJson(data);
	QJsonObject obj = doc.object();
	if (!obj.contains("type") && obj.value("type").toString() != "pin")
		return;

	QJsonObject pin_data = obj.value("data").toObject();
	setName(pin_data.value("name").toString());
	setSignal(pin_data.value("state").toBool());
}