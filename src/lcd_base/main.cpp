#include <QApplication>
#include "lcd_glass_panel.h"
#include "lcd.h"
#include "lcd_controller.h"
#include "pin.h"

#include <QThread>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    LCD lcd(16, 2);
    lcd.show();

    return app.exec();
}