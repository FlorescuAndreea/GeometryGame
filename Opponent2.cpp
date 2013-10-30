#include "Opponent2.h"
#include <math.h>

Opponent2::Opponent2(float x, float y){
	
	Color *albastru = new Color(0.117647, 0.564706, 1);
	Color *bleumarin = new Color(0, 0.74902, 1);
	
	this->big = false;
	this->x = x;
	this->y = y;
	this->l = 15;
	this->points = 20;

	r1 = new Rectangle2D(Point2D(x, y), l, l, *albastru, true);
	r1ext = new Rectangle2D(Point2D(x, y), l, l, *bleumarin, false);

	r2 = new Rectangle2D(Point2D(x + l, y), l, l, *albastru, true);
	r2ext = new Rectangle2D(Point2D(x + l, y), l, l, *bleumarin, false);

	r3 = new Rectangle2D(Point2D(x + 2 * l, y), l, l, *albastru, true);
	r3ext = new Rectangle2D(Point2D(x + 2 * l, y), l, l, *bleumarin, false);

	r4 = new Rectangle2D(Point2D(x, y - l), l, l, *albastru, true);
	r4ext = new Rectangle2D(Point2D(x, y - l), l, l, *bleumarin, false);
}

Opponent2::~Opponent2() {

}

void Opponent2::addOpponent(Visual2D *playGround) {
	DrawingWindow::addObject2D_to_Visual2D(r1, playGround);
	DrawingWindow::addObject2D_to_Visual2D(r1ext, playGround);
	DrawingWindow::addObject2D_to_Visual2D(r2, playGround);
	DrawingWindow::addObject2D_to_Visual2D(r2ext, playGround);
	DrawingWindow::addObject2D_to_Visual2D(r3, playGround);
	DrawingWindow::addObject2D_to_Visual2D(r3ext, playGround);
	DrawingWindow::addObject2D_to_Visual2D(r4, playGround);
	DrawingWindow::addObject2D_to_Visual2D(r4ext, playGround);
}

float Opponent2::getPoints() {
	return this->points;
}

void Opponent2::rotateOpponent(float u) {
	x = x * cos(u);
	x = y * sin(u);
	Transform2D::loadIdentityMatrix();
	Transform2D::rotateMatrix(u);
	Transform2D::applyTransform_o(r1);
	Transform2D::applyTransform_o(r1ext);
	Transform2D::applyTransform_o(r2);
	Transform2D::applyTransform_o(r2ext);
	Transform2D::applyTransform_o(r3);
	Transform2D::applyTransform_o(r3ext);
	Transform2D::applyTransform_o(r4);
	Transform2D::applyTransform_o(r4ext);
}
void Opponent2::translateOpponent() {
	Transform2D::loadIdentityMatrix();
}
void Opponent2::move() {
	if(rand()%2 == 0) {
		rotateOpponent(0.01);
	} else {
		rotateOpponent(-0.01);
	}
}
