#include <QApplication>
#include <lcd_model.h>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    LCDGlassPanel lcd(20, 4);
    lcd.show();

    return app.exec();
}