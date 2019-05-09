#pragma once

#include <QWidget>

class QPaintEvent;

class Pin : public QWidget
{

	Q_OBJECT

public:
	Pin(QWidget* parent = nullptr);

	bool getSignal() const;
	void setSignal(bool value);

protected:
	void paintEvent(QPaintEvent* event);

signals:
	void signalChanged(bool);

private:
	bool __signal;
};
