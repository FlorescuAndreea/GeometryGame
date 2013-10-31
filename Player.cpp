#include "Player.h"

Player::Player(float x, float y) {

	this->epsilon = 10;

	this->weaponOn = false;
	this->speed = 1;
	this->x = x;
	this->y = y;
	this->radius = 25;
	this->u = 0;
	this->weaponWidth = 90;

	//Add Player
	Color *color = new Color(1, 0.498039, 0.313725);
	Player::poligon = new Polygon2D(Color(1,1,1), false);
	cerc = new Circle2D(Point2D(x, y), this->radius, *color, false);
	poligon->addPoint(Point2D(x-20, y));
	poligon->addPoint(Point2D(x, y + 20));
	poligon->addPoint(Point2D(x + 20, y + 10));
	poligon->addPoint(Point2D(x, y + 17));
	poligon->addPoint(Point2D(x - 10, y));
	poligon->addPoint(Point2D(x, y - 17));
	poligon->addPoint(Point2D(x + 20, y - 10));
	poligon->addPoint(Point2D(x, y - 20));
	//End Player

	//Add Weapon
	weapon = new Weapon(x, y);
	//End Weapon
}

Player::~Player() {
	delete cerc;
	delete poligon;
}

void Player::addPlayer(Visual2D *playGround) {
	DrawingWindow::addObject2D_to_Visual2D(cerc, playGround);
	DrawingWindow::addObject2D_to_Visual2D(poligon, playGround);
}

void Player::rotatePlayer(float u) {

	Transform2D::loadIdentityMatrix();
	Transform2D::translateMatrix(-this->x, -this->y);
	Transform2D::rotateMatrix(u);
	Transform2D::translateMatrix(this->x, this->y);
	Transform2D::applyTransform_o(poligon);
	weapon->rotate(u);
	this->u += u;
}

void Player::activateWeapon(Visual2D *playGround) {
	weaponOn = true;
	speed = 0.2;
	weapon->addWeapon(playGround);
}

void Player::deactivateWeapon(Visual2D *playGround) {
	weaponOn = false;
	speed = 1;
	weapon->removeWeapon(playGround);
}

void Player::translatePlayer() {
	float newX, newY;
	float tx, ty;
	tx = radius*cos(u)*speed;
	ty = radius*sin(u)*speed;
	newX = this->x + tx;
	newY = this->y + ty;
	if(newX + weaponWidth < DrawingWindow::width && newX - weaponWidth> 0 && //x is in window
		newY + weaponWidth < DrawingWindow::height && newY - weaponWidth  - epsilon > 0 //y is in window
	   ) {

		this->x = newX;
		this->y = newY;
		weapon->setCoord(x, y);
		Transform2D::loadIdentityMatrix();
		Transform2D::translateMatrix(tx, ty);
		Transform2D::applyTransform_o(poligon);
		Transform2D::applyTransform_o(cerc);
		weapon->translate(tx, ty);
		weapon->getTransPoints();
	}
}

bool Player::isWeaponOn() {
	return this->weaponOn;
}