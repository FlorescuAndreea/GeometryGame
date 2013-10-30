#include "Opponent3.h"

Opponent3::Opponent3(float x, float y) : Object(x, y) {
	this->x = x;
	this->y = y;
	this->l = 15;
	this->u = 0;
	this->r = 3;
	this->dir.first = -1;
	this->dir.second = 1;
	this->speed = 0.05;
	Color *colorC = new Color(0.780392, 0.0823529, 0.52156);
	Color *color = new Color(1, 1, 0.878431);
	cerc = new Circle2D(Point2D(x, y), r, *color, true);
	
	t1 = new Polygon2D(*colorC, true);
	t1->addPoint(Point2D(x+r, y));
	t1->addPoint(Point2D(x+r+l, y));
	t1->addPoint(Point2D(x+r+l, y-l));

	t2 = new Polygon2D(*color, false);
	t2->addPoint(Point2D(x, y-r));
	t2->addPoint(Point2D(x, y-r-l));
	t2->addPoint(Point2D(x-l, y-r-l));

	t3 = new Polygon2D(*colorC, true);
	t3->addPoint(Point2D(x-r, y));
	t3->addPoint(Point2D(x-r-l, y));
	t3->addPoint(Point2D(x-r-l, y+l));

	t4 = new Polygon2D(*color, false);
	t4->addPoint(Point2D(x, y+r));
	t4->addPoint(Point2D(x, y+r+l));
	t4->addPoint(Point2D(x+l, y+r+l));

}

Opponent3::~Opponent3() {

}

void Opponent3::addOpponent(Visual2D *playGround) {
	DrawingWindow::addObject2D_to_Visual2D(cerc, playGround);
	DrawingWindow::addObject2D_to_Visual2D(t1, playGround);
	DrawingWindow::addObject2D_to_Visual2D(t2, playGround);
	DrawingWindow::addObject2D_to_Visual2D(t3, playGround);
	DrawingWindow::addObject2D_to_Visual2D(t4, playGround);
}

void Opponent3::rotateOpponent(float u) {
	//Se actualizeaza valoare lui u
	this->u += u;

	Transform2D::loadIdentityMatrix();
	Transform2D::translateMatrix(-this->x, -this->y);
	Transform2D::rotateMatrix(u);
	Transform2D::translateMatrix(this->x, this->y);
}

void Opponent3::translateOpponent() {
	float tx, ty;
	float newX, newY;
	tx = this->l * speed * dir.first;
	ty = this->l * speed * dir.second;
	newX = x+tx;
	newY = y+ty;
	if(isOutOfBox(newX, newY)) {
		this->dir = this->chooseDirection();
	}

	Transform2D::translateMatrix(tx, ty);
	Transform2D::applyTransform_o(cerc);
	Transform2D::applyTransform_o(t1);
	Transform2D::applyTransform_o(t2);
	Transform2D::applyTransform_o(t3);
	Transform2D::applyTransform_o(t4);
	
	this->x += tx;
	this->y += ty;

}

void Opponent3::move () {
	rotateOpponent(0.05);
	translateOpponent();
}

pair<float, float> Opponent3::chooseDirection() {
	pair<float, float> newDir;
	newDir.first = rand()%3 - 1;
	newDir.second = rand()%3 - 1;
	return newDir;
}

bool Opponent3::isOutOfBox(float newX, float newY) {
	float epsilon = 30;
	return
		!(newX + this->r + this->l + epsilon < DrawingWindow::width && newX - this->r - this->l - epsilon > 0 && //x is in window
		newY + this->r + this->l + 100 + epsilon < DrawingWindow::height && newY - (this->r + this->l + epsilon) > 0); //y is in window
}