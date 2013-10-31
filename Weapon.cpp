#include "Weapon.h"

Weapon::Weapon(float x, float y) {
	Color *color = new Color(1, 0.498039, 0.313725);
	this->x = x;
	this->y = y;
	this->u = 0;
	this->weaponWidth = 60;
	weapon = new Polygon2D(*color, true);
	weapon->addPoint(Point2D(this->x + 30, this->y + 15));
	weapon->addPoint(Point2D(this->x + 90, this->y));
	weapon->addPoint(Point2D(this->x + 30, this->y - 15));
}
Weapon::~Weapon(){
	delete weapon;
}

void Weapon::setCoord(float x, float y){
	this->x = x;
	this->y = y;
}

pair<float, float> Weapon::getCoord(){
	pair<float, float> coord;
	coord.first = x;
	coord.second = y;
	return coord;
}

void Weapon::translate(float tx, float ty) {
	Transform2D::loadIdentityMatrix();
	Transform2D::translateMatrix(tx, ty);
	Transform2D::applyTransform_o(weapon);
}

void Weapon::rotate(float u) {
	this->u += u;
	Transform2D::loadIdentityMatrix();
	Transform2D::translateMatrix(-this->x, -this->y);
	Transform2D::rotateMatrix(u);
	Transform2D::translateMatrix(this->x, this->y);
	Transform2D::applyTransform_o(weapon);
}

void Weapon::addWeapon(Visual2D *playGround) {
	DrawingWindow::addObject2D_to_Visual2D(weapon, playGround);
}

void Weapon::removeWeapon(Visual2D *playGround) {
	DrawingWindow::removeObject2D_from_Visual2D(weapon, playGround);
}

Point2D Weapon::getTransPoints() {
	vector<Point2D*> pt;
	pt = weapon->transf_points;
	return *pt[1];
}

