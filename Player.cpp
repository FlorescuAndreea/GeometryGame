#include "Player.h"

Player::Player(float x, float y) {

	this->epsilon = 30;

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
	weapon = new Polygon2D(*color, true);
	weapon->addPoint(Point2D(this->x + 30, this->y + 15));
	weapon->addPoint(Point2D(this->x + 90, this->y));
	weapon->addPoint(Point2D(this->x + 30, this->y - 15));
	//End Weapon
}

Player::~Player() {
	
}

void Player::addPlayer(Visual2D *playGround) {
	DrawingWindow::addObject2D_to_Visual2D(cerc, playGround);
	DrawingWindow::addObject2D_to_Visual2D(poligon, playGround);
}

void Player::rotatePlayer(float u) {

	this->u += u;

	Transform2D::loadIdentityMatrix();
	Transform2D::translateMatrix(-this->x, -this->y);
	Transform2D::rotateMatrix(u);
	Transform2D::translateMatrix(this->x, this->y);
	Transform2D::applyTransform_o(poligon);
	Transform2D::applyTransform_o(weapon);
}

void Player::activateWeapon(Visual2D *playGround) {
	weaponOn = true;
	speed = 0.2;
	DrawingWindow::addObject2D_to_Visual2D(weapon, playGround);
}

void Player::deactivateWeapon(Visual2D *playGround) {
	weaponOn = false;
	speed = 1;
	DrawingWindow::removeObject2D_from_Visual2D(weapon, playGround);
}

void Player::translatePlayer() {
	float newX, newY;
	newX = this->x + radius*cos(u)*speed;
	newY = this->y + radius*sin(u)*speed;

	if(newX + weaponWidth < DrawingWindow::width && newX - weaponWidth > 0 && //x is in window
		newY + weaponWidth + 100 - epsilon < DrawingWindow::height && newY - weaponWidth > 0 //y is in window
	   ) {

		this->x = newX;
		this->y = newY;
		Transform2D::loadIdentityMatrix();
		Transform2D::translateMatrix(radius*cos(u)*speed, radius* sin(u)*speed);
		Transform2D::applyTransform_o(poligon);
		Transform2D::applyTransform_o(cerc);
		Transform2D::applyTransform_o(weapon);
	}
	cout << y << "\n";
}

bool Player::isWeaponOn() {
	return this->weaponOn;
}