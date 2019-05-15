#pragma once

#include <QObject>
#include <QList>

class LCDController;
class LCDBlock;
class QPaintEvent;
class Port;

class LCD : public QObject
{

	Q_OBJECT

public:
	LCD(uint8_t columns_count, uint8_t row_count, LCDController* controller, QObject* parent = nullptr);

	uint64_t getBlock(uint8_t column, uint8_t row) const;
	uint8_t rows() const;
	uint8_t columns() const;
	
private:
	uint8_t __rows;
	uint8_t __columns;
	LCDController* __controller;
};

