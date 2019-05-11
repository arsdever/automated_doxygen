#pragma once

#include <QWidget>

class LCDController;
class LCDGlassPanel;
class Port;

class LCD : public QWidget
{

	Q_OBJECT

public:
	LCD(uint8_t w, uint8_t h, QWidget* parent = nullptr);

	const Port& getPort() const;
	Port& getPort();

private:
	Port* __port;
	LCDGlassPanel* __glass_panel;
	LCDController* __controller;
};

