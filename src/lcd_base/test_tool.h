#pragma once

#include <QWidget>

class Port;
class QLineEdit;

class TestTool : public QWidget
{

	Q_OBJECT

public:
	TestTool(Port* port);

private slots:
	void writeCommand();
	void writeData();

private:
	Port* __port;
	QLineEdit* __data;
};

