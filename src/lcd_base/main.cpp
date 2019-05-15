#include <QApplication>
#include "bc1604a.h"
#include "test_tool.h"

#include <QThread>
#include <QtWin>
#include <QLibrary>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    BC1604A lcd;
	QtWin::setCompositionEnabled(true);
	QtWin::extendFrameIntoClientArea(&lcd, QMargins(-1,-1,-1,-1));
	QtWin::enableBlurBehindWindow(&lcd);
	QtWin::markFullscreenWindow(&lcd);
    lcd.show();
	TestTool tester(&lcd.getPort());
	tester.show();

    return app.exec();
}