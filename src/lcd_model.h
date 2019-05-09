#ifndef LCD_MODEL_H
#define LCD_MODEL_H

#include <QWidget>
#include <QFont>
#include <QFontMetrics>

class QPaintEvent;

class LCDModel : public QWidget
{
  public:
    LCDModel(int width, int height, QWidget *parent = nullptr);

  protected:
    void paintEvent(QPaintEvent *event);

  private:
    QFont __font;
    QFontMetrics __metrics;
    int __width;
    int __height;
};

#endif