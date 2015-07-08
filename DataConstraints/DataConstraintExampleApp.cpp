#include <vector>
#include <iostream>
#include <cmath>
#include "cinder/app/AppNative.h"
#include "cinder/cairo/Cairo.h"
#include "cinder/Rand.h"
#include "../vc2013/DataConstraints.h"

using namespace ci;
using namespace ci::app;
using namespace std;

struct Point{
	Constraint x;
	Constraint y;
	Point(int x, int y) : x(x), y(y){}
	Point() : Point(0, 0) {}
};

class Box{
public:
	Point center,
		left_top,
		right_bottom;
	Color color;
	virtual ~Box(){}
protected:
	virtual void initilize(){
		left_top.x.setFormula(center.x - width / 2);
		left_top.y.setFormula(center.y - height / 2);
		right_bottom.x.setFormula(center.x + width / 2);
		right_bottom.y.setFormula(center.y + height / 2);
	}
public:
		Box(Point& center, Color& color) : center(center), color(color){
			initilize();
		}
		Box(Box&) = delete;
		Box &operator=(Box&) = delete;
		void move(Point& pt){
			center.x = pt.x;
			center.y = pt.y;
		}
		void moveSet(Point& pt){
			center.x.set(pt.x.get());
			center.y.set(pt.y.get());
		}
		void draw(cairo::Context ctx){
			ctx.setSource(color);
			ctx.rectangle(left_top.x, left_top.y, width, height);
			ctx.fill();
		}
		static const int width, height;
};

const int Box::width = 50, Box::height = 30;

class BoxHelper : public Box{
protected:
	Box &dep;
public:
	void initilize() override{
		Box::initilize();
		center.x.setFormula(dep.left_top.x + dep.width + 50);
		center.y.setFormula(dep.left_top.y + dep.height / 2);
	}
public:
	BoxHelper(Box& other, Color& color) : Box(other.center, color), dep(other){
		initilize();
	}
	BoxHelper(BoxHelper& other) : Box(other.center, other.color), dep(other){
		initilize();
	}
	BoxHelper &operator=(const BoxHelper&) = delete;
};

class DataConstraintExampleApp : public AppNative {
	vector<Box> boxes;
/*protected:
	Box redBox;
	BoxHelper greenBox;
	BoxHelper blueBox;
	bool isRed,
		isBlue,
		isGreen;
	Constraint redBoxCenterX, redBoxCenterY;
public:
	DataConstraintExampleApp() : redBox(Point(50, 50), Color(1.0, 0.0, 0.0)),
		greenBox(redBox, Color(0.0, 1.0, 0.0)),
		blueBox(greenBox, Color(0.0, 0.0, 1.0)),
		isRed(false), isBlue(false), isGreen(false){
		redBoxCenterX.setFormula((int)redBox.center.x);
		redBoxCenterY.setFormula((int)redBox.center.y);
	}
	*/
public:
	void setup() override;
	void mouseDown(MouseEvent event) override;
	void mouseUp(MouseEvent event) override;
	void mouseDrag(MouseEvent event) override;
	void update() override;
	void draw() override;
	void renderScene(cairo::Context &ctx);
	void prepareSettings(Settings *settings) override;
};

void DataConstraintExampleApp::setup()
{
}

void DataConstraintExampleApp::update(){
}

Box redBox(Point(50, 50), Color(1.0, 0.0, 0.0));
BoxHelper greenBox(redBox, Color(0.0, 1.0, 0.0));
BoxHelper blueBox(greenBox, Color(0.0, 0.0, 1.0));
bool isRed(false), isBlue(false), isGreen(false);

void DataConstraintExampleApp::mouseDown( MouseEvent event )
{
	int x = event.getX(),
		y = event.getY();

	if ((x > redBox.left_top.x) && (x < redBox.right_bottom.x) && (y < redBox.right_bottom.y) && (y > redBox.left_top.y)){
		isRed = true;
		greenBox.center.x.setFormula(redBox.left_top.x + redBox.width + 50);
		greenBox.center.y.setFormula(redBox.left_top.y + redBox.height / 2);
		blueBox.center.x.setFormula(greenBox.left_top.x + greenBox.width + 50);
		blueBox.center.y.setFormula(greenBox.left_top.y + greenBox.height / 2);
	}
	else if ((x > greenBox.left_top.x) && (x < greenBox.right_bottom.x) && (y < greenBox.right_bottom.y) && (y > greenBox.left_top.y)){
		isBlue = true;
		blueBox.center.x.setFormula(greenBox.left_top.x + greenBox.width + 50);
		blueBox.center.y.setFormula(greenBox.left_top.y + greenBox.height / 2);
	}
	else if ((x > blueBox.left_top.x) && (x < blueBox.right_bottom.x) && (y < blueBox.right_bottom.y) && (y > blueBox.left_top.y)){
		isGreen = true;
	}
}

void DataConstraintExampleApp::mouseUp(MouseEvent event)
{
	isRed = isBlue = isGreen = false;
}

void DataConstraintExampleApp::mouseDrag(MouseEvent event)
{
	int x = event.getX(),
		y = event.getY();
	if (isRed){
		redBox.move(Point(x, y));
	}
	else if (isBlue){
		greenBox.move(Point(x, y));
	}
	else if (isGreen){
		blueBox.move(Point(x, y));
	}
	//debug
	//cout << endl << redBox.right_bottom.x << " , " << redBox.right_bottom.y << endl << greenBox.right_bottom.x << " , " << greenBox.right_bottom.y << endl << blueBox.right_bottom.x << " , " << blueBox.right_bottom.y << endl << endl;
}


void DataConstraintExampleApp::prepareSettings(Settings *settings)
{
	settings->enableConsoleWindow();
}

void DataConstraintExampleApp::renderScene(cairo::Context &ctx)
{
	ctx.setSourceRgb(0.9, 0.9, 0.9);
	ctx.paint();

	redBox.draw(ctx);
	greenBox.draw(ctx);
	blueBox.draw(ctx);
	ctx.stroke();
}

void DataConstraintExampleApp::draw()
{
	// clear out the window with black
	cairo::Context ctx(cairo::createWindowSurface());

	renderScene(ctx);

}

CINDER_APP_NATIVE(DataConstraintExampleApp, Renderer2d)
