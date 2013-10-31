#pragma once
#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
#include <iostream>
#include <windows.h>

class Object {

public:
	float x, y;
	pair<float, float> dir;
	Object();
	Object(float x, float y) {
		this->x = x;
		this->y = y;
	}

	pair<float, float> getCoordinates() {
		pair<float, float> coord;
		coord.first = x;
		coord.second = y;
		return coord;
	}

	void chooseDirection() {
		dir.first = rand()%3 - 1;
		dir.second = rand()%3 - 1;
	}

	virtual void move() {}
	virtual float getPoints() { return 0;}
	virtual void addOpponent(Visual2D *playground) {}
	virtual pair<Point2D, Point2D> getTransfPoints() { return pair<Point2D, Point2D>();}
	virtual void die(Visual2D *playGround) {}
};
