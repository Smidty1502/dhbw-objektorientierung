#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <Windows.h>

#include "Figur.h"
#include "Spieler.h"
#include "Vektor2d.h"
#include "Gelaende.h"

// Simulationsgeschwindigkeit
const double DT = 100.0;
int x = 0;
int y = 0;
bool jmp = false;

//Auflösung
const int  fbreite = 1280;
const int  fhoehe = 720;
const int bodenEbene = 150;

Vektor2d triangleFuss(0, 570);
Vektor2d triangleHitbox(50, 570);
Spieler testTriangle(triangleFuss, 100, triangleHitbox, 50);

Vektor2d boden1Vec(50, 500);
Gelaende boden1(boden1Vec, 100);
Vektor2d boden2Vec(200, 480);
Gelaende boden2(boden2Vec, 100);
Vektor2d boden3Vec(350, 440);
Gelaende boden3(boden3Vec, 100);
Vektor2d boden4Vec(210, 390);
Gelaende boden4(boden4Vec, 100);
vector<Gelaende> Lvl1bodenVec{ boden1, boden2, boden3 ,boden4};

class GameWindow : public Gosu::Window
{
	std::unique_ptr<Gosu::Image> background_image;

public:
	Gosu::Image bild;
	GameWindow() 
		: Window(fbreite, fhoehe)
		
	{
		set_caption("Bestes Game ever!!!");

		background_image.reset(new Gosu::Image("HintergrundGameTest.png", Gosu::IF_TILEABLE));		//Hintergrund
	}

	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override
	{
		background_image->draw(0, 0, 0);

		graphics().draw_triangle(
			double(testTriangle.fussLinks.get_x()) + 50, double(testTriangle.hitboxVec.at(testTriangle.hoehe - 1).get_y()), Gosu::Color::GREEN,		// Spitze oben
			//50 + x, (fhoehe - bodenEbene) - 50 + y, Gosu::Color::GREEN,
			double(testTriangle.fussRechts.get_x()), double(testTriangle.fussRechts.get_y()), Gosu::Color::GREEN,		//Spitze rechts
			//100 + x, (fhoehe - bodenEbene) + y, Gosu::Color::GREEN,
			double(testTriangle.fussLinks.get_x()), double(testTriangle.fussLinks.get_y()), Gosu::Color::GREEN,
			//0 + x, (fhoehe - bodenEbene) + y, Gosu::Color::GREEN,
			0.0
		);

		graphics().draw_line(
			0.0, (fhoehe - bodenEbene), Gosu::Color::WHITE,
			fbreite, (fhoehe - bodenEbene), Gosu::Color::WHITE,
			0.0
		);
		for(Gelaende elem: Lvl1bodenVec)
		{
			graphics().draw_line(
				elem.left.get_x(), elem.left.get_y(), Gosu::Color::WHITE,
				elem.right.get_x(), elem.right.get_y(), Gosu::Color::WHITE,
				0.0);
		}
	}

	int ctr = 0;
	void ask_KB_W()		//Tastaturabfrage für W
	{
		if (input().down(Gosu::KB_W))
		{
			ctr++;
		} else
		{
			ctr = 0;
		}
		
		if (input().down(Gosu::KB_W) && testTriangle.fussLinks.get_y() >= (-100 + testTriangle.ground) || ctr <= 20) //W gedrückt und Sprunghöhe über ground nicht erreicht
		{	
			cout << "w Taste" << endl;
			if((testTriangle.fussLinks.get_y() <= -100 + testTriangle.ground) )
			{
				jmp = true;
				cout << "oben angekommen" << endl;
			}
			if(jmp == false)	//Wenn nicht schon gesprungen
			{
				testTriangle.hitboxVec.at(testTriangle.hoehe - 1).add_y(-5);
				testTriangle.fussLinks.add_y(-5);
				testTriangle.fussRechts.add_y(-5);		//Sprung
				cout << "springe" << endl;
			}
		}
		if((!input().down(Gosu::KB_W) && testTriangle.fussLinks.get_y() < (testTriangle.ground)) || jmp)	//W nicht gedrückt oder Sprung durchgeführt
		{

			cout << "Sprung aufhoeren" << endl;
			testTriangle.hitboxVec.at(testTriangle.hoehe - 1).add_y(5);
			testTriangle.fussLinks.add_y(5);
			testTriangle.fussRechts.add_y(5);		//Fallen
			jmp = true;

			if( testTriangle.fussLinks.get_y() >= 0 + testTriangle.ground)
			{
				jmp = false;
				cout << "jmp false" << endl;
			}
		}
	}
	void ask_boden()
	{
		for (Gelaende elem : Lvl1bodenVec)
		{
			if (testTriangle.fussLinks.get_y() <= elem.left.get_y()) // dreieck ueber Ebene 
			{
				cout << "ueber Ebene, pruefe X" << endl;
				ctr = 0;
				if (((testTriangle.fussLinks.get_x() <= elem.right.get_x()) && (testTriangle.fussLinks.get_x() >= elem.left.get_x()))
					|| ((testTriangle.fussRechts.get_x() <= elem.right.get_x()) && (testTriangle.fussRechts.get_x() >= elem.left.get_x())))
				{
					cout << "ueber und zwischen Ebene!" << endl;
					if (jmp)
					{
						cout << "neue Ebene! : " << elem.height << endl;
						testTriangle.ground = elem.height;
					}
				}
				else
				{
					if (testTriangle.ground == elem.height)
					{
						testTriangle.ground = 570;
						cout << "ground wird zurueck gesetzt" << endl;
					}
					cout << "ausserhalb if" << endl;
				}
			}
		}
	}

	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		//Dreieck mit Bewegung
		if (input().down(Gosu::KB_D) && x <= (fbreite -100))
		{
			testTriangle.fussLinks.add_x(5);
			testTriangle.fussRechts.add_x(5);
		}
		if (input().down(Gosu::KB_A) && x >= 0)
		{
			testTriangle.fussLinks.add_x(-5);
			testTriangle.fussRechts.add_x(-5);
		}
		if (jmp || !input().down(Gosu::KB_W))
		{
			ask_boden();
		}
		ask_KB_W();
	}
};

// C++ Hauptprogramm
int main()
{
	GameWindow window;
	window.show();
}
