#ifndef _GraphicalObjectApp_
#define _GraphicalObjectApp_

#include <vector>
#include <bitset>
#include <tchar.h>
#include <cinder/app/App.h>
#include <iostream>
#include "cinder/app/AppNative.h"
#include "cinder/cairo/Cairo.h"
#include "cinder/Rand.h"
//#include "../src/GraphicalObject.cpp"

class GraphicalObject {
	bool selectedGraphicalObject;
	cinder::Vec2d topLeftBCorner;
	cinder::Vec2d initialMouseLocation;
	cinder::Vec2d centerOfBoundingBox;
	cinder::Vec2d prevCenterOfBoundingBox;
	cinder::Vec2d prevTopLeftCorner;
	cinder::Vec2d activeCenterOfBoundingBox;
	cinder::Vec2d activeTopLeftCorner;
	double width;
	double height;
	cinder::ColorA color;
	virtual void doMouseEvent(cinder::app::MouseEvent event) = 0;
public:
	virtual ~GraphicalObject();
	virtual void draw(cinder::cairo::Context &ctx) = 0;
	virtual bool onMouseEvent(cinder::app::MouseEvent event);
	bool isSelectedGraphicalObject();
	cinder::Vec2d getTopLeftBCorner();
	cinder::Vec2d getInitialMouseLocation();
	cinder::Vec2d getCenterOfBoundingBox();
	cinder::Vec2d getPrevCenterOfBoundingBox();
	cinder::Vec2d getPrevTopLeftCorner();
	cinder::Vec2d getActiveCenterOfBoundingBox();
	cinder::Vec2d getActiveTopRightCorner();
	cinder::ColorA getColor();
	double getWidth();
	double getHeight();
	void setInitialMouseLocation(cinder::Vec2d newInitialMouseLocation);
	void setTopLeftBCorner(cinder::Vec2d newTopLeftBCorner);
	void setCenterOfBoundingBox(cinder::Vec2d newCenterOfBOundingBox);
	void setPrevCenterOfBoundingBox(cinder::Vec2d newPrevCenterOfBoundingBox);
	void setPrevTopLeftCorner(cinder::Vec2d newPrevTopLeftCorner);
	void setSelectedGraphicalObject(bool state);
	void setActiveCenterOfBoundingBox(cinder::Vec2d newActiveCenterOfBoundingBox);
	void setActiveTopLeftCorner(cinder::Vec2d newActiveTopRightCorner);
	void setColor(cinder::ColorA newColor);
	void setWidth(double newWidth);
	void setHeight(double newHeight);
	virtual void render(cinder::cairo::Context &ctx);
	virtual void adjustGraphicalObject(cinder::app::MouseEvent event);
};

#endif /*_GraphicalObjectApp_*/