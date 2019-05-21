#pragma once

#include <QWidget>

class Pin;
class QPaintEvent;
class QMouseEvent;
class QEvent;

#define PIN_WIDTH 2
#define PIN_HEIGHT 3.4

class PinWidget : public QWidget
{

	Q_OBJECT

public:
	PinWidget(QWidget* parent = nullptr);
	PinWidget(Pin* pin, QWidget* parent = nullptr);
	PinWidget(QString const& pin_name, QWidget* parent = nullptr);

protected:
	void paintEvent(QPaintEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void enterEvent(QEvent* event) override;
	void leaveEvent(QEvent* event) override;

private:
	void init();

private:
	Pin* __pin;
	bool __hover;
};
