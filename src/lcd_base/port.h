#ifndef PORT_H
#define PORT_H

#include "pin.h"
#include <QList>

class Port : public QList<Pin*>
{
public:
	void mutePort();
	void unmutePort();
	template <typename INT_TYPE>
	void write(uint8_t index, INT_TYPE value);
	template <typename INT_TYPE>
	void write(uint8_t index, INT_TYPE value, uint8_t sz);

	QString serialize() const;
	void deserialize(QString const& data);
};

template<typename INT_TYPE>
inline void Port::write(uint8_t index, INT_TYPE value)
{
	for (int i = index; i < index + (sizeof INT_TYPE) * 8; ++i, value >>= 1)
	{
		if (i > size())
			continue;

		at(i)->setSignal(value & 1);
	}
}

template<typename INT_TYPE>
inline void Port::write(uint8_t index, INT_TYPE value, uint8_t sz)
{
	for (int i = index; i < index + sz * 8; ++i, value >>= 1)
	{
		if (i > size() - 1)
			continue;

		at(i)->setSignal(value & 1);
	}
}


#endif