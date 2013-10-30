#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
#include <iostream>
#include <windows.h>

class Opponent2 {
public:
	private:
	float x, y, l;
	Rectangle2D *r1, *r2, *r3, *r4, *r1ext, *r2ext, *r3ext, *r4ext;
	float points;
	bool big;
public:
	Opponent2(float x, float y);
	~Opponent2();
	void addOpponent(Visual2D *playGround);
	void rotateOpponent(float u);
	void translateOpponent();
	float getPoints();
	void move();
};