#pragma once

#include <QWidget>
#include "../lcd_base/port.h"

class Tester : public QWidget
{
public:
	Port* __port;
};
