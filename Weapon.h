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

class Weapon {
private:
	float x, y;
	float u;
	bool weaponOn;
	float weaponWidth;
	Polygon2D *weapon;
public:
	Weapon(float x, float y);
	~Weapon();

	void setCoord(float x, float y);
	pair<float, float> getCoord();
	float getWeaponWidth();
	void addWeapon(Visual2D *playGround);
	void removeWeapon(Visual2D *playGround);
	void translate(float tx, float ty);
	void rotate(float u);
	//presupun ca jucatorul poate omori un inamic numai cu varful armei
	Point2D getTransPoints(); 
};
