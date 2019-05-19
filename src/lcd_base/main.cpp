#include <QApplication>
#include "bc1604a.h"
#include "lcd1602a_1.h"
#include "test_tool.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    LCD1602A_1 lcd;
    lcd.show();
	TestTool test(&lcd.getPort());
	test.show();

    return app.exec();
}