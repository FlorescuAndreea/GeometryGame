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
	Object(float x, float y) {
		this->x = x;
		this->y = y;
	}

	void move() {
	//implementare in clase mai specifice
	}
	pair<float, float> getCoordinates() {
		pair<float, float> coord;
		coord.first = x;
		coord.second = y;
		return coord;
	}
};
