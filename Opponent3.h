#include "Object.h"

class Opponent3 : Object {
private:
	float l; // latura triunghiului
	float u; // unghiul sub care s-a produs rotatia
	float r; // raza cercului interior
	float points; // numarul de puncte pe care il castiga jucatorul
	pair<float, float> dir; //directia in care se misca Oponentul
	float speed;

	// Componentele vizuale ale Oponentului
	Circle2D *cerc;
	Polygon2D *t1;
	Polygon2D *t2;
	Polygon2D *t3;
	Polygon2D *t4;

	// Alege o noua directie random pentru deplasarea oponentului
	pair<float, float> chooseDirection();
	// determina daca noua pozitie a oponentului este in playGround 
	bool isOutOfBox(float newX, float newY); 
public:
	Opponent3(float x, float y);
	~Opponent3();

	void addOpponent(Visual2D *playGround);
	void rotateOpponent(float u);
	void translateOpponent();
	void move();
	float getPoints();
};