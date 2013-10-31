#include "Collisions.h"

Collision::Collision(){

}

Collision::~Collision(){

}

vector<Object*> Collision::check(vector<Object*> objects, Player *player, Visual2D *playGround, Stats *stats) {
	cout << "Collision\n";
	if (objects.size() == 0) return objects;
	return weaponVSopponent(player->weapon, objects, playGround, stats);
}

bool oneVSone(Point2D p, pair<Point2D, Point2D> opp) {
	if (p.x >= opp.first.x && p.x <= opp.second.x && // se incadreaza in lungimea dreptunghiului
		p.y >= opp.second.y && p.y <= opp.first.y) { // se incadreaza in latimea dreptunghiului
		
			return true; // exista coliziune
	} 
	return false;
}

vector<Object*> Collision::weaponVSopponent(Weapon *weapon, vector<Object*> objects, Visual2D *playGround, Stats *stats) {
	Point2D p = weapon->getTransPoints();
	cout << "p=" <<p.x << " " << p.y << " " << "obj=" << objects[0]->getTransfPoints().first.x << " "<< objects[0]->getTransfPoints().first.y << " " << objects[0]->getTransfPoints().second.x << " " << objects[0]->getTransfPoints().second.y << "\n";
	for (int i = 0; i < objects.size(); i++) {
		if (oneVSone(p, objects[i]->getTransfPoints())) {
			stats->setScore(stats->getScore() + objects[i]->getPoints());		
			objects[i]->die(playGround);
			delete objects[i];
			objects.erase(objects.begin() + i);
			
		}
	}
	return objects;
}