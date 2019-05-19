#include "test_tool.h"
#include "pin.h"
#include "port.h"
#include "lcd_controller.h"

#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>

TestTool::TestTool(Port* port) 
	: __port(port),
	__data(new QLineEdit)
{
	init();
}

void TestTool::init()
{
	QGridLayout* lay = new QGridLayout;

	QPushButton* wc = new QPushButton("Write Command");
	QPushButton* wd = new QPushButton("Write Data");
	lay->addWidget(__data, 0, 0, 1, -1);
	lay->addWidget(wc, 1, 0);
	lay->addWidget(wd, 1, 1);

	__port->mutePort();
	for (Pin* pin : *__port)
	{
		pin->setSignal(false);
	}
	__port->unmutePort();

	connect(wc, SIGNAL(clicked()), this, SLOT(writeCommand()));
	connect(wd, SIGNAL(clicked()), this, SLOT(writeData()));

	__data->setText("0x0f");
	writeCommand();
	__data->setText("0x30");
	writeCommand();

	QString message("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Ut mattis vestibulum risus, consectetur vestibulum leo ultrices a amet.");

	for (int i = 0; i < message.size(); ++i)
	{
		__data->setText(tr("0x%1").arg(int(message[i].toLatin1()), 0, 16));
		writeData();
	}
	__data->setText("0x18");

	setLayout(lay);
}

void TestTool::writeCommand()
{
	bool ok = false;
	uint8_t data = __data->text().toInt(&ok, 16);

	if (ok)
	{
		__port->at(LCDController::DB0)->setSignal(data & 1);
		__port->at(LCDController::DB1)->setSignal(data & (1 << 1));
		__port->at(LCDController::DB2)->setSignal(data & (1 << 2));
		__port->at(LCDController::DB3)->setSignal(data & (1 << 3));
		__port->at(LCDController::DB4)->setSignal(data & (1 << 4));
		__port->at(LCDController::DB5)->setSignal(data & (1 << 5));
		__port->at(LCDController::DB6)->setSignal(data & (1 << 6));
		__port->at(LCDController::DB7)->setSignal(data & (1 << 7));
	}

	__port->at(LCDController::E)->setSignal(true);
	__port->at(LCDController::E)->setSignal(false);
}

void TestTool::writeData()
{
	bool ok = false;
	uint8_t data = __data->text().toInt(&ok, 16);
	__port->at(LCDController::RS)->setSignal(true);
	
	if (ok)
	{
		__port->at(LCDController::DB0)->setSignal(data & 1);
		__port->at(LCDController::DB1)->setSignal(data & (1 << 1));
		__port->at(LCDController::DB2)->setSignal(data & (1 << 2));
		__port->at(LCDController::DB3)->setSignal(data & (1 << 3));
		__port->at(LCDController::DB4)->setSignal(data & (1 << 4));
		__port->at(LCDController::DB5)->setSignal(data & (1 << 5));
		__port->at(LCDController::DB6)->setSignal(data & (1 << 6));
		__port->at(LCDController::DB7)->setSignal(data & (1 << 7));
	}

	__port->at(LCDController::E)->setSignal(true);
	__port->at(LCDController::E)->setSignal(false);
	__port->at(LCDController::RS)->setSignal(false);
}