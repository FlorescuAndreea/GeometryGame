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

#include "Weapon.h"

class Player {

private:
	float x, y;
	float radius;
	float u;
	Polygon2D *poligon;
	Circle2D *cerc;
	float weaponWidth;
	float speed;
	bool weaponOn;
	float epsilon;

public:
	Weapon *weapon;
	Player(float x, float y);
	~Player();
	void addPlayer(Visual2D *playGround);
	void rotatePlayer(float u);
	void translatePlayer();
	bool isWeaponOn();
	void activateWeapon(Visual2D *playGround);
	void deactivateWeapon(Visual2D *playGround);
};