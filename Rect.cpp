#include "cinder/cairo/Cairo.h"
#include "../vc2013/Rect.h"

Rect::~Rect(){

}

void Rect::draw(cinder::cairo::Context &ctx) const{
	ctx.setSource(color);												//color
	ctx.rectangle(topRightCorner.x, topRightCorner.y, width, height);	//create rectangle
	ctx.setLineWidth(borderWidth);										//rectangle border width
	ctx.fill();															//paint
}

cinder::ColorA Rect::getColor(){
	return color;
}

double Rect::getWidth(){
	return width;
}

double Rect::getHeight(){
	return height;
}

double Rect::getBorderWidth(){
	return borderWidth;
}

cinder::Vec2d Rect::getTopRightCorner(){
	return topRightCorner;
}

cinder::Vec2d Rect::getCenter(){
	return center;
}

void Rect::setCenter(cinder::Vec2d newCenter){
	center = newCenter;
}

void Rect::setTopRightCorner(cinder::Vec2d newTopRightCorner){
	topRightCorner = newTopRightCorner;
}

void Rect::setWidth(double newWidth){
	width = newWidth;
}

void Rect::setHeight(double newHeight){
	height = newHeight;
}

void Rect::setBorderWidth(double newBorderWidth){
	borderWidth = newBorderWidth;
}
