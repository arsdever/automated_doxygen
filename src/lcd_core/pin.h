#pragma once

#include "lcd_core_global.h"
#include <QUuid>
#include <QObject>

class LCD_CORE_EXPORT Pin : public QObject
{

	Q_OBJECT

public:
	Pin(QObject* parent);
	Pin(QUuid uuid = QUuid::createUuid(), QObject* parent = nullptr);

	bool getSignal() const;
	void setSignal(bool value);

	QString getName() const;
	void setName(QString const& pin_name);

signals:
	void signalChanged(bool);

private:
	QString __name;
	bool __signal;
};
