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
	this->points = 30;
	Color *colorC = new Color(0.780392, 0.0823529, 0.52156);
	Color *color = new Color(1, 1, 0.878431);
	cerc = new Circle2D(Point2D(x, y), r, *color, true);
	
	t1 = new Polygon2D(*colorC, true);
	t1->addPoint(Point2D(x+r, y));
	t1->addPoint(Point2D(x+r+l, y));
	t1->addPoint(Point2D(x+r+l, y-l));

	t2 = new Polygon2D(*color, true);
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
	delete t1;
	delete t2;
	delete t3;
	delete t4;
}

void Opponent3::addOpponent(Visual2D *playGround) {
	DrawingWindow::addObject2D_to_Visual2D(cerc, playGround);
	DrawingWindow::addObject2D_to_Visual2D(t1, playGround);
	DrawingWindow::addObject2D_to_Visual2D(t2, playGround);
	DrawingWindow::addObject2D_to_Visual2D(t3, playGround);
	DrawingWindow::addObject2D_to_Visual2D(t4, playGround);
}

void Opponent3::removeOpponent(Visual2D *playGround) {
	DrawingWindow::removeObject2D_from_Visual2D(cerc, playGround);
	DrawingWindow::removeObject2D_from_Visual2D(t1, playGround);
	DrawingWindow::removeObject2D_from_Visual2D(t2, playGround);
	DrawingWindow::removeObject2D_from_Visual2D(t3, playGround);
	DrawingWindow::removeObject2D_from_Visual2D(t4, playGround);
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
		this->chooseDirection();
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


bool Opponent3::isOutOfBox(float newX, float newY) {
	float epsilon = 30;
	return
		!(newX + this->r + this->l + epsilon < DrawingWindow::width && newX - this->r - this->l - epsilon > 0 && //x is in window
		newY + this->r + this->l + 100 + epsilon < DrawingWindow::height && newY - (this->r + this->l + epsilon) > 0); //y is in window
}

float Opponent3::getPoints() {
	return this->points;
}

pair<Point2D, Point2D> Opponent3::getTransfPoints() {
	vector<Point2D*> aux; // retine toate punctele din obiectele componente
	aux = t1->transf_points;
	aux.insert(aux.end(), t2->transf_points.begin(), t2->transf_points.end());
	aux.insert(aux.end(), t3->transf_points.begin(), t3->transf_points.end());
	aux.insert(aux.end(), t4->transf_points.begin(), t4->transf_points.end());
	cout << "len=" << aux.size() << "\n";
	
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

void Opponent3::die(Visual2D *playGround) {
	this->removeOpponent(playGround);
}