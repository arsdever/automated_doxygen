#include "lcd_glass_panel.h"
#include "lcd_glass_panel_block_5x8.h"

#include <QPainter>
#include <QPaintEvent>
#include <QGridLayout>

#define BLOCK_SPACING_HORIZONTAL .62
#define BLOCK_SPACING_VERTICAL .7
#define SCREEN_MARGIN_HORIZONTAL 6.95
#define SCREEN_MARGIN_VERTICAL 1.75

LCDGlassPanel::LCDGlassPanel(int w, int h, QWidget* parent)
	: QWidget(parent),
	__width(w),
	__height(h)
{
	QGridLayout* l = new QGridLayout;
	for (int r = 0; r < __height; ++r)
	{
		for (int c = 0; c < __width; ++c)
		{
			LCDGlassPanelBlock5x8* block = new LCDGlassPanelBlock5x8(this);
			__blocks.push_back(block);
			//block->move(SCREEN_MARGIN + c * block->sizeHint().width() + (c - 1) * BLOCK_MARGIN,
			//	SCREEN_MARGIN + r * block->sizeHint().height() + (r - 1) * BLOCK_MARGIN);
			l->addWidget(block, r, c);
		}
	}
	l->setHorizontalSpacing(NORMALIZE_X(BLOCK_SPACING_HORIZONTAL));
	l->setVerticalSpacing(NORMALIZE_Y(BLOCK_SPACING_VERTICAL));
	l->setContentsMargins(NORMALIZE_X(SCREEN_MARGIN_HORIZONTAL), NORMALIZE_Y(SCREEN_MARGIN_VERTICAL), NORMALIZE_X(SCREEN_MARGIN_HORIZONTAL), NORMALIZE_Y(SCREEN_MARGIN_VERTICAL));

	setLayout(l);
	//for (int i = 0; i < __pin_count; ++i) {
	//	Pin* pin = new Pin(this);
	//	__pin_array.push_back(pin);
	//	pin->move(calculatePinPosition(i));
	//	connect(pin, SIGNAL(signalChanged(bool)), this, SLOT(pinSignalChanged()));
	//}
	//setFixedSize(0, 0);
}



LCDGlassPanel::~LCDGlassPanel()
{
	//for (Pin* pin : __pin_array)
	//	delete pin;
	for (LCDGlassPanelBlock5x8* block : __blocks)
		delete block;
}

uint64_t LCDGlassPanel::getSymbol(char ch)
{
	switch (ch)
	{
		// CUSTOM CHARS 0x00 - 0x0F
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15: return getCustomSymbol(ch);

		// SYMBOLS
	case ' ': return 0x0000000000000000;
	case '!': return 0x0404040400000400;
	case '"': return 0x0A0A0A0000000000;
	case '#': return 0x0A0A1F0A1F0A0A00;
	case '$': return 0x040F140E051E0400;
	case '%': return 0x1819020408130300;
	case '&': return 0x0C12140815121D00;
	case '\'': return 0x0C04080000000000;
	case '(': return 0x0204080808040200;
	case ')': return 0x0804020202040800;
	case '*': return 0x0004150E15040000;
	case '+': return 0x0004041F04040000;
	case ',': return 0x000000000C040800;
	case '-': return 0x0000001F00000000;
	case '.': return 0x00000000000C0C00;
	case '/': return 0x0001020408100000;
	case ':': return 0x000C0C000C0C0000;
	case ';': return 0x000C0C000C040800;
	case '<': return 0x0204081008040200;
	case '=': return 0x00001F001F000000;
	case '>': return 0x0804020102040800;
	case '?': return 0x0E11010204000400;
	case '@': return 0x0E11010D15150E00;
	case '[': return 0x0E08080808080E00;
	case '\\': return 0x110A1F041F040400;
	case ']': return 0x0E02020202020E00;
	case '^': return 0x040A110000000000;
	case '_': return 0x0000000000001F00;
	case '`': return 0x0804020000000000;
	case '{': return 0x0204040804040200;
	case '|': return 0x0404040404040400;
	case '}': return 0x0804040204040800;
	case 0x7E: return 0x0004021F02040000;
	case 0x7F: return 0x0004081F08040000;

		// DIGITS
	case '0': return 0x0E11131519110E00;
	case '1': return 0x040C040404040E00;
	case '2': return 0x0E11010204081F00;
	case '3': return 0x1F02040201110E00;
	case '4': return 0x02060A121F020200;
	case '5': return 0x1F101E0101110E00;
	case '6': return 0x0608101E11110E00;
	case '7': return 0x1F01020408080800;
	case '8': return 0x0E11110E11110E00;
	case '9': return 0x0E11110F01020C00;

		// UPCASE LETTERS
	case 'A': return 0x0E11111F11111100;
	case 'B': return 0x1E11111E11111E00;
	case 'C': return 0x0E11101010110E00;
	case 'D': return 0x1E11111111111E00;
	case 'E': return 0x1F10101E10101F00;
	case 'F': return 0x1F10101E10101000;
	case 'G': return 0x0E11101013110E00;
	case 'H': return 0x1111111F11111100;
	case 'I': return 0x0E04040404040E00;
	case 'J': return 0x0E04040404140800;
	case 'K': return 0x1112141814121100;
	case 'L': return 0x1010101010101F00;
	case 'M': return 0x111B151111111100;
	case 'N': return 0x1111191513111100;
	case 'O': return 0x0E11111111110E00;
	case 'P': return 0x1E11111E10101000;
	case 'Q': return 0x0E11111115120D00;
	case 'R': return 0x1E11111E14121100;
	case 'S': return 0x0E11100E01110E00;
	case 'T': return 0x1F04040404040400;
	case 'U': return 0x1111111111110E00;
	case 'V': return 0x11111111110A0400;
	case 'W': return 0x11111111151B1100;
	case 'X': return 0x11110A040A111100;
	case 'Y': return 0x11110A0404040400;
	case 'Z': return 0x1F01020408101F00;

		// UPCASE LETTERS
	case 'a': return 0x00000E010F110F00;
	case 'b': return 0x1010161911111E00;
	case 'c': return 0x00000E1010110E00;
	case 'd': return 0x01010D1311110F00;
	case 'e': return 0x00000E111F100E00;
	case 'f': return 0x0609081C08080800;
	case 'g': return 0x000F11110F010E00;
	case 'h': return 0x1010161911111100;
	case 'i': return 0x04000C0404040E00;
	case 'j': return 0x0200060202120C00;
	case 'k': return 0x1010121418141200;
	case 'l': return 0x0C04040404040E00;
	case 'm': return 0x00001A1515111100;
	case 'n': return 0x0000161911111100;
	case 'o': return 0x00000E1111110E00;
	case 'p': return 0x00001E111E101000;
	case 'q': return 0x00000D130F010100;
	case 'r': return 0x0000161910101000;
	case 's': return 0x00000E100E011E00;
	case 't': return 0x08081C0808090600;
	case 'u': return 0x0000111111130D00;
	case 'v': return 0x00001111110A0400;
	case 'w': return 0x0000111115150A00;
	case 'x': return 0x0000110A040A1100;
	case 'y': return 0x000011110F010E00;
	case 'z': return 0x00001F0204081F00;

	default: return 0x0;
	}
}

void LCDGlassPanel::writeChar(uint8_t x, uint8_t y, char ch)
{
	if (y * __width + x >= __blocks.size()) return;
	LCDGlassPanelBlock5x8* block = __blocks.at(y * __width + x);
	block->setSymbol(ch);
}

QPoint LCDGlassPanel::calculatePinPosition(int i)
{
	return QPoint(i * 20 + 30, 0);
}

uint64_t LCDGlassPanel::getCustomSymbol(char symb)
{
	return uint64_t();
}

void LCDGlassPanel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(140, 193, 32));
}

void LCDGlassPanel::pinSignalChanged()
{
}

void LCDGlassPanel::shiftToLeft()
{
	for (uint8_t y = 0; y < __height; ++y)
	{
		LCDGlassPanelBlock5x8* block = __blocks.at(y * __width);
		for (uint8_t x = 1; x < __width; ++x)
		{
			__blocks[y * __width + x - 1] = __blocks.at(y * __width + x);
		}
		__blocks[y * __width + __width - 1] = block;
	}
}

void LCDGlassPanel::shiftToRight()
{
	for (uint8_t y = 0; y < __height; ++y)
	{
		LCDGlassPanelBlock5x8* block = __blocks.at(y * __width + __width - 1);
		for (uint8_t x = __width - 1; x > 0; --x)
		{
			__blocks[y * __width + x] = __blocks.at(y * __width + x - 1);
		}
		__blocks[0] = block;
	}
}