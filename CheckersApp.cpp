#include <vector>
#include <iostream>
#include <cmath>
#include <cinder/app/App.h>
#include "cinder/app/AppNative.h"
#include "cinder/cairo/Cairo.h"
#include "cinder/Rand.h"
#include "../vc2013/Rect.h"
#include "../vc2013/GraphicalObject.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CheckerPiece : public GraphicalObject{
	bool crowned;
	bool captured;
	double radius;
	char player;
	int arrayLocation;
	void doMouseEvent(cinder::app::MouseEvent event) override;
public:
	CheckerPiece(bool selectedGraphicalObject,
		Vec2d topLeftBCorner,
		Vec2d initialMouseLocation,
		Vec2d centerOfBoundingBox,
		double width,
		double height,
		cinder::ColorA color,
		bool newCrowned,
		bool newCaptured,
		double newRadius,
		char newPlayer,
		int newArrayLocation);
	~CheckerPiece() override;
	void crownCheckerPiece();
	void setArrayLocation(int newArrayLocation);
	void adjustGraphicalObject(cinder::app::MouseEvent event) override;
	//void doMouseEvent(cinder::app::MouseEvent event) override;
	void draw(cinder::cairo::Context &ctx) override;
	bool onMouseEvent(cinder::app::MouseEvent event) override;
	bool getStatus();
	void setCaptured(bool status);
	double getRadius();
	char getPlayer();
	int getArrayLocation();
};

CheckerPiece::CheckerPiece(bool selectedGraphicalObject,
	Vec2d topLeftBCorner,
	Vec2d initialMouseLocation,
	Vec2d centerOfBoundingBox,
	double width,
	double height,
	cinder::ColorA color,
	bool newCrowned,
	bool newCaptured,
	double newRadius,
	char newPlayer,
	int newArrayLocation){
	setSelectedGraphicalObject(selectedGraphicalObject);
	setTopLeftBCorner(topLeftBCorner);
	//defualt value set to initialMouseLocation
	setInitialMouseLocation(Vec2d(.5, .5));
	setCenterOfBoundingBox(centerOfBoundingBox);
	// All newer member variables, end ABC setter use
	setWidth(width);
	setHeight(height);
	setColor(color);
	crowned = newCrowned;
	captured = newCaptured;
	radius = newRadius;
	player = newPlayer;
	arrayLocation = newArrayLocation;
}

CheckerPiece::~CheckerPiece(){

}

char CheckerPiece::getPlayer(){
	return player;
}

int CheckerPiece::getArrayLocation(){
	return arrayLocation;
}

void CheckerPiece::setArrayLocation(int newArrayLocation){
	arrayLocation = newArrayLocation;
}

bool CheckerPiece::onMouseEvent(cinder::app::MouseEvent event){

	Vec2d center = getCenterOfBoundingBox();
	double x = (double)event.getX();
	double y = (double)event.getY();
	double dist = sqrt(pow((y - center.y), 2) + pow((x - center.x), 2));
	if (dist < radius){
		setPrevCenterOfBoundingBox(getCenterOfBoundingBox());

		setSelectedGraphicalObject(true);
		//doMouseEvent(event);
		return true;
	}
	return false;
}

void CheckerPiece::setCaptured(bool status){
	captured = status;
}

bool CheckerPiece::getStatus(){
	return captured;
}

double CheckerPiece::getRadius(){
	return radius;
}

void CheckerPiece::draw(cinder::cairo::Context &ctx){
	ctx.setSource(getColor());													//set color
	ctx.setLineWidth(10);														//set line width
	ctx.circle(getCenterOfBoundingBox().x, getCenterOfBoundingBox().y, radius);	//set mask
	ctx.fill();																	//paint
}

void CheckerPiece::adjustGraphicalObject(cinder::app::MouseEvent event){
	Vec2d initialLocation = getInitialMouseLocation();
	if (initialLocation == Vec2d(.5, .5)){
		setInitialMouseLocation(event.getPos());
		return;
	}

	Vec2d difference = Vec2d(floor((double)event.getX() - initialLocation.x), floor((double)event.getY() - initialLocation.y));
	setCenterOfBoundingBox(Vec2d((getCenterOfBoundingBox().x + difference.x), (getCenterOfBoundingBox().y + difference.y)));
	setTopLeftBCorner(Vec2d((getTopLeftBCorner().x + difference.x), (getTopLeftBCorner().y + difference.y)));
	setInitialMouseLocation(event.getPos());
}

void CheckerPiece::doMouseEvent(cinder::app::MouseEvent event){

}

class Board{
	vector<CheckerPiece> NewBoard;
	vector<CheckerPiece> Captured;
public:
	Board();
	~Board();
	bool isOccupied(Vec2d boardLocation);
	void updateBoard();

};

Board::Board(){
	//Initilize a new board

}

class OccupencyGrid{
	std::vector<std::vector<Vec2d>> grid;
public:
	OccupencyGrid();
	OccupencyGrid(std::vector<std::vector<Vec2d>> newOccupencyGrid);
	OccupencyGrid(std::vector<Vec2d> listOfCenterPoints);
	~OccupencyGrid();
	std::vector<std::vector<Vec2d>> getOccupencyGrid();
	void setOccupencyGrid(std::vector<std::vector<Vec2d>> newOccupencyGrid);
	void refreshOcupencyGrid(std::vector<Vec2d> listOfCenterPoints);
};

OccupencyGrid::OccupencyGrid(){
}

OccupencyGrid::~OccupencyGrid(){
}

OccupencyGrid::OccupencyGrid(std::vector<std::vector<Vec2d>> newOccupencyGrid){
	grid = newOccupencyGrid;
}

OccupencyGrid::OccupencyGrid(std::vector<Vec2d> listOfCenterPoints){
	std::vector<Vec2d> Column;
	int outSideItterator = 0;
	grid.push_back(Column);
	for (unsigned int i = 0; i < listOfCenterPoints.size(); i++){
		grid[outSideItterator].push_back(listOfCenterPoints[i]);
		if (((i + 2) % 8) == 1 && (i >= 7) && (i < listOfCenterPoints.size() - 1)){
			outSideItterator++;
			grid.push_back(Column);
		}
	}
}

std::vector<std::vector<Vec2d>> OccupencyGrid::getOccupencyGrid(){
	return grid;
}

void OccupencyGrid::setOccupencyGrid(std::vector<std::vector<Vec2d>> newOccupencyGrid){
	grid = newOccupencyGrid;
}

void OccupencyGrid::refreshOcupencyGrid(std::vector<Vec2d> listOfCenterPoints){
	grid.erase(grid.begin(), grid.end());
	std::vector<Vec2d> Column;
	int outSideItterator = 0;
	grid.push_back(Column);
	for (unsigned int i = 0; i < listOfCenterPoints.size(); i++){
		grid[outSideItterator].push_back(listOfCenterPoints[i]);
		if (((i + 2) % 8) == 1 && (i >= 7) && (i < listOfCenterPoints.size() - 1)){
			outSideItterator++;
			grid.push_back(Column);
		}
	}
}

class CheckersApp : public AppNative {
	//std::vector<CheckerPiece> newBoard;
	//std::vector<CheckerPiece> captured;
	std::vector<CheckerPiece> pieces;
	std::vector<Rect> rectangles;
	std::vector<Vec2d> centerPoints;
	OccupencyGrid occupencyGrid;
	bool turn; // 0 for black, 1 for red
public:
	bool nonKingMove();
	bool isOccupied(int arrayLocation);
	bool lookAhead(CheckerPiece &checker);
	char whichPlayer(int arrayLocation);
	int closestRectangle(CheckerPiece &checker);
	int currentRectangle(Vec2d previousCenter);
	int rectToCheckerAddress(int address);
	void setup() override;
	void mouseDown(MouseEvent event) override;
	void mouseUp(MouseEvent event) override;
	void mouseDrag(MouseEvent event) override;
	void update() override;
	void draw() override;
	void resize() override;
	void renderScene(cairo::Context &ctx);
	void constructBoard(int width, int height);
	void loadCenterPoints();
	void constructCheckerPieces();
	//Vec2d closestLegalPosistion(CheckerPiece checker);
	void closestLegalPosistion(CheckerPiece &checker);
	void prepareSettings(Settings *settings) override;
	void finishTurn();
	void revertTurn(CheckerPiece &checker);
	void executeTurn(CheckerPiece &checker, int newArrayIndex);
};

// closestLegalPosistion to the node
/*Vec2d CheckersApp::closestLegalPosistion(CheckerPiece checker){
	double distance			= 0,
	curBestDistance	= INT_MAX;
	int indexBestDistance = 0;
	Vec2d center;

	for (int i = 0; i < rectangles.size(); i++){
	center = rectangles[i].getCenter();
	distance = sqrt(pow((center.y - checker.getCenterOfBoundingBox().y), 2) + pow((center.x - checker.getCenterOfBoundingBox().x), 2));
	if (curBestDistance < distance){
	curBestDistance = distance;
	indexBestDistance = i;
	}
	}

	checker.setCenterOfBoundingBox[rectangles[indexBestDistance].getCenter()];
	return rectangles[indexBestDistance].getCenter();
	}*/
char CheckersApp::whichPlayer(int arrayLocation){
	for (int i = 0; i < pieces.size(); i++){
		if (pieces[i].getArrayLocation() == arrayLocation){
			return pieces[i].getPlayer();
		}
	}
	return 'n';
}

bool CheckersApp::isOccupied(int arrayLocation){
	for (unsigned int i = 0; i < pieces.size(); i++){
		if (rectangles[arrayLocation].getCenter() == pieces[i].getCenterOfBoundingBox()){
			return true;
		}
	}
	return false;
}

void CheckersApp::executeTurn(CheckerPiece &checker, int newArrayIndex){
	checker.setCenterOfBoundingBox(rectangles[newArrayIndex].getCenter());
	checker.setTopLeftBCorner(rectangles[newArrayIndex].getTopRightCorner());
	checker.setArrayLocation(newArrayIndex);
}

// Reverts the object to pre-drag status
void CheckersApp::revertTurn(CheckerPiece &checker){
	Vec2d oldCenter, oldTopLeft;
	oldCenter = checker.getPrevCenterOfBoundingBox();
	oldTopLeft = checker.getPrevTopLeftCorner();
	checker.setCenterOfBoundingBox(oldCenter);
	checker.setTopLeftBCorner(oldTopLeft);
}

// Simply changes the current player at the end of a turn
void CheckersApp::finishTurn(){
	turn = !turn;
}

// Looks ahead if jump was made to see if multi-jumps are available
bool CheckersApp::lookAhead(CheckerPiece &checker){
	/*int checkerLocation = checker.getArrayLocation();
	char checkerPlayer = checker.getPlayer();
	if (!(checkerLocation > 53) || (checkerLocation < 8)){
		if (checkerPlayer == 'b'){
			if (checkerLocation % 8 == 0){
				int intermediate = checkerLocation + 9;
				if (isOccupied(intermediate)){
					if (whichPlayer(intermediate) == 'r'){
						if (checkerLocation > 47){
							return false;
						}
						else{
							if (isOccupied(intermediate + 9)){
								return false;
							}
							else{
								return true;
							}
						}
					}
					else{
						return false;
					}
				}
				else{
					return false;
				}
			}
			else if ((checkerLocation + 1) % 8 == 0){
				int intermediate = checkerLocation + 7;
				if (isOccupied(intermediate)){
					if (whichPlayer(intermediate) == 'r'){
						if (checkerLocation > 47){
							return false;
						}
						else{
							if (isOccupied(intermediate + 7)){
								return false;
							}
							else{
								return true;
							}
						}
					}
					else{
						return false;
					}
				}
				else{
					return false;
				}
			}
			else{
				int intermediate1 = checkerLocation + 7;
				int intermediate2 = checkerLocation + 9;
				if (isOccupied(intermediate1)){
					if (whichPlayer(intermediate1) == 'r'){
						if (checkerLocation > 47){
							return false;
						}
						else{
							if (isOccupied(intermediate1 + 7)){
								//return false;
							}
							else{
								return true;
							}
						}
					}
				}
				if (isOccupied(intermediate2)){
					if (whichPlayer(intermediate2) == 'r'){
						if (checkerLocation > 47){
							return false;
						}
						else{
							if (isOccupied(intermediate2 + 9)){
								return false;
							}
							else{
								return true;
							}
						}
					}
				}
				else{
					return false;
				}
			}
		}
		else if (checkerPlayer == 'r'){
			if (checkerLocation % 8 == 0){
				int intermediate = checkerLocation + 7;
				if (isOccupied(intermediate)){
					if (whichPlayer(intermediate) == 'b'){
						if (checkerLocation < 16){
							return false;
						}
						else{
							if (isOccupied(intermediate + 7)){
								return false;
							}
							else{
								return true;
							}
						}
					}
					else{
						return false;
					}
				}
				else{
					return false;
				}
			}
			else if ((checkerLocation + 1) % 8 == 0){
				int intermediate = checkerLocation + 9;
				if (isOccupied(intermediate)){
					if (whichPlayer(intermediate) == 'b'){
						if (checkerLocation < 16){
							return false;
						}
						else{
							if (isOccupied(intermediate + 9)){
								return false;
							}
							else{
								return true;
							}
						}
					}
					else{
						return false;
					}
				}
				else{
					return false;
				}
			}
			else{
				int intermediate1 = checkerLocation + 7;
				int intermediate2 = checkerLocation + 9;
				if (isOccupied(intermediate1)){
					if (whichPlayer(intermediate1) == 'b'){
						if (checkerLocation < 16){
							return false;
						}
						else{
							if (isOccupied(intermediate1 + 7)){
								//return false;
							}
							else{
								return true;
							}
						}
					}
				}
				if (isOccupied(intermediate2)){
					if (whichPlayer(intermediate2) == 'b'){
						if (checkerLocation < 16){
							return false;
						}
						else{
							if (isOccupied(intermediate2 + 9)){
								return false;
							}
							else{
								return true;
							}
						}
					}
				}
				else{
					return false;
				}
			}
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}*/
return false;

}

int CheckersApp::rectToCheckerAddress(int address){
	for (int i = 0; i < pieces.size(); i++){
		if (pieces[i].getArrayLocation() == address){
			return i;
		}
	}
}

void CheckersApp::closestLegalPosistion(CheckerPiece &checker){
	//check Player
	char curPlayer = checker.getPlayer();
	int selectedRectangle;
	int jumpDirection;
	//handle black pieces
	if (curPlayer == 'b'){
		//is it blacks turn?
		if (turn == false){
			int currentLocation = checker.getArrayLocation();
			selectedRectangle = closestRectangle(checker);
			//if we are currently at the left edge
			if (currentLocation % 8 == 0){
				//if the selected location is 9 units away, we can make this move
				if ((selectedRectangle - currentLocation) == 9){
					if (isOccupied(selectedRectangle)){
						revertTurn(checker);
						return;
					}
					else{
						executeTurn(checker, selectedRectangle);
						finishTurn();
						return;
					}
				}
				//if the selected location is 18 units away, we need more logic to 
				//see if this is a legal move
				else if ((selectedRectangle - currentLocation) == 18){
					int intermediateLocation = selectedRectangle - 9;
					//is the rectangle we are jumping over occupied?
					if (isOccupied(intermediateLocation)){
						//is the occupied rectangle occupied by the oponet?
						if (whichPlayer(intermediateLocation) == 'r'){
							//go and jump over the piece!
							executeTurn(checker, selectedRectangle);
							//look ahead to see if any double etc jumps lie ahead
							if (lookAhead(checker)){
								//end this seshion, still blacks turn
								return;
							}
							//if no results from look ahead, end turn
							finishTurn();
							return;
						}
						//well, looks like a missplaced checker! REVERT
						else{
							revertTurn(checker);
							return;
						}
					}
					//well, looks like a missplaced checker! REVERT
					else{
						revertTurn(checker);
						return;
					}
				}
				//otherwise exit
				else{
					revertTurn(checker);
					return;
				}
			}
			//if we are currently at the right edge
			else if ((currentLocation + 1) % 8 == 0){
				//if the selected location is 7 units away, we can make this move
				if ((selectedRectangle - currentLocation) == 7){
					if (isOccupied(selectedRectangle)){
						revertTurn(checker);
						return;
					}
					else{
						executeTurn(checker, selectedRectangle);
						finishTurn();
						return;
					}
				}
				else if ((selectedRectangle - currentLocation) == 14){
					int intermediateLocation = selectedRectangle - 7;
					//is the rectangle we are jumping over occupied?
					if (isOccupied(intermediateLocation)){
						//is the occupied rectangle occupied by the oponet?
						if (whichPlayer(intermediateLocation) == 'r'){
							int jumped = rectToCheckerAddress(intermediateLocation);
							pieces[jumped].setCaptured(true);
							//go and jump over the piece!
							executeTurn(checker, selectedRectangle);
							//look ahead to see if any double etc jumps lie ahead
							if (lookAhead(checker)){
								//end this seshion, still blacks turn
								return;
							}
							//if no results from look ahead, end turn
							finishTurn();
							return;
						}
						//well, looks like a missplaced checker! REVERT
						else{
							revertTurn(checker);
							return;
						}
					}
					//well, looks like a missplaced checker! REVERT
					else{
						revertTurn(checker);
						return;
					}
				}
				//otherwise exit
				else{
					revertTurn(checker);
					return;
				}
			}
			else if (((selectedRectangle - currentLocation) == 18) || ((selectedRectangle - currentLocation) == 14)){
				int intermediateLocation = selectedRectangle - ((selectedRectangle - currentLocation) / 2);
				//is the rectangle we are jumping over occupied?
				if (isOccupied(intermediateLocation)){
					//is the occupied rectangle occupied by the oponet?
					if (whichPlayer(intermediateLocation) == 'r'){
						//go and jump over the piece!
						int jumped = rectToCheckerAddress(intermediateLocation);
						pieces[jumped].setCaptured(true);
						executeTurn(checker, selectedRectangle);
						//look ahead to see if any double etc jumps lie ahead
						if (lookAhead(checker)){
							//end this seshion, still blacks turn
							return;
						}
						//if no results from look ahead, end turn
						finishTurn();
						return;
					}
					//well, looks like a missplaced checker! REVERT
					else{
						revertTurn(checker);
						return;
					}
				}
				//well, looks like a missplaced checker! REVERT
				else{
					revertTurn(checker);
					return;
				}
			}
			else{
				//if the selected location is 7/9 units away, we can make this move
				if (((selectedRectangle - currentLocation) == 7) || ((selectedRectangle - currentLocation) == 9)){
					if (isOccupied(selectedRectangle)){
						revertTurn(checker);
						return;
					}
					else{
						executeTurn(checker, selectedRectangle);
						finishTurn();
						return;
					}
				}
				//otherwise exit
				else{
					revertTurn(checker);
					return;
				}
			}
			//check for legal move
		}
		else{
			revertTurn(checker);
			return;
		}
	}
	else if (curPlayer == 'r'){
		//is it reds turn?
		if (turn == true){
			int currentLocation = checker.getArrayLocation();
			selectedRectangle = closestRectangle(checker);
			//if we are currently at the left edge
			if ((currentLocation) % 8 == 0){
				//if the selected location is 9 units away, we can make this move
				if ((currentLocation - selectedRectangle) == 7){
					if (isOccupied(selectedRectangle)){
						revertTurn(checker);
						return;
					}
					else{
						executeTurn(checker, selectedRectangle);
						finishTurn();
						return;
					}
				}
				else if ((currentLocation - selectedRectangle) == 14){
					int intermediateLocation = selectedRectangle - 7;
					//is the rectangle we are jumping over occupied?
					if (isOccupied(intermediateLocation)){
						//is the occupied rectangle occupied by the oponet?
						if (whichPlayer(intermediateLocation) == 'b'){
							int jumped = rectToCheckerAddress(intermediateLocation);
							pieces[jumped].setCaptured(true);
							//go and jump over the piece!
							executeTurn(checker, selectedRectangle);
							//look ahead to see if any double etc jumps lie ahead
							if (lookAhead(checker)){
								//end this seshion, still blacks turn
								return;
							}
							//if no results from look ahead, end turn
							finishTurn();
							return;
						}
						//well, looks like a missplaced checker! REVERT
						else{
							revertTurn(checker);
							return;
						}
					}
					//well, looks like a missplaced checker! REVERT
					else{
						revertTurn(checker);
						return;
					}
				}
				//otherwise exit
				else{
					revertTurn(checker);
					return;
				}
			}
			//if we are currently at the right edge
			else if ((currentLocation + 1) % 8 == 0){
				//if the selected location is 7 units away, we can make this move
				if ((currentLocation - selectedRectangle) == 9){
					if (isOccupied(selectedRectangle)){
						revertTurn(checker);
						return;
					}
					else{
						executeTurn(checker, selectedRectangle);
						finishTurn();
						return;
					}
				}
				else if ((currentLocation - selectedRectangle) == 18){
					int intermediateLocation = selectedRectangle - 9;

					//is the rectangle we are jumping over occupied?
					if (isOccupied(intermediateLocation)){
						//is the occupied rectangle occupied by the oponet?
						if (whichPlayer(intermediateLocation) == 'r'){
							int jumped = rectToCheckerAddress(intermediateLocation);
							pieces[jumped].setCaptured(true);
							//go and jump over the piece!
							executeTurn(checker, selectedRectangle);
							//look ahead to see if any double etc jumps lie ahead
							if (lookAhead(checker)){
								//end this seshion, still blacks turn
								return;
							}
							//if no results from look ahead, end turn
							finishTurn();
							return;
						}
						//well, looks like a missplaced checker! REVERT
						else{
							revertTurn(checker);
							return;
						}
					}
					//well, looks like a missplaced checker! REVERT
					else{
						revertTurn(checker);
						return;
					}
				}
				//otherwise exit
				else{
					revertTurn(checker);
					return;
				}
			}
			else if (((currentLocation - selectedRectangle) == 18) || ((currentLocation - selectedRectangle) == 14)){
				int intermediateLocation = selectedRectangle - ((currentLocation - selectedRectangle) / 2);
				intermediateLocation = intermediateLocation + (currentLocation - selectedRectangle);
				//is the rectangle we are jumping over occupied?
				if (isOccupied(intermediateLocation)){
					//is the occupied rectangle occupied by the oponet?
					if (whichPlayer(intermediateLocation) == 'b'){
						int jumped = rectToCheckerAddress(intermediateLocation);
						pieces[jumped].setCaptured(true);
						//go and jump over the piece!
						executeTurn(checker, selectedRectangle);
						//look ahead to see if any double etc jumps lie ahead
						if (lookAhead(checker)){
							//end this seshion, still blacks turn
							return;
						}
						//if no results from look ahead, end turn
						finishTurn();
						return;
					}
					//well, looks like a missplaced checker! REVERT
					else{
						revertTurn(checker);
						return;
					}
				}
				//well, looks like a missplaced checker! REVERT
				else{
					revertTurn(checker);
					return;
				}
			}
			else{
				//if the selected location is 7/9 units away, we can make this move
				if (((currentLocation - selectedRectangle) == 7) || ((currentLocation - selectedRectangle) == 9)){
					if (isOccupied(selectedRectangle)){
						revertTurn(checker);
						return;
					}					
					else{
						executeTurn(checker, selectedRectangle);
						finishTurn();
						return;
					}
				}
				//otherwise exit
				else{
					revertTurn(checker);
					return;
				}

			}
			//check for legal move

		}
		else{
			revertTurn(checker);
			return;
		}
	}



	//checker.setCenterOfBoundingBox(rectangles[indexBestDistance].getCenter());
	//checker.setTopLeftBCorner(rectangles[indexBestDistance].getTopRightCorner());
}

// Returns
int CheckersApp::currentRectangle(Vec2d previousCenter){
	return 0;
}

// Returns the closest rectangles array posistion, regardless of legality
int CheckersApp::closestRectangle(CheckerPiece &checker){
	double distance = 0,
		curBestDistance = INT_MAX;
	int indexBestDistance = 0;
	Vec2d center;

	for (unsigned int i = 0; i < rectangles.size(); i++){
		center = rectangles[i].getCenter();
		distance = sqrt(pow((center.y - checker.getCenterOfBoundingBox().y), 2) + pow((center.x - checker.getCenterOfBoundingBox().x), 2));
		if (curBestDistance > distance){
			curBestDistance = distance;
			indexBestDistance = i;
		}
	}
	return indexBestDistance;
}

// Create the CheckerPieces
void CheckersApp::constructCheckerPieces(){
	//black CheckerPieces (loaded at the top)
	// [ ][b][ ][b][ ][b][ ][b]
	// [b][ ][b][ ][b][ ][b][ ]
	// [ ][b][ ][b][ ][b][ ][b]
	// [ ][ ][ ][ ][ ][ ][ ][ ]
	// [ ][ ][ ][ ][ ][ ][ ][ ]
	// [ ][ ][ ][ ][ ][ ][ ][ ]
	// [ ][ ][ ][ ][ ][ ][ ][ ]
	// [ ][ ][ ][ ][ ][ ][ ][ ]
	bool skipRedSpace = true;
	//set checker's width to 5% smaller than the board square
	double checkerWidthHeight = rectangles[22].getWidth() - (rectangles[22].getWidth()*.05);
	double checkerRadius = checkerWidthHeight / 2;
	for (int i = 0; i < 24; i++){
		if (!skipRedSpace){
			/*(bool selectedGraphicalObject,
				Vec2d topLeftBCorner,
				Vec2d initialMouseLocation,
				Vec2d centerOfBoundingBox,
				int width,
				int height,
				cinder::ColorA color,
				bool newCrowned,
				bool newCaptured,
				double newRadius,
				char newPlayer)*/
			rectangles[i].getTopRightCorner();
			pieces.push_back(CheckerPiece(false, rectangles[i].getTopRightCorner(), Vec2d(.5, .5), rectangles[i].getCenter(), checkerWidthHeight, checkerWidthHeight, ColorA(CM_HSV, 1, 0, 0, 1), false, false, checkerRadius, 'b', i));
			//toggle skipRedSpace
			skipRedSpace = !skipRedSpace;

		}
		//toggle skipRedSpace
		else
			skipRedSpace = !skipRedSpace;
		if (i == 7 || i == 15)
			skipRedSpace = !skipRedSpace;
	}
	//red CheckerPieces (loaded at the bottom
	// [ ][b][ ][b][ ][b][ ][b]
	// [b][ ][b][ ][b][ ][b][ ]
	// [ ][b][ ][b][ ][b][ ][b]
	// [ ][ ][ ][ ][ ][ ][ ][ ]
	// [ ][ ][ ][ ][ ][ ][ ][ ]
	// [r][ ][r][ ][r][ ][r][ ]
	// [ ][r][ ][r][ ][r][ ][r]
	// [r][ ][r][ ][r][ ][r][ ]
	for (int i = 40; i < 64; i++){
		if (skipRedSpace){
			/*(bool selectedGraphicalObject,
			Vec2d topLeftBCorner,
			Vec2d initialMouseLocation,
			Vec2d centerOfBoundingBox,
			int width,
			int height,
			cinder::ColorA color,
			bool newCrowned,
			bool newCaptured,
			double newRadius,
			char newPlayer)*/
			rectangles[i].getTopRightCorner();
			pieces.push_back(CheckerPiece(false, rectangles[i].getTopRightCorner(), Vec2d(.5, .5), rectangles[i].getCenter(), checkerWidthHeight, checkerWidthHeight, ColorA(CM_HSV, 1, 1, 1, 1), false, false, checkerRadius, 'r', i));
			//toggle skipRedSpace
			skipRedSpace = !skipRedSpace;
		}
		//toggle skipRedSpace
		else
			skipRedSpace = !skipRedSpace;
		if (i == 47 || i == 55)
			skipRedSpace = !skipRedSpace;
	}
}


// Prepare the game pre-draw
void CheckersApp::prepareSettings(Settings *settings)
{
	settings->enableConsoleWindow();
	settings->setWindowSize(900, 900);
	int x = 900;
	int y = 900;

	turn = false;

	constructBoard(y, x);
	loadCenterPoints();
	occupencyGrid.refreshOcupencyGrid(centerPoints);
	constructCheckerPieces();
}


void CheckersApp::loadCenterPoints(){
	if (centerPoints.size() != 0){
		centerPoints.erase(centerPoints.begin(), centerPoints.end());
	}
	/*for (int i = rectangles.size(); i > 0; i--){
		centerPoints.push_back(rectangles[i].getCenter());
		}*/
	for (int i = 0; i < rectangles.size(); i++){
		centerPoints.push_back(rectangles[i].getCenter());
	}
}

void CheckersApp::setup()
{

}

void CheckersApp::mouseDown(MouseEvent event){
	if (event.isLeft()){
		/*for (unsigned int i = 0; i < pieces.size(); i++){
			if (pieces[i + 1].onMouseEvent(event)){
			return;
			}
			}*/
		for (unsigned int i = pieces.size(); i > 0; i--){
			if (pieces[i - 1].onMouseEvent(event)){
				// Set as "on top"
				pieces.push_back(pieces[i - 1]);
				// save top left corner of bounding box
				pieces[i - 1].setPrevTopLeftCorner(rectangles[i - 1].getTopRightCorner());
				pieces.erase(pieces.begin() + (i - 1));
				return;
			}
		}
	}
}

void CheckersApp::mouseUp(MouseEvent event){
	for (unsigned int i = 0; i < pieces.size(); i++){
		if (pieces[i].isSelectedGraphicalObject()){
			pieces[i].setSelectedGraphicalObject(false);
			pieces[i].setInitialMouseLocation(Vec2d(.5, .5));
			closestLegalPosistion(pieces[i]);
		}
	}
}

void CheckersApp::mouseDrag(MouseEvent event){
	for (unsigned int i = 0; i < pieces.size(); i++){
		if (pieces[i].isSelectedGraphicalObject()){
			pieces[i].adjustGraphicalObject(event);
		}
	}
}

void CheckersApp::update()
{
}

void CheckersApp::resize(){
	int resolution = getWindowHeight();
	setWindowSize(resolution, resolution);
	rectangles.erase(rectangles.begin(), rectangles.end());
	constructBoard(resolution, resolution);
}


void CheckersApp::renderScene(cairo::Context &ctx)
{
	//setWindowSize(getWindowPosX() / 2, getWindowPosX());
	ctx.setSourceRgb(0.9, 0.9, 0.9);
	ctx.paint();
	for (Rect rect : rectangles){
		rect.draw(ctx);
	}
	/*for (CheckerPiece pic : pieces){
		pic.draw(ctx);
	}*/
	for (int i = 0; i < pieces.size(); i++){
		pieces[i].draw(ctx);
		if (pieces[i].getStatus()){
			pieces.erase(pieces.begin() + i);
		}
	}
}


void CheckersApp::constructBoard(int width, int height){
	int numberofSquares = 63;
	double steps = floor(width / 8);
	double curX = 0;
	double curY = 0;
	double curHeight = 0;
	double curWidth = 0;
	double curCenterX = 0;
	double curCenterY = 0;
	bool toggleColor = true;
	int newRow = 1;
	for (int i = 0; i <= numberofSquares; i++){
		curCenterX = curWidth + floor(steps / 2);
		curCenterY = curHeight + floor(steps / 2);
		if (toggleColor){
			rectangles.push_back(Rect(steps, steps, 3, Vec2d(curCenterX, curCenterY), Vec2d(curWidth, curHeight), ColorA(CM_HSV, randFloat(), 1, 1, .65)));
			toggleColor = false;
		}
		else{
			rectangles.push_back(Rect(steps, steps, 3, Vec2d(curCenterX, curCenterY), Vec2d(curWidth, curHeight), ColorA(CM_HSV, 1, 0, 0, .65)));
			toggleColor = true;
		}
		newRow++;
		if (newRow == 9){
			newRow = 1;
			curHeight += steps;
			curWidth = -steps;
			toggleColor = !toggleColor;
		}
		curWidth += steps;
	}
}

void CheckersApp::draw()
{
	// clear out the window with black
	cairo::Context ctx(cairo::createWindowSurface());

	renderScene(ctx);
}

CINDER_APP_NATIVE(CheckersApp, Renderer2d)
