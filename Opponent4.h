#pragma once
#include "Object.h"

using namespace std;

class Opponent4 : public Object{
private:
	float l;
	Rectangle2D *r1;
	Rectangle2D *r2;
	float points;
	int scale; //variabila care determina tipul scalarii (pe x, pe y, niciuna)
	float scaleFactor; // numarul cu care se realizeaza scalarea
	int clock;
	float speed;

	Polygon2D *romb;
public:
	Opponent4(float x, float y);
	~Opponent4();
	void addOpponent(Visual2D *playGround);
	void removeOpponent(Visual2D *playGround);
	void rotateOpponent(float u);
	void translateOpponent();
	void scaleOpponent();
	void move();
	float getPoints();
	bool isOutOfBox(float newX, float newY);
	pair<Point2D, Point2D> getTransfPoints();
	void die(Visual2D *playGround);
};