#ifndef LCD_MEASUREMENTS_H
#define LCD_MEASUREMENTS_H

#include <core.h>

struct LCDPhysicalSettings final
{
	struct Glass
	{
		struct Block
		{
			double __pixel_width;
			double __pixel_height;
			double __pixel_h_spacing;
			double __pixel_v_spacing;
			double __block_width;
			double __block_height;
		} __block_settings;
		double __block_h_spacing;
		double __block_v_spacing;
		double __blocks_width;
		double __blocks_height;
		double __viewport_width;
		double __viewport_height;
	} __glass_settings;

	struct Port
	{
		double __pinout_length;
		double __pin_hole_diameter;
	} __port_settings;

	double __pcb_width;
	double __pcb_height;
	double __pcb_hole_diameter;
	double __pcb_hole_h_distance;
	double __pcb_hole_v_distance;
	double __pin_margin;
	double __border_width;
	double __border_height;
};

#endif