#include "lcd.h"
#include "lcd_controller.h"

LCD::LCD(uint8_t column_count, uint8_t row_count, LCDController* controller, QObject* parent)
	: QObject(parent),
	__rows(row_count),
	__columns(column_count),
	__controller(controller) {}

uint64_t LCD::getBlock(uint8_t column, uint8_t row) const
{
	return __controller->getSymbolFromDDRAM(column + row * 0x40);
}

uint8_t LCD::rows() const
{
	return __rows;
}

uint8_t LCD::columns() const
{
	return __columns;
}