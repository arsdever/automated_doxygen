#pragma once

#ifndef ZOOM_FACTOR
#define ZOOM_FACTOR 1
#endif
#define TO_INCH(mm) ((mm) * 0.0393700787)
#define NORMALIZE_X(value) ((physicalDpiX() * (TO_INCH(value))) * ZOOM_FACTOR)
#define NORMALIZE_Y(value) ((physicalDpiY() * (TO_INCH(value))) * ZOOM_FACTOR)