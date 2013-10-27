#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
#include <iostream>
#include <windows.h>
#include "Player.h"


#define PI 3.14159265358979323846

using namespace std;

Visual2D *playGround;
Visual2D *headsUpDisplay;
Rectangle2D *rect;
Circle2D *cerc;
Polygon2D *poligon;
Color *portocaliu = new Color(1, 0.498039, 0.313725);
Player *player = new Player(100, 100, *portocaliu);	

Text *text;

//functia care permite adaugarea de obiecte
void DrawingWindow::init()
{
	playGround = new Visual2D(0,0,DrawingWindow::width,DrawingWindow::height,0,100,DrawingWindow::width,DrawingWindow::height);  
	addVisual2D(playGround);
	player->addPlayer(playGround);

	headsUpDisplay = new Visual2D(0,0,DrawingWindow::width,DrawingWindow::height,0,0,DrawingWindow::width,100);
	addVisual2D(headsUpDisplay);
	addObject2D_to_Visual2D(new Line2D(Point2D(0, 99), Point2D(DrawingWindow::width,99), Color(1, 0.498039, 0.313725)),headsUpDisplay);
}


//functia care permite animatia
void DrawingWindow::onIdle()
{

}

//functia care se apeleaza la redimensionarea ferestrei
void DrawingWindow::onReshape(int width,int height)
{
	
	playGround->poarta(0,0,width,height); 
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
	DrawingWindow dw(argc, argv, 1000, 600, 0, 0, "Laborator EGC");
	//se apeleaza functia init() - in care s-au adaugat obiecte
	dw.init();
	//se intra in bucla principala de desenare - care face posibila desenarea, animatia si procesarea evenimentelor
	dw.run();
	return 0;

}