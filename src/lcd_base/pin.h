#pragma once

#include <QWidget>

class QPaintEvent;
class QMouseEvent;

#define PIN_WIDTH 1.8
#define PIN_HEIGHT 3.4

class Pin : public QWidget
{

	Q_OBJECT

public:
	Pin(QWidget* parent = nullptr);

	bool getSignal() const;
	void setSignal(bool value);

protected:
	void paintEvent(QPaintEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);

signals:
	void signalChanged(bool);

private:
	bool __signal;
};

class Port : public QList<Pin*>
{
public:
	void mutePort();
	void unmutePort();
	template <typename INT_TYPE>
	void write(uint8_t index, INT_TYPE value);
	template <typename INT_TYPE>
	void write(uint8_t index, INT_TYPE value, uint8_t sz);
};

template<typename INT_TYPE>
inline void Port::write(uint8_t index, INT_TYPE value)
{
	for (int i = index + (sizeof INT_TYPE) * 8 - 1; i >= index; --i)
	{
		if (i > size())
			continue;

		at(i)->setSignal(value);
	}
}

template<typename INT_TYPE>
inline void Port::write(uint8_t index, INT_TYPE value, uint8_t sz)
{
	for (int i = index + sz * 8 - 1; i >= index; --i)
	{
		if (i > size())
			continue;

		at(i)->setSignal(value);
	}
}
