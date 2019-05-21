#pragma once

#include "lcd_core_global.h"
#include <QUuid>
#include <QObject>
#include <interfaces.h>

class LCD_CORE_EXPORT Pin : public QObject, public Serializable, public Deserializable
{

	Q_OBJECT

public:
	Pin(QObject* parent);
	Pin(QUuid uuid = QUuid::createUuid(), QObject* parent = nullptr);

	bool getSignal() const;
	void setSignal(bool value);

	QString getName() const;
	void setName(QString const& pin_name);

public:
	QByteArray serialize() const override;
	void deserialize(QByteArray const&) override;

signals:
	void signalChanged(bool);

private:
	QString __name;
	bool __signal;
};
