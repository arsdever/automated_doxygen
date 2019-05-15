#include <QApplication>
#include "bc1604a.h"
#include "test_tool.h"

#include <QThread>
#include <QLibrary>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    BC1604A lcd;
    lcd.show();
	TestTool tester(&lcd.getPort());
	tester.show();

    return app.exec();
}