#include <cinder/app/App.h>
#include "cinder/app/AppNative.h"
#include "cinder/cairo/Cairo.h"
#include "../vc2013/GraphicalObject.h"

// Destructor
GraphicalObject::~GraphicalObject(){
}
// Optional Render
void GraphicalObject::render(cinder::cairo::Context &ctx){

}
// Return top left most point
cinder::Vec2d  GraphicalObject::getTopLeftBCorner(){
	return topLeftBCorner;
}
// Returm initial mouse location point
cinder::Vec2d  GraphicalObject::getInitialMouseLocation(){
	return initialMouseLocation;
}
// Return the center of bounding box
cinder::Vec2d GraphicalObject::getCenterOfBoundingBox(){
	return centerOfBoundingBox;
}
// Return the previous center of boudingbox
cinder::Vec2d GraphicalObject::getPrevCenterOfBoundingBox(){
	return prevCenterOfBoundingBox;
}
// Return the previous top left corner of the boundingbox
cinder::Vec2d GraphicalObject::getPrevTopLeftCorner(){
	return prevTopLeftCorner;
}
// Returns the active center element. Use for updating object prior to comit
cinder::Vec2d GraphicalObject::getActiveCenterOfBoundingBox(){
	return activeCenterOfBoundingBox;
}
// Returns the active corner element. Use for updating object prior to comit
cinder::Vec2d GraphicalObject::getActiveTopRightCorner(){
	return activeTopLeftCorner;
}
// Return the width of the bounding box
double GraphicalObject::getWidth(){
	return width;
}
// Return the height of the bounding box
double GraphicalObject::getHeight(){
	return height;
}
// Check and see if mouse event is in applicaion window
bool GraphicalObject::onMouseEvent(cinder::app::MouseEvent event){
	if (((event.getX() <= topLeftBCorner.x) && 
		(event.getX() >= topLeftBCorner.x)) && 
		((event.getY() <= topLeftBCorner.y) && 
		(event.getY() >= topLeftBCorner.y))){

		selectedGraphicalObject = true;
		setPrevCenterOfBoundingBox(event.getPos());
		doMouseEvent(event);		
		return true;
	}
	else{
		return false;
	}
}
// Setting the top left corner of the bounding box
void GraphicalObject::setTopLeftBCorner(cinder::Vec2d newTopLeftBCorner){
	topLeftBCorner = newTopLeftBCorner;
}
// Setting the initialPosistion of the
void GraphicalObject::setInitialMouseLocation(cinder::Vec2d newInitialMouseLocation){
	initialMouseLocation = newInitialMouseLocation;
}
// Setting the center of the bound box
void GraphicalObject::setCenterOfBoundingBox(cinder::Vec2d newCenterOfBOundingBox){
	centerOfBoundingBox = newCenterOfBOundingBox;
}
// Setting the previous center of bounding box
void GraphicalObject::setPrevCenterOfBoundingBox(cinder::Vec2d newPrevCenterOfBoundingBox){
	prevCenterOfBoundingBox = newPrevCenterOfBoundingBox;
}
// Setting the previous top left corner of bounding box
void GraphicalObject::setPrevTopLeftCorner(cinder::Vec2d newPrevTopLeftCorner){
	prevCenterOfBoundingBox = newPrevTopLeftCorner;
}
// Setting the active center object
void GraphicalObject::setActiveCenterOfBoundingBox(cinder::Vec2d newActiveCenterOfBoudningBox){
	activeCenterOfBoundingBox = newActiveCenterOfBoudningBox;
}
// Setting the active corner object
void GraphicalObject::setActiveTopLeftCorner(cinder::Vec2d newActiveTopLeftCorner){
	activeTopLeftCorner = newActiveTopLeftCorner;
}
// Setting the color of the piece
void GraphicalObject::setColor(cinder::ColorA newColor){
	color = newColor;
}
// Setting the width of the GraphicalObject
void GraphicalObject::setWidth(double newWidth){
	width = newWidth;
}
// Setting the height of the GraphicalObject
void GraphicalObject::setHeight(double newHeight){
	height = newHeight;
}
// Alter The Object on Drag
void GraphicalObject::adjustGraphicalObject(cinder::app::MouseEvent event){
	cinder::Vec2d initialLocation = getInitialMouseLocation();
	if (initialLocation == cinder::Vec2d(.5, .5)){
		setInitialMouseLocation(event.getPos());
		return;
	}

	cinder::Vec2d difference = cinder::Vec2d(
		floor(
		(double)event.getX() - initialLocation.x), 
		floor(
		(double)event.getY() - initialLocation.y));

	setCenterOfBoundingBox(
		cinder::Vec2d(
		(getCenterOfBoundingBox().x + difference.x), 
		(getCenterOfBoundingBox().y + difference.y)));

	setTopLeftBCorner(
		cinder::Vec2d((getTopLeftBCorner().x + difference.x),
		(getTopLeftBCorner().y + difference.y)));

}
// Return the SelectedGraphicalObject variable
bool GraphicalObject::isSelectedGraphicalObject(){
	return selectedGraphicalObject;
}
// Set the boolean SelectedGraphicalObject
void GraphicalObject::setSelectedGraphicalObject(bool state){
	selectedGraphicalObject = state;
}
// Return the color of the object
cinder::ColorA GraphicalObject::getColor(){
	return color;
}