#include "tester.h"
#include <QtWidgets/QApplication>
#include "../lcd_base/port.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Tester w;
	w.__port = new Port;
	w.__port->push_back(new Pin("test_pin", Pin::Output, &w));
	w.show();
	return a.exec();
}
