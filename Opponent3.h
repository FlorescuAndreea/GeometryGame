#pragma once
#include "Object.h"

class Opponent3 : public Object {
private:
	float l; // latura triunghiului
	float u; // unghiul sub care s-a produs rotatia
	float r; // raza cercului interior
	float points; // numarul de puncte pe care il castiga jucatorul
	float speed;

	// Componentele vizuale ale Oponentului
	Circle2D *cerc;
	Polygon2D *t1;
	Polygon2D *t2;
	Polygon2D *t3;
	Polygon2D *t4;

	// determina daca noua pozitie a oponentului este in playGround 
	bool isOutOfBox(float newX, float newY); 
public:
	Opponent3(float x, float y);
	~Opponent3();

	void addOpponent(Visual2D *playGround);
	void removeOpponent(Visual2D *playGround);
	void rotateOpponent(float u);
	void translateOpponent();
	void move();
	float getPoints();
	pair<Point2D, Point2D> getTransfPoints();
	void die(Visual2D *playGround);
};