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

//Aufl�sung
const int  fbreite = 1920;
const int  fhoehe = 1080;

const int bodenEbene = 936;

bool gespiegelt = false;

//Sprungh�he
int sprunghoehe = -65;



Vektor2d PSpawn(20, bodenEbene);
Vektor2d PHitbox(50, bodenEbene);
Spieler Player1(PSpawn, 16, PHitbox, 41);

Vektor2d MarioBodenvec(0, 935);
Gelaende MarioBoden(MarioBodenvec, 1920);
Vektor2d Mario1vec(1056, 840);
Gelaende Mario1(Mario1vec, 96);  
Vektor2d Mario2vec(1536, 792);
Gelaende Mario2(Mario2vec, 96);
Vektor2d Mario3vec(985, 880);
Gelaende Mario3(Mario3vec, 32);
Vektor2d Mario4vec(1207, 805);
Gelaende Mario4(Mario4vec, 1302 - 1206);
Vektor2d Mario5vec(1367, 800);
Gelaende Mario5(Mario5vec, 1462 - 1366);
Vektor2d Mario6vec(1681, 740);
Gelaende Mario6(Mario6vec, 32);
Vektor2d Mario7vec(1760, 690);
Gelaende Mario7(Mario7vec, 160);
Vektor2d Mario8vec(1617, 635);
Gelaende Mario8(Mario8vec, 1712-1616);
Vektor2d Mario9vec(1415, 580);
Gelaende Mario9(Mario9vec, 1542-1414);
Vektor2d Mario10vec(1243, 560);
Gelaende Mario10(Mario10vec, 1306-1242);
Vektor2d Mario11vec(1085, 565);
Gelaende Mario11(Mario11vec, 1148-1084);
Vektor2d Mario12vec(966, 535);
Gelaende Mario12(Mario12vec, 997-965);
Vektor2d Mario13vec(690, 655);
Gelaende Mario13(Mario13vec, 849-689);
Vektor2d Mario14vec(544, 605);
Gelaende Mario14(Mario14vec, 639-543);
Vektor2d Mario15vec(118, 570);
Gelaende Mario15(Mario15vec, 437-117);

Vektor2d Mario16vec(287, 510);
Gelaende Mario16(Mario16vec, 32);
Vektor2d Mario17vec(226, 455);
Gelaende Mario17(Mario17vec, 32);
Vektor2d Mario18vec(161, 400);
Gelaende Mario18(Mario18vec, 32);
Vektor2d Mario19vec(212, 340);
Gelaende Mario19(Mario19vec, 32);
Vektor2d Mario20vec(262, 280);
Gelaende Mario20(Mario20vec, 32);
Vektor2d Mario21vec(379, 275);
Gelaende Mario21(Mario21vec, 32);

Vektor2d Mario22vec(407, 215);
Gelaende Mario22(Mario22vec, 143);
Vektor2d Mario23vec(598, 235);
Gelaende Mario23(Mario23vec, 894);
Vektor2d Mario24vec(555, 170);
Gelaende Mario24(Mario24vec, 32);
Vektor2d Mario25vec(710, 165);
Gelaende Mario25(Mario25vec, 32);
Vektor2d Mario26vec(834, 155);
Gelaende Mario26(Mario26vec, 32);
Vektor2d Mario27vec(964, 140);
Gelaende Mario27(Mario27vec, 128);
Vektor2d Mario28vec(1200, 135);
Gelaende Mario28(Mario28vec, 32);
Vektor2d Mario29vec(1320, 130);
Gelaende Mario29(Mario29vec, 32);
Vektor2d Mario30vec(1425, 90);
Gelaende Mario30(Mario30vec, 160);
Vektor2d Mario31vec(1698, 145);
Gelaende Mario31(Mario31vec, 1918-1698);
vector<Gelaende> MarioLvl{ MarioBoden, Mario1, Mario2, Mario3, Mario4, Mario5, Mario6, Mario7, Mario8, Mario9, Mario10, Mario11, Mario12, Mario13, Mario14, Mario15, Mario16, Mario17, Mario18, Mario19, Mario20, Mario21, Mario22, Mario23, Mario24, Mario25, Mario26, Mario27, Mario28, Mario29, Mario30, Mario31 };

vector<Projektil> projektilVec;


class GameWindow : public Gosu::Window
{
	std::unique_ptr<Gosu::Image> background_image;

public:
	Gosu::Image bild;
	Gosu::Image bildL;

	GameWindow() 
		: Window(fbreite, fhoehe)
		, bild(Player1.grafik)
		, bildL(Player1.grafikl)
	{
		set_caption("Bestes Game ever!!!");

		background_image.reset(new Gosu::Image("MarioTheme.png", Gosu::IF_TILEABLE));		//Hintergrund
	}


	void draw() override
	{
		background_image->draw(0, 0, 0);

		//Bild einf�gen
		if (!gespiegelt)
		{
			bild.draw_rot(Player1.fussLinks.get_x() + (Player1.breite / 2), Player1.fussLinks.get_y(), 5.0,
				0.0,
				0.5, 0.95
			);
		}
		if(gespiegelt)
		{
			bildL.draw_rot(Player1.fussLinks.get_x() + (Player1.breite / 2) , Player1.fussLinks.get_y(), 5.0,
				0.0,
				0.5,0.95
			);
		}

		//F�r Fehlererkennung der Karte
		/*for(Gelaende elem: MarioLvl)
		{
			graphics().draw_line(
				elem.left.get_x(), elem.left.get_y(), Gosu::Color::WHITE,
				elem.right.get_x(), elem.right.get_y(), Gosu::Color::WHITE,
				0.0);
		}*/
		
	}

	int ctr = 0;
	void ask_KB_W()		//Tastaturabfrage f�r W
	{
		if (input().down(Gosu::KB_W))
		{
			ctr++;
		} else
		{
			ctr = 0;
		}
		
		if (ctr <= 15 && input().down(Gosu::KB_W) && Player1.fussLinks.get_y() >= (sprunghoehe + Player1.ground))// || ctr <= 20) //W gedr�ckt und Sprungh�he �ber ground nicht erreicht
		{	
			cout << "w Taste" << endl;
			if(Player1.fussLinks.get_y() <= sprunghoehe + Player1.ground)
			{
				jmp = true;
				cout << "oben angekommen" << endl;
			}
			if(jmp == false)	//Wenn nicht schon gesprungen
			{
				Player1.hitboxOben.add_y(-5);
				Player1.hitboxUnten.add_y(-5);
				Player1.fussLinks.add_y(-5);
				Player1.fussRechts.add_y(-5);		//Sprung
				cout << "springe" << endl;
			}
		}
		if((!input().down(Gosu::KB_W) && Player1.fussLinks.get_y() < (Player1.ground)) || jmp || ctr >= 15)	//W nicht gedr�ckt oder Sprung durchgef�hrt
		{


			cout << "Sprung aufhoeren" << endl;
			Player1.hitboxOben.add_y(5);
			Player1.hitboxUnten.add_y(5);
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

	int aktive_projektile = 0;
	void shoot(bool links, int p_Zahl)
	{
		aktive_projektile++;
		Vektor2d hb(Player1.hitboxUnten.get_x(),Player1.hitboxUnten.get_y() + (Player1.hoehe / 2));
		Projektil p(hb, 3, 200);
		if(aktive_projektile == p_Zahl)
		{
			projektilVec.push_back(p);
		}	
		else
		{
			projektilVec.at(p_Zahl);
		}
		
		for(size_t i=0; i<p.range;i=i+p.speed)
		{
			p.move(links);
			projektilVec.at(p_Zahl) = p;
		}
		aktive_projektile--;
	}

	bool shot = false;
	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		//Spieler mit Bewegung
		if (input().down(Gosu::KB_D) && x <= (fbreite -100))
		{
			Player1.hitboxOben.add_x(5);
			Player1.hitboxUnten.add_x(5);
			Player1.fussLinks.add_x(5);
			Player1.fussRechts.add_x(5);
			gespiegelt = false;

		}
		if (input().down(Gosu::KB_A) && x >= 0)
		{
			Player1.hitboxOben.add_x(-5);
			Player1.hitboxUnten.add_x(-5);
			Player1.fussLinks.add_x(-5);
			Player1.fussRechts.add_x(-5);
			gespiegelt = true;
		}
		if (jmp || !input().down(Gosu::KB_W))
		{
			cout << "ask_Boden" << endl;
			ask_boden();
		}
		ask_KB_W();
		if(input().down(Gosu::KB_SPACE) && !shot) // Leer gedr�ckt und noch nicht geschossen
		{
			shoot(gespiegelt, 0);
		}
	}
	
};

// C++ Hauptprogramm
int main()
{
	GameWindow window;
	window.show();
}
