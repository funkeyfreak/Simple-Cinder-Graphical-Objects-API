#ifndef _RECT_
#define _RECT_

#include "cinder/cairo/Cairo.h"

class Rect{
	double width;
	double height;
	double borderWidth;
	cinder::Vec2d center;
	cinder::Vec2d topRightCorner;
	cinder::ColorA color;
public:
	Rect(double width, double height, double borderWidth, cinder::Vec2d center, cinder::Vec2d topRightCorner, cinder::ColorA color) :
		width(width), height(height), borderWidth(borderWidth), center(center), topRightCorner(topRightCorner), color(color){}
	~Rect();
	void draw(cinder::cairo::Context &ctx) const;
	cinder::ColorA getColor();
	double getWidth();
	double getHeight();
	double getBorderWidth();
	cinder::Vec2d getTopRightCorner();
	cinder::Vec2d getCenter();
	void setCenter(cinder::Vec2d newCenter);
	void setTopRightCorner(cinder::Vec2d newTopRightCorner);
	void setWidth(double newWidth);
	void setHeight(double newHeight);
	void setBorderWidth(double newBorderWidth);
};

#endif /*_RECT_*/