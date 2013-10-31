#include "Opponent1.h"

Opponent1::Opponent1(float x, float y) : Object(x, y) {
	Color *color = new Color(0, 0.807843, 0.819608); 
	this->clock = 0;
	this->x = x;
	this->y = y;
	this->l = 20;
	this->u = 0;
	this->points = 10;
	this->speed = 0.02;


	this->dir.first = 1;
	this->dir.second = 0;
	
	Opponent1::r1 = new Rectangle2D(Point2D(x, y), l, l, *color, false);
	Opponent1::r2 = new Rectangle2D(Point2D(x + l/2, y - l/2), l, l, *color, false);
	Opponent1::rm = new Rectangle2D(Point2D(x + l/2, y), l/2, l/2, *color, true);
}

Opponent1::~Opponent1() {
	delete r1;
	delete r2;
	delete rm;
}

void Opponent1::addOpponent(Visual2D *playGround) {
	DrawingWindow::addObject2D_to_Visual2D(r1, playGround);
	DrawingWindow::addObject2D_to_Visual2D(r2, playGround);
	DrawingWindow::addObject2D_to_Visual2D(rm, playGround);
}

void Opponent1::removeOpponent(Visual2D *playGround) {
	DrawingWindow::removeObject2D_from_Visual2D(r1, playGround);
	DrawingWindow::removeObject2D_from_Visual2D(r2, playGround);
	DrawingWindow::removeObject2D_from_Visual2D(rm, playGround);
}

float Opponent1::getPoints() {
	return this->points;
}

void Opponent1::move() {
	
	if (clock == 100) {
		chooseDirection();
		clock = 0;
	}
	translateOpponent();
	clock ++;
}

void Opponent1::rotateOpponent(float u) {
	this->u = u;
	Transform2D::loadIdentityMatrix();
	Transform2D::translateMatrix(-this->x, -this->y);
	Transform2D::rotateMatrix(u);
	Transform2D::translateMatrix(this->x, this->y);
	Transform2D::applyTransform_o(r1);
	Transform2D::applyTransform_o(r2);
	Transform2D::applyTransform_o(rm);
}

void Opponent1::translateOpponent() {
	float newX, newY;
	float tx, ty;
	
	tx = this->l * speed;
	ty = this->l * speed;
	newX = this->x + tx;
	newY = this->y + ty;

	//daca oponentul iese din suprafata de joc i se inverseaza directia
	if (isOutOfBox(newX, newY)) {
		dir.first = -dir.first;
		dir.second = -dir.second;
	} 
		
	Transform2D::loadIdentityMatrix();
	Transform2D::translateMatrix(l * speed * dir.first, l * speed * dir.second);
	Transform2D::applyTransform_o(r1);
	Transform2D::applyTransform_o(r2);
	Transform2D::applyTransform_o(rm);

	this->x += l * speed * dir.first;
	this->y += l * speed * dir.second;
}

//metoda care verifica daca oponentul iese din suprafata de joc
bool Opponent1::isOutOfBox(float newX, float newY) {
	float epsilon = 30;
	return
		newX + this->l * 2 + epsilon > DrawingWindow::width || newX  - epsilon < 0 || //x is in window
		newY + this->l/2 + 100 + epsilon > DrawingWindow::height || newY - (this->l/2 + epsilon) < 0; //y is in window
}

pair<Point2D, Point2D> Opponent1::getTransfPoints() {
	// r1->transf_points[0] -> extrema stanga a dreptunghiului imaginar
	// r2->transf_points[2] -> extrema dreapta a dreptunghiului imaginar
	vector<Point2D*> aux; // retine toate punctele din obiectele componente
	aux = r1->transf_points;
	aux.insert(aux.end(), r2->transf_points.begin(), r2->transf_points.end());
	
	float maxX = 0, maxY = 0, minX = DrawingWindow::width, minY = DrawingWindow::height;
	for (int i = 0; i < aux.size(); i++) {
		if (aux[i]->x > maxX) {
			maxX = aux[i]->x;
		}
		
		if (aux[i]->x < minX) {
			minX = aux[i]->x;
		}

		if(aux[i]->y > maxY) {
			maxY = aux[i]->y;	
		}

		if(aux[i]->y < minY) {
			minY = aux[i]->y;
		}
	}
	// pentru dreptunghiul imaginar se folosesc doua puncte:
	// P1(minX, maxY), P2(maxX, minY)
	return make_pair(Point2D(minX, maxY), Point2D(maxX, minY));
}

void Opponent1::die(Visual2D *playGround) {
	this->removeOpponent(playGround);
}