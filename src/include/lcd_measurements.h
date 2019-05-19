#ifndef LCD_MEASUREMENTS_H
#define LCD_MEASUREMENTS_H

struct LCDPhysicalSettings final
{
	double __pixel_width;
	double __pixel_height;
	double __pixel_h_spacing;
	double __pixel_v_spacing;
	double __block_width;
	double __block_height;
	double __block_h_spacing;
	double __block_v_spacing;
	double __blocks_width;
	double __blocks_height;
	double __viewport_width;
	double __viewport_height;
	double __pinout_length;
	double __pin_hole_diameter;
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