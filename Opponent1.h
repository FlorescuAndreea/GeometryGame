#pragma once
#include "Object.h"

class Opponent1 :public Object {
private:
	float l, u;
	Rectangle2D *r1;
	Rectangle2D *r2;
	Rectangle2D *rm;
	float points;
	float speed;
	int clock;

public:
	Opponent1(float x, float y);
	~Opponent1();
	void addOpponent(Visual2D *playGround);
	void removeOpponent(Visual2D *playGround);
	void rotateOpponent(float u);
	void translateOpponent();
	float getPoints();
	void move();
	bool isOutOfBox(float newX, float newY);
	pair<Point2D, Point2D> getTransfPoints();
	void die(Visual2D *playGround);
};