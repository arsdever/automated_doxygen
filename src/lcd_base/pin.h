#pragma once

#include <QWidget>

class QPaintEvent;
class QMouseEvent;
class QEvent;

#define PIN_WIDTH 2
#define PIN_HEIGHT 3.4

class Pin : public QWidget
{

	Q_OBJECT

public:
	Pin(QWidget* parent = nullptr);
	Pin(QString const& pin_name, QWidget* parent = nullptr);

	bool getSignal() const;
	void setSignal(bool value);

	QString getName() const;
	void setName(QString const& pin_name);

protected:
	void paintEvent(QPaintEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void enterEvent(QEvent* event) override;
	void leaveEvent(QEvent* event) override;
	
signals:
	void signalChanged(bool);

private:
	bool __signal;
	QString __name;
	bool __hover;
};
