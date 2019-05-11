#pragma once

#define ZOOM_FACTOR 2
#define TO_INCH(mm) ((mm) * 0.0393700787)
#define NORMALIZE_X(value) ((logicalDpiX() * (TO_INCH(value))) * ZOOM_FACTOR)
#define NORMALIZE_Y(value) ((logicalDpiY() * (TO_INCH(value))) * ZOOM_FACTOR)