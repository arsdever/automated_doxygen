#include "lcd_controller.h"
#include "pin.h"

#include <QDebug>

LCDController::LCDController(uint8_t w, uint8_t h, Port& port, QObject* parent)
	: QObject(parent),
	__port(port),
	__shifted(0),
	__ddram(new uint8_t[0x7F]),
	__cgram(new uint8_t[0x3F]),
	__address_counter(__ddram),
	__increment_mode(true),
	__lines(false),
	__shift(false),
	__cursor(false),
	__blink(false),
	__itype(BIT8)
{
	emit changeDisplayState(false);
}

static uint8_t swap(uint8_t number)
{
	uint8_t result = 0;
	for (uint8_t i = 0; i < 8; ++i)
	{
		result |= number & 1;
		result <<= 1;
		number >>= 1;
	}
	return result;
}

void LCDController::instruction(uint8_t command)
{
	if (__port.at(Pinout::RW)->getSignal() || __port.at(Pinout::RS)->getSignal())
	{
		if (__port.at(Pinout::RW)->getSignal() && !__port.at(Pinout::RS)->getSignal()) readAddressAndBusyFlag();
		else if (!__port.at(Pinout::RW)->getSignal() && __port.at(Pinout::RS)->getSignal()) writeData(getData());
		else readData();
	}
	else if (command & 0x80) setAddressDDRAM(command & 0x7F);
	else if (command & 0x40) setAddressCGRAM(command & 0x3F);
	else if (command & 0x20) setFunction(command & 0x10, command & 0x08, command & 0x04);
	else if (command & 0x10) shiftCursorOrDisplay(command & 0x08, command & 0x04);
	else if (command & 0x08) changeDisplayState(command & 0x04, command & 0x02, command & 0x01);
	else if (command & 0x04) setEntryMode(command & 0x02, command & 0x01);
	else if (command & 0x02) returnHome();
	else if (command & 0x01) clearDisplay();
}

uint8_t LCDController::getData() const
{
	uint8_t command = 0;
	command |= __port.at(Pinout::DB7)->getSignal() ? 1 : 0;
	command <<= 1;
	command |= __port.at(Pinout::DB6)->getSignal() ? 1 : 0;
	command <<= 1;
	command |= __port.at(Pinout::DB5)->getSignal() ? 1 : 0;
	command <<= 1;
	command |= __port.at(Pinout::DB4)->getSignal() ? 1 : 0;

	if (__itype == BIT8)
	{
		command <<= 1;
		command |= __port.at(Pinout::DB3)->getSignal() ? 1 : 0;
		command <<= 1;
		command |= __port.at(Pinout::DB2)->getSignal() ? 1 : 0;
		command <<= 1;
		command |= __port.at(Pinout::DB1)->getSignal() ? 1 : 0;
		command <<= 1;
		command |= __port.at(Pinout::DB0)->getSignal() ? 1 : 0;
	}

	return command;
}

uint64_t LCDController::getSymbolFromCGROM(char ch) const
{
	switch (ch)
	{
		// CUSTOM CHARS 0x00 - 0x0F
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15: return *((uint64_t*)(__cgram + 8 * (ch % 8)));

		// SYMBOLS
	case ' ': return 0x0000000000000000;
	case '!': return 0x0404040400000400;
	case '"': return 0x0A0A0A0000000000;
	case '#': return 0x0A0A1F0A1F0A0A00;
	case '$': return 0x040F140E051E0400;
	case '%': return 0x1819020408130300;
	case '&': return 0x0C12140815121D00;
	case '\'': return 0x0C04080000000000;
	case '(': return 0x0204080808040200;
	case ')': return 0x0804020202040800;
	case '*': return 0x0004150E15040000;
	case '+': return 0x0004041F04040000;
	case ',': return 0x000000000C040800;
	case '-': return 0x0000001F00000000;
	case '.': return 0x00000000000C0C00;
	case '/': return 0x0001020408100000;
	case ':': return 0x000C0C000C0C0000;
	case ';': return 0x000C0C000C040800;
	case '<': return 0x0204081008040200;
	case '=': return 0x00001F001F000000;
	case '>': return 0x0804020102040800;
	case '?': return 0x0E11010204000400;
	case '@': return 0x0E11010D15150E00;
	case '[': return 0x0E08080808080E00;
	case '\\': return 0x110A1F041F040400;
	case ']': return 0x0E02020202020E00;
	case '^': return 0x040A110000000000;
	case '_': return 0x0000000000001F00;
	case '`': return 0x0804020000000000;
	case '{': return 0x0204040804040200;
	case '|': return 0x0404040404040400;
	case '}': return 0x0804040204040800;
	case 0x7E: return 0x0004021F02040000;
	case 0x7F: return 0x0004081F08040000;

		// DIGITS
	case '0': return 0x0E11131519110E00;
	case '1': return 0x040C040404040E00;
	case '2': return 0x0E11010204081F00;
	case '3': return 0x1F02040201110E00;
	case '4': return 0x02060A121F020200;
	case '5': return 0x1F101E0101110E00;
	case '6': return 0x0608101E11110E00;
	case '7': return 0x1F01020408080800;
	case '8': return 0x0E11110E11110E00;
	case '9': return 0x0E11110F01020C00;

		// UPCASE LETTERS
	case 'A': return 0x0E11111F11111100;
	case 'B': return 0x1E11111E11111E00;
	case 'C': return 0x0E11101010110E00;
	case 'D': return 0x1E11111111111E00;
	case 'E': return 0x1F10101E10101F00;
	case 'F': return 0x1F10101E10101000;
	case 'G': return 0x0E11101013110E00;
	case 'H': return 0x1111111F11111100;
	case 'I': return 0x0E04040404040E00;
	case 'J': return 0x0E04040404140800;
	case 'K': return 0x1112141814121100;
	case 'L': return 0x1010101010101F00;
	case 'M': return 0x111B151111111100;
	case 'N': return 0x1111191513111100;
	case 'O': return 0x0E11111111110E00;
	case 'P': return 0x1E11111E10101000;
	case 'Q': return 0x0E11111115120D00;
	case 'R': return 0x1E11111E14121100;
	case 'S': return 0x0E11100E01110E00;
	case 'T': return 0x1F04040404040400;
	case 'U': return 0x1111111111110E00;
	case 'V': return 0x11111111110A0400;
	case 'W': return 0x11111111151B1100;
	case 'X': return 0x11110A040A111100;
	case 'Y': return 0x11110A0404040400;
	case 'Z': return 0x1F01020408101F00;

		// UPCASE LETTERS
	case 'a': return 0x00000E010F110F00;
	case 'b': return 0x1010161911111E00;
	case 'c': return 0x00000E1010110E00;
	case 'd': return 0x01010D1311110F00;
	case 'e': return 0x00000E111F100E00;
	case 'f': return 0x0609081C08080800;
	case 'g': return 0x000F11110F010E00;
	case 'h': return 0x1010161911111100;
	case 'i': return 0x04000C0404040E00;
	case 'j': return 0x0200060202120C00;
	case 'k': return 0x1010121418141200;
	case 'l': return 0x0C04040404040E00;
	case 'm': return 0x00001A1515111100;
	case 'n': return 0x0000161911111100;
	case 'o': return 0x00000E1111110E00;
	case 'p': return 0x00001E111E101000;
	case 'q': return 0x00000D130F010100;
	case 'r': return 0x0000161910101000;
	case 's': return 0x00000E100E011E00;
	case 't': return 0x08081C0808090600;
	case 'u': return 0x0000111111130D00;
	case 'v': return 0x00001111110A0400;
	case 'w': return 0x0000111115150A00;
	case 'x': return 0x0000110A040A1100;
	case 'y': return 0x000011110F010E00;
	case 'z': return 0x00001F0204081F00;

	default: return 0x0;
	}
}

uint64_t LCDController::getSymbolFromDDRAM(uint8_t address) const
{
	if (__lines == 1)
		return getSymbolFromCGROM(__ddram[address > 0x3F ? (address % 0x40 + __shifted) % 0x40 + 0x40 : (address + __shifted) % 0x40]);
	else
		return getSymbolFromCGROM(__ddram[(address + __shifted) % 0x80]);
}

void LCDController::incrementAddressCounter()
{
	if (__ddram_address)
	{
		if (__lines)
		{
			if (++__address_counter > __ddram + 0x7F)
				__address_counter = __ddram;
		}
		else
		{
			if (__address_counter < __ddram + 0x40)
			{
				if (++__address_counter > __ddram + 0x3F)
					__address_counter = __ddram;
			}
			else
			{
				if (++__address_counter > __ddram + 0x7F)
					__address_counter = __ddram + 0x40;
			}
		}
	}
	else if(++__address_counter > __cgram + 0x3F)
		__address_counter = __ddram_address ? __ddram : __cgram;
}

void LCDController::decrementAddressCounter()
{
	if (__ddram_address)
	{
		if (__lines)
		{
			if (--__address_counter < __ddram)
				__address_counter = __ddram + 0x7F;
		}
		else
		{
			if (__address_counter < __ddram + 0x40)
			{
				if (--__address_counter < __ddram)
					__address_counter = __ddram + 0x3F;
			}
			else
			{
				if (--__address_counter < __ddram + 0x3F)
					__address_counter = __ddram + 0x7F;
			}
		}
	}
	else if (--__address_counter < __cgram)
		__address_counter = __cgram + 0x3F;
}

void LCDController::portEnabled(bool enabled)
{
	if (enabled)
	{
		if (__itype == BIT4)
		{
			if (!__waiting_second)
			{
				__command = getData() << 4;
				__waiting_second = true;
				return;
			}
			__command |= getData() & 0x0F;
			__waiting_second = false;
			instruction(__command);
			return;
		}
		instruction(getData());
	}
}

void LCDController::clearDisplay()
{
	__address_counter = 0;
	__increment_mode = 1;
	for (int i = 0; i < 0x7F; ++i)
	{
		__ddram[i] = 0;
		emit changed();
	}
}

void LCDController::returnHome()
{
	__address_counter = 0;
	__increment_mode = 1;
	__shifted = 0;
	emit changed();
}

void LCDController::setEntryMode(bool id, bool s)
{
	__shift = s;
	__increment_mode = id;
}

void LCDController::changeDisplayState(bool d, bool c, bool b)
{
	emit changeDisplayState(d);
	__cursor = c;
	__blink = b;
}

void LCDController::shiftCursorOrDisplay(bool s, bool d)
{
	bool shift = s;
	bool dir = d;
	if (shift)
	{
		if (dir)
		{
			if (++__shifted > (__lines ? 0x3F : 0x7F))
				__shifted = 0;
		}
		else
		{
			if (--__shifted < 0)
				__shifted = __lines ? 0x3F : 0x7F;
		}
		emit changed();
	}
	else
	{
		if (dir)
			incrementAddressCounter();
		else
			decrementAddressCounter();
	}
}

void LCDController::setFunction(bool dl, bool n, bool f)
{
	if (dl)
		__itype = BIT8;
	else
		__itype = BIT4;

	__lines = n;
	bool font_type = f;
}

void LCDController::setAddressCGRAM(uint8_t a)
{
	__address_counter = __cgram + a;
}

void LCDController::setAddressDDRAM(uint8_t a)
{
	__address_counter = __ddram + a;
}

void LCDController::readAddressAndBusyFlag()
{
	__port.mutePort();
	__port.write(Pinout::DB0, swap(__ddram_address ? __address_counter - __ddram : __address_counter - __cgram), 8);
	__port.unmutePort();
}

void LCDController::writeData(uint8_t d)
{
	*__address_counter = d;
	if (__ddram_address)
	{
		uint8_t absaddr = __address_counter - __ddram;
		emit changed();

		if (__increment_mode)
			incrementAddressCounter();
		else
			decrementAddressCounter();
	}
}

void LCDController::readData()
{
	__port.mutePort();
	__port.write(Pinout::DB0, swap(*__address_counter));
	__port.unmutePort();
}