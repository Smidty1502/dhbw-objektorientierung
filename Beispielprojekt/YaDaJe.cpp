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
const int  fbreite = 1920;
const int  fhoehe = 1080;
const int bodenEbene = 936;

Vektor2d triangleFuss(20, bodenEbene);
Vektor2d triangleHitbox(50, bodenEbene);
Spieler Player1(triangleFuss, 16, triangleHitbox, 41);


Vektor2d MarioBodenvec(0, 935);
Gelaende MarioBoden(MarioBodenvec, 1920);
Vektor2d Mario1vec(1056, 840);
Gelaende Mario1(Mario1vec, 95); 
Vektor2d Mario1bvec(1056, 800);
Gelaende Mario1b(Mario1bvec, 95);
Vektor2d Mario2vec(1536, 792);
Gelaende Mario2(Mario2vec, 95);
Vektor2d Mario3vec(985, 877);
Gelaende Mario3(Mario3vec, 1016-985);
Vektor2d Mario4vec(1207, 807);
Gelaende Mario4(Mario4vec, 1302-1207);
Vektor2d Mario5vec(1367, 806);
Gelaende Mario5(Mario5vec, 1462-1367);
Vektor2d Mario6vec(1681, 740);
Gelaende Mario6(Mario6vec, 31);
Vektor2d Mario7vec(1760, 689);
Gelaende Mario7(Mario7vec, 159);
vector<Gelaende> MarioLvl{MarioBoden, Mario1, Mario1b, Mario2, Mario3, Mario4, Mario5, Mario6, Mario7 };


//Unbenutzt
//Vektor2d boden1Vec(50, 500);
//Gelaende boden1(boden1Vec, 100);
//Vektor2d boden2Vec(200, 480);
//Gelaende boden2(boden2Vec, 100);
//Vektor2d boden3Vec(350, 440);
//Gelaende boden3(boden3Vec, 100);
//Vektor2d boden4Vec(210, 390);
//Gelaende boden4(boden4Vec, 100);
//vector<Gelaende> Lvl1bodenVec{ boden1, boden2, boden3 ,boden4};

class GameWindow : public Gosu::Window
{
	std::unique_ptr<Gosu::Image> background_image;

public:
	Gosu::Image bild;
	GameWindow() 
		: Window(fbreite, fhoehe)
		, bild(Player1.grafik)
		
	{
		set_caption("Bestes Game ever!!!");

		background_image.reset(new Gosu::Image("MarioThemevor.png", Gosu::IF_TILEABLE));		//Hintergrund
	}

	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override
	{
		background_image->draw(0, 0, 0);

		//graphics().draw_triangle(
		//	double(Player1.fussLinks.get_x()) + 8, double(Player1.hitboxVec.at(Player1.hoehe - 1).get_y()), Gosu::Color::RED,		// Spitze oben
		//	//50 + x, (fhoehe - bodenEbene) - 50 + y, Gosu::Color::GREEN,
		//	double(Player1.fussRechts.get_x()) -8, double(Player1.fussRechts.get_y()), Gosu::Color::RED,		//Spitze rechts
		//	//100 + x, (fhoehe - bodenEbene) + y, Gosu::Color::GREEN,
		//	double(Player1.fussLinks.get_x()), double(Player1.fussLinks.get_y()), Gosu::Color::RED,
		//	//0 + x, (fhoehe - bodenEbene) + y, Gosu::Color::GREEN,
		//	0.0
		//);
		
		//Bild einfügen

		bild.draw_rot(Player1.fussLinks.get_x() + (Player1.breite/2) , Player1.fussLinks.get_y(), 5.0, 
			180.0,
			0.5,0.95
		);

		graphics().draw_line(
			0.0, (bodenEbene), Gosu::Color::WHITE,
			fbreite, (bodenEbene), Gosu::Color::WHITE,
			0.0
		);
		for(Gelaende elem: MarioLvl)
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
		
		if (ctr <= 20 && input().down(Gosu::KB_W) && Player1.fussLinks.get_y() >= (-100 + Player1.ground))// || ctr <= 20) //W gedrückt und Sprunghöhe über ground nicht erreicht
		{	
			cout << "w Taste" << endl;
			if((Player1.fussLinks.get_y() <= -100 + Player1.ground) )
			{
				jmp = true;
				cout << "oben angekommen" << endl;
			}
			if(jmp == false)	//Wenn nicht schon gesprungen
			{
				Player1.hitboxVec.at(Player1.hoehe - 1).add_y(-5);
				Player1.fussLinks.add_y(-5);
				Player1.fussRechts.add_y(-5);		//Sprung
				cout << "springe" << endl;
			}
		}
		if((!input().down(Gosu::KB_W) && Player1.fussLinks.get_y() < (Player1.ground)) || jmp || ctr >= 20)	//W nicht gedrückt oder Sprung durchgeführt
		{

			cout << "Sprung aufhoeren" << endl;
			Player1.hitboxVec.at(Player1.hoehe - 1).add_y(5);
			Player1.fussLinks.add_y(5);
			Player1.fussRechts.add_y(5);		//Fallen
			jmp = true;

			if( Player1.fussLinks.get_y() >= 0 + Player1.ground)
			{
				jmp = false;
				cout << "jmp false" << endl;
			}
		}
	}
	int active_x_left = 0; 
	int active_x_right = 0;
	int active_y = 0;
	void ask_boden()
	{
		for (Gelaende elem : MarioLvl)
		{
			if (Player1.fussLinks.get_y() <= elem.left.get_y()) // dreieck ueber Ebene 
			{
				cout << "ueber Ebene, pruefe X" << endl;
				ctr = 0;
				if (((Player1.fussLinks.get_x() <= elem.right.get_x()) && (Player1.fussLinks.get_x() >= elem.left.get_x()))
					|| ((Player1.fussRechts.get_x() <= elem.right.get_x()) && (Player1.fussRechts.get_x() >= elem.left.get_x())))
				{
					cout << elem.height<< ": ueber und zwischen Ebene!"  << endl;
					if (jmp || ((Player1.fussLinks.get_x() > active_x_right) || Player1.fussRechts.get_x() < active_x_left))
					{
						cout << "neue Ebene! : " << elem.height << endl;
						Player1.ground = elem.height;
						active_x_left = elem.left.get_x();
						active_x_right = elem.right.get_x();
					}
				}
				else
				{
					if (Player1.ground == elem.height)
					{
						Player1.ground = bodenEbene;
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
		//Spieler mit Bewegung
		if (input().down(Gosu::KB_D) && x <= (fbreite -100))
		{
			Player1.fussLinks.add_x(5);
			Player1.fussRechts.add_x(5);
		}
		if (input().down(Gosu::KB_A) && x >= 0)
		{
			Player1.fussLinks.add_x(-5);
			Player1.fussRechts.add_x(-5);
		}
		if (jmp || !input().down(Gosu::KB_W))
		{
			cout << "ask_Boden" << endl;
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
