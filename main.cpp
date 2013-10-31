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
#include "Collisions.h"

#define PI 3.14159265358979323846

using namespace std;

int clock;

Visual2D *playGround;
Visual2D *headsUpDisplay;

Player *player = new Player(100, 100);	
Opponent1 *o1 = new Opponent1(50, 550);
Opponent3 *o3 = new Opponent3(1200, 50);
Opponent4 *o4 = new Opponent4(1200, 500);
Stats *stats = new Stats();
Collision *collision = new Collision();
vector<Object*> objects;

//functia care permite adaugarea de obiecte
void DrawingWindow::init()
{
	playGround = new Visual2D(0,0,DrawingWindow::width,DrawingWindow::height,
		0,100,DrawingWindow::width,DrawingWindow::height);  
	addVisual2D(playGround);
	playGround->cadruPoarta(Color(0,1,0));
	player->addPlayer(playGround);

	headsUpDisplay = new Visual2D(0,0,DrawingWindow::width,DrawingWindow::height,
		0,0,DrawingWindow::width,100);
	addVisual2D(headsUpDisplay);
	headsUpDisplay->cadruPoarta(Color(1, 0, 0));
	stats->addStats(headsUpDisplay);
	objects.push_back(new Opponent1(50, 550));
	objects[objects.size() - 1]->addOpponent(playGround);
}


//functia care permite animatia
void DrawingWindow::onIdle()
{
	if (clock % 500 == 0) {
		objects.push_back(new Opponent1(50, 550));
		objects[objects.size() - 1]->addOpponent(playGround);
	}
	if (clock % 700 == 0) {
		objects.push_back(new Opponent3(1200, 50));
		objects[objects.size() - 1]->addOpponent(playGround);
	}
	if (clock % 1000 == 0) {
		objects.push_back(new Opponent4(1200, 500));
		objects[objects.size() - 1]->addOpponent(playGround);
		clock = 0;
	}
	objects = collision->check(objects, player, playGround, stats);
	for (int i=0; i < objects.size(); i++) {
		objects[i]->move();
	}
	
	
	clock ++;
}

//functia care se apeleaza la redimensionarea ferestrei
void DrawingWindow::onReshape(int width,int height)
{
	playGround->poarta(0,100,DrawingWindow::width,DrawingWindow::height);
	headsUpDisplay->poarta(0,0,DrawingWindow::width,100);
}

//functia care defineste ce se intampla cand se apasa pe tastatura
void DrawingWindow::onKey(unsigned char key)
{

	switch(key)
	{
		case 27: 
			exit(0);
		case KEY_UP:
			player->translatePlayer();
			break;
		case KEY_SPACE:
			if (player->isWeaponOn()) {
				player->deactivateWeapon(playGround);
			} else {
				player->activateWeapon(playGround);
			}
			break;
		case KEY_RIGHT:
			player->rotatePlayer(0.1);
			break;
		case KEY_LEFT:
			player->rotatePlayer(-0.1);
			break;
	}
}

//functia care defineste ce se intampla cand se da click pe mouse
void DrawingWindow::onMouse(int button,int state,int x, int y)
{
	
}


int main(int argc, char** argv)
{
	//creare fereastra
	DrawingWindow dw(argc, argv, 1300, 700, 0, 0, "Geometry Wars");
	//se apeleaza functia init() - in care s-au adaugat obiecte
	dw.init();
	//se intra in bucla principala de desenare - care face posibila desenarea, animatia si procesarea evenimentelor
	dw.run();
	return 0;

}