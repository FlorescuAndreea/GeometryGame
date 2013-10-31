#pragma once
#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
#include <iostream>
#include <windows.h>

class Stats {
private:
	Polygon2D *life1, *life2, *life3;
	Text *life;
	Text *name;
	Text *score;
	Text *score_num;

	string *score_text;
	int nrOfLifes;
	int currenLife;
	int score_nr;
public:
	Stats() {
		nrOfLifes = 3;
		currenLife = 3;
		score_nr = 0;
		score_text = new string("0");
		
		life = new Text("Health",Point2D(50, 400),Color(0.8, 0, 0), BITMAP_HELVETICA_18);
		name = new Text("GEOMETRY WAR", Point2D(600, 300), Color(0.8, 0, 0), BITMAP_HELVETICA_18);
		score = new Text("SCORE", Point2D(1100, 400), Color(0.8, 0, 0), BITMAP_HELVETICA_18);
		score_num = new Text(*score_text, Point2D(1105, 200), Color(0.8, 0, 0), BITMAP_HELVETICA_18);
		life1 = new Polygon2D(Color(1, 0, 0), false);
		life2 = new Polygon2D(Color(1, 0, 0), false);
		life3 = new Polygon2D(Color(1, 0, 0), false);

		int x = 50;
		int y = 200;

		life1->addPoint(Point2D(x, y));
		life1->addPoint(Point2D(x-10, y+50));
		life1->addPoint(Point2D(x-20, y));
		life1->addPoint(Point2D(x, y-100));
		life1->addPoint(Point2D(x+20, y));
		life1->addPoint(Point2D(x+10, y + 50));

		x += 50;
		life2->addPoint(Point2D(x, y));
		life2->addPoint(Point2D(x-10, y+50));
		life2->addPoint(Point2D(x-20, y));
		life2->addPoint(Point2D(x, y-100));
		life2->addPoint(Point2D(x+20, y));
		life2->addPoint(Point2D(x+10, y + 50));

		x+=50;
		life3->addPoint(Point2D(x, y));
		life3->addPoint(Point2D(x-10, y+50));
		life3->addPoint(Point2D(x-20, y));
		life3->addPoint(Point2D(x, y-100));
		life3->addPoint(Point2D(x+20, y));
		life3->addPoint(Point2D(x+10, y + 50));
	}

	~Stats(){

	}
	void addStats(Visual2D *HUD) {
		DrawingWindow::addObject2D_to_Visual2D(life1, HUD);
		DrawingWindow::addObject2D_to_Visual2D(life2, HUD);
		DrawingWindow::addObject2D_to_Visual2D(life3, HUD);
		DrawingWindow::addText_to_Visual2D(life, HUD);
		DrawingWindow::addText_to_Visual2D(name, HUD);
		DrawingWindow::addText_to_Visual2D(score, HUD);
		DrawingWindow::addText_to_Visual2D(score_num, HUD);
	}

	int getNrOfLifes() {
		return nrOfLifes;
	}

	int getScore() {
		return score_nr;
	}

	void setScore(int s) {
		score_nr = s;
		score_num->text = to_string(s);
	}

};