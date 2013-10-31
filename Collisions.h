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
#include <vector>

#include "Player.h"

#include "Object.h"
#include "Opponent1.h"
#include "Opponent3.h"
#include "Opponent4.h"
#include "Weapon.h"
#include "Stats.h"

class Collision {
	
private:
	vector<Object*> playerVSopponent(Player player, vector<Object*> objects, Visual2D *playGround, Stats *stats);
	vector<Object*> weaponVSopponent(Weapon *weapon, vector<Object*> objects, Visual2D *playGround, Stats *stats);
	vector<Object*> opponentVSopponent(vector<Object*> objects, Visual2D *playGround, Stats *stats);
public:
	Collision();
	~Collision();
	vector<Object*> check(vector<Object*> objects, Player *player, Visual2D *playGround, Stats *stats);

};