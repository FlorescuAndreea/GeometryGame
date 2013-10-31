#include "Opponent4.h"

Opponent4::Opponent4(float x, float y) : Object(x, y) {
	this->x = x;
	this->y = y;
	this->l = 30;
	
	this->scale = 0;
	this->scaleFactor = 1.3;
	this->points = 40;
	this->clock = 0;

	this->speed = 0.03;
	this->dir.first = -1;
	this->dir.second = 0;

	Color *color = new Color(0, 1, 0);
	
	romb = new Polygon2D(*color, true);
	romb->addPoint(Point2D(x+l/2, y));
	romb->addPoint(Point2D(x+l, y+l/2));
	romb->addPoint(Point2D(x+l/2, y+l));
	romb->addPoint(Point2D(x, y+l/2));
}

Opponent4::~Opponent4() {
	delete romb;
}

void Opponent4::addOpponent(Visual2D *playGround) {
	DrawingWindow::addObject2D_to_Visual2D(romb, playGround);
}

void Opponent4::removeOpponent(Visual2D *playGround) {
	DrawingWindow::removeObject2D_from_Visual2D(romb, playGround);
}

float Opponent4::getPoints() {
	return this->points;
}

bool Opponent4::isOutOfBox(float newX, float newY) {
	float epsilon = 30;
	return
		newX + this->l + epsilon > DrawingWindow::width || newX  - epsilon < 0 || //x is in window
		newY + this->l + 100 + epsilon > DrawingWindow::height || newY - (this->l + epsilon) < 0; //y is in window
}

void Opponent4::translateOpponent() {
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
	Transform2D::applyTransform_o(romb);

	this->x += l * speed * dir.first;
	this->y += l * speed * dir.second;
}

void Opponent4::move() {
	if(this->clock % 50 == 0) {
		Transform2D::loadIdentityMatrix();
		Transform2D::translateMatrix(-x, -y);
		switch(scale) {
			case 0:
				Transform2D::scaleMatrix(1, scaleFactor); //scalarea coordonatei y
				break;
			case 1:
				Transform2D::scaleMatrix(1, 1/scaleFactor); //revenire la dim initiala
				break;
			case 2:
				Transform2D::scaleMatrix(scaleFactor, 1); //scalarea coordonatei x
				break;
			case 3:
				Transform2D::scaleMatrix(1/scaleFactor, 1); //revenire la dim initiala
		}
		scale = (scale + 1) % 4;
		Transform2D::translateMatrix(x, y);
		Transform2D::applyTransform_o(this->romb);
	} else {
		translateOpponent();
		
		if(clock == 501) {
			clock = 0;
			this->chooseDirection();
		}
	}
	clock ++;
}

pair<Point2D, Point2D> Opponent4::getTransfPoints(){
	vector<Point2D*> aux; // retine toate punctele din obiectele componente
	aux = romb->transf_points;

	// pentru dreptunghiul imaginar se folosesc doua puncte:
	// P1(minX, maxY), P2(maxX, minY)
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

	return make_pair(Point2D(minX, maxY), Point2D(maxX, minY));
}

void Opponent4::die(Visual2D *playGround) {
	this->removeOpponent(playGround);
}