#pragma once

#include <QWidget>

class QLineEdit;
class Port;

class TestTool : public QWidget
{

	Q_OBJECT

public:
	TestTool(Port* port);
	void init();

private slots:
	void writeCommand();
	void writeData();

private:
	Port* __port;
	QLineEdit* __data;
};

