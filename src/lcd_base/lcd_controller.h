#ifndef LCD_CONTROLLER_H
#define LCD_CONTROLLER_H

#include <QObject>

class Port;
class LCDGlassPanel;

class LCDController : public QObject
{

	Q_OBJECT

public:
	enum Pinout
	{
		VSS = 0,
		VDD,
		V0,
		RS,
		RW,
		E,
		DB0,
		DB1,
		DB2,
		DB3,
		DB4,
		DB5,
		DB6,
		DB7,
		LEDP,
		LEDM
	};

	enum InterfaceType
	{
		BIT4,
		BIT8,
		SCI
	};

public:
	LCDController(uint8_t w, uint8_t h, Port& port, QObject* parent = nullptr);

	void instruction(uint8_t command);

public slots:
	void portEnabled(bool enabled);

signals:
	void changeDisplayState(bool);
	void changed();

private:
	// Some helpers
	uint8_t getData() const;
	uint64_t getSymbolFromCGROM(char ch) const;
	uint64_t getSymbolFromDDRAM(uint8_t address) const;
	void incrementAddressCounter();
	void decrementAddressCounter();

	// Instructions
	void clearDisplay();
	void returnHome();
	void setEntryMode(bool id, bool s);
	void changeDisplayState(bool d, bool c, bool b);
	void shiftCursorOrDisplay(bool s, bool d);
	void setFunction(bool dl, bool n, bool f);
	void setAddressCGRAM(uint8_t a);
	void setAddressDDRAM(uint8_t a);
	void readAddressAndBusyFlag();
	void writeData(uint8_t d);
	void readData();

private:
	Port& __port;
	int8_t __shifted;
	uint8_t* __ddram;
	uint8_t* __cgram;
	uint8_t* __address_counter;
	bool __ddram_address;
	bool __increment_mode;
	bool __lines;
	bool __shift;
	bool __cursor;
	bool __blink;
	bool __waiting_second;
	uint8_t __command;
	InterfaceType __itype;

	friend class LCD;
};

#endif
