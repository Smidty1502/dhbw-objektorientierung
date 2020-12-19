#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <vector>
#include <forward_list>
#include <string>
#include <iostream>
#include <Windows.h>

#include "Figur.h"
#include "Spieler.h"
#include "Vektor2d.h"
#include "Gelaende.h"
#include "Gegner.h"
#include <memory>


// Simulationsgeschwindigkeit

const double DT = 100.0;
int x = 0;
int y = 0;
bool jmp = false;

//Auflösung
const int  fbreite = 1920;
const int  fhoehe = 1080;

const int bodenEbene = 936;

bool gespiegelt = false;

//Sprunghöhe
int sprunghoehe = -65;
double timer = 0;

Vektor2d PSpawn(20, bodenEbene);
Vektor2d PHitbox(20, bodenEbene);
Spieler Player1(PSpawn, 16, PHitbox, 41);
Vektor2d PBowserMitte(1880, 145);
Vektor2d PBowserHitbox(1910, 145);
Gegner Bowser1(PBowserMitte, 108, PBowserHitbox, 98, "BowserSwag");
Vektor2d PWilliMitte(1600, 792);
Vektor2d PWilliHitbox(1579, 792);
Gegner KugelWilli(PWilliMitte, 43, PWilliHitbox, 50, "Kanone");
vector<Gegner> Gegnervec{Bowser1, KugelWilli};
Vektor2d tempVec(0, KugelWilli.hoehe / 2 + 10);
Projektil kugel(KugelWilli.hitboxUnten - tempVec, 5, 1920 / 2, true);
unique_ptr<Projektil>kugelPtr = make_unique<Projektil>(kugel);

Gosu::Font font1(20);




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
Gelaende Mario8(Mario8vec, 1712 - 1616);
Vektor2d Mario9vec(1415, 580);
Gelaende Mario9(Mario9vec, 1542 - 1414);
Vektor2d Mario10vec(1243, 560);
Gelaende Mario10(Mario10vec, 1306 - 1242);
Vektor2d Mario11vec(1085, 565);
Gelaende Mario11(Mario11vec, 1148 - 1084);
Vektor2d Mario12vec(966, 535);
Gelaende Mario12(Mario12vec, 997 - 965);
Vektor2d Mario13vec(690, 655);
Gelaende Mario13(Mario13vec, 849 - 689);
Vektor2d Mario14vec(544, 605);
Gelaende Mario14(Mario14vec, 639 - 543);
Vektor2d Mario15vec(118, 570);
Gelaende Mario15(Mario15vec, 437 - 117);

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
Gelaende Mario31(Mario31vec, 1918 - 1698);
vector<Gelaende> MarioLvl{ MarioBoden, Mario1, Mario2, Mario3, Mario4, Mario5, Mario6, Mario7, Mario8, Mario9, Mario10, Mario11, Mario12, Mario13, Mario14, Mario15, Mario16, Mario17, Mario18, Mario19, Mario20, Mario21, Mario22, Mario23, Mario24, Mario25, Mario26, Mario27, Mario28, Mario29, Mario30, Mario31 };

Vektor2d Mario40vec(fbreite - 100, fhoehe - 60);
Gelaende Mario40(Mario40vec, 100);
Vektor2d Mario41vec(fbreite - 100, fhoehe - 2 * 60);
Gelaende Mario41(Mario41vec, 100);
Vektor2d Mario42vec(fbreite - 100, fhoehe - 3 * 60);
Gelaende Mario42(Mario42vec, 100);
Vektor2d Mario43vec(fbreite - 100, fhoehe - 4 * 60);
Gelaende Mario43(Mario43vec, 100);
Vektor2d Mario44vec(fbreite - 100, fhoehe - 5 * 60);
Gelaende Mario44(Mario44vec, 100);
Vektor2d Mario45vec(fbreite - 100, fhoehe - 6 * 60);
Gelaende Mario45(Mario45vec, 100);
Vektor2d Mario46vec(fbreite - 100, fhoehe - 7 * 60);
Gelaende Mario46(Mario46vec, 100);
Vektor2d Mario47vec(fbreite - 100, fhoehe - 8 *60);
Gelaende Mario47(Mario47vec, 100);
Vektor2d Mario48vec(fbreite - 100, fhoehe - 9 * 60);
Gelaende Mario48(Mario48vec, 100);
Vektor2d Mario49vec(fbreite - 100, fhoehe - 10 * 60);
Gelaende Mario49(Mario49vec, 100);
Vektor2d Mario50vec(fbreite - 100, fhoehe - 11* 60);
Gelaende Mario50(Mario50vec, 100);
Vektor2d Mario51vec(fbreite - 100, fhoehe - 12* 60);
Gelaende Mario51(Mario51vec, 100);
Vektor2d Mario52vec(fbreite - 100, fhoehe - 13* 60);
Gelaende Mario52(Mario52vec, 100);
Vektor2d Mario53vec(fbreite - 100, fhoehe - 14 * 60);
Gelaende Mario53(Mario53vec, 100);
Vektor2d Mario54vec(fbreite - 100, fhoehe - 15 * 60);
Gelaende Mario54(Mario54vec, 100);
Vektor2d Mario55vec(fbreite - 100, 145);
Gelaende Mario55(Mario55vec, 100);

vector<Gelaende> MarioLv2{ MarioBoden, Mario40, Mario41, Mario42, Mario43, Mario44, Mario45, Mario46, Mario47, Mario48, Mario49, Mario50, Mario51, Mario52, Mario53, Mario54, Mario55 };

class GameWindow : public Gosu::Window
{
	std::unique_ptr<Gosu::Image> background_image;

public:
	Gosu::Image bild;
	Gosu::Image bildL;
	Gosu::Image bullet;
	Gosu::Image win;
	Gosu::Image bowser;
	Gosu::Image Willi;
	Gosu::Image Kanone;

	GameWindow()
		: Window(fbreite, fhoehe)
		, bild(Player1.grafik)
		, bildL(Player1.grafikl)
		, bullet("RBullet.png")
		, win("winner1.png")
		, bowser(Bowser1.grafik)
		, Willi("LKugelwilli.png")
		, Kanone(KugelWilli.grafik)
	{
		set_caption("Bestes Game ever!!!");

		background_image.reset(new Gosu::Image("MarioTheme.png", Gosu::IF_TILEABLE));		//Hintergrund
	}


	void draw() override
	{
		background_image->draw(0, 0, 0);

		//Bild einfügen
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
		for (int i = 0;i < 5;i++)
		{
			if (Player1.shotsVec.at(i)->fliegt)
			{
				bullet.draw_rot(Player1.shotsVec.at(i)->hitboxLinks.get_x(), Player1.shotsVec.at(i)->hitboxLinks.get_y(), 0.0, 0,
					0.8, 0.5,
					0.25, 0.25);
			}
		}
		if (KugelWilli.alive)
		{
			Kanone.draw_rot(KugelWilli.fussLinks.get_x(), KugelWilli.fussLinks.get_y() - KugelWilli.hoehe / 2, 0, 0,
				0.5, 0.5,
				1, 1
			);
		}
		if (KugelWilli.alive)
		{
			Willi.draw_rot(kugelPtr->hitboxLinks.get_x(), kugelPtr->hitboxLinks.get_y(), 0, 0
				, 0.5, 0.5,
				1, 1);
		}

		if(Bowser1.alive)
		{
			bowser.draw_rot(Bowser1.fussLinks.get_x(), Bowser1.fussLinks.get_y() - Bowser1.hoehe/2, 0, 0
			, 0.5, 0.5,
			1, 1
			);
		}
		if (wT >= 1)
		{
			win.draw(fbreite / 2 - 250, fhoehe / 2 - 200, 5, 1,1);
		}

		//Für Fehlererkennung der Karte
		/*for(Gelaende elem: MarioLvl)
		{
			graphics().draw_line(
				elem.left.get_x(), elem.left.get_y(), Gosu::Color::WHITE,
				elem.right.get_x(), elem.right.get_y(), Gosu::Color::WHITE,
				0.0);
		}*/
		
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
		
		if (ctr <= 15 && input().down(Gosu::KB_W) && Player1.fussLinks.get_y() >= (sprunghoehe + Player1.ground))// || ctr <= 20) //W gedrückt und Sprunghöhe über ground nicht erreicht
		{	
			//cout << "w Taste" << endl;
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
				//cout << "springe" << endl;
			}
		}
		if((!input().down(Gosu::KB_W) && Player1.fussLinks.get_y() < (Player1.ground)) || jmp || ctr >= 15)	//W nicht gedrückt oder Sprung durchgeführt
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
		vector<Gelaende> currentLvl;
		switch(Player1.level) {
		case 1: currentLvl = MarioLvl;
			break;
		case 2: currentLvl = MarioLv2;
			break;
		default: cout << "Kein Level erkannt!" << endl;
			break;
		}
		for (Gelaende elem : currentLvl)
		{
			if (Player1.fussLinks.get_y() <= elem.left.get_y()) // dreieck ueber Ebene 
			{
				//cout << "ueber Ebene, pruefe X" << endl;
				ctr = 0;
				if (((Player1.fussLinks.get_x() <= elem.right.get_x()) && (Player1.fussLinks.get_x() >= elem.left.get_x()))
					|| ((Player1.fussRechts.get_x() <= elem.right.get_x()) && (Player1.fussRechts.get_x() >= elem.left.get_x())))
				{
					//cout << elem.height<< ": ueber und zwischen Ebene!"  << endl;
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
					//cout << "ausserhalb if" << endl;
				}
			}
		}
	}

	int shoot_CD = 0;
	int aktive_projektile = 0;
	int shoot(bool links, int ProjektilIndex)
	{
		if(aktive_projektile < 10)
		{
			Vektor2d hb(Player1.hitboxUnten.get_x(),Player1.hitboxUnten.get_y() - (Player1.hoehe / 2));
			Projektil p(hb, 10, 400, links);
			auto uP = make_unique<Projektil>(p);
			cout << "Shuss erstellt!" << endl;
			aktive_projektile++;
			Player1.shotsVec.at(ProjektilIndex) = move(uP);
			cout << "Cooldown hoch" << endl;
			shoot_CD = 20;
			return ProjektilIndex + 1;
		}
		else
		{
			cout << "Projektilvektor voll!" << endl;
			return ProjektilIndex;
		}
	}

	//void zeit()
	//{
	//	//Gosu::Color c = WHITE;
	//	timer++;
	//	font1.draw_rel(to_string(timer/60), 30, 50, 1, 1, 1,1,1, 0x11111111, Gosu::AM_DEFAULT);
	//}

	int wT = 0;
	int ProjektilIndex = 0;
	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		if (KugelWilli.alive)
		{
			if (kugelPtr->move())
			{
				//cout << "KugelWilli bewegt zu: " << kugelPtr->hitboxLinks.get_x() << endl;
				if (kugelPtr->hitboxLinks.get_x() <= Player1.fussRechts.get_x() && kugelPtr->hitboxRechts.get_x() >= Player1.fussLinks.get_x())
				{
					cout << "Treffer?" << endl;
					//if(770 745)
					if (Player1.hitboxUnten.get_y() >= kugelPtr->hitboxLinks.get_y() - 12) 
					{
						cout << "Spieler unter Kugel" << endl;
						if(Player1.hitboxOben.get_y() <= kugelPtr->hitboxLinks.get_y() + 13)
						{
							cout << "Treffer!!!" << endl; 
							Player1.hitboxOben.set_x(Player1.breite / 2);
							Player1.hitboxUnten.set_x(Player1.breite / 2);
							Player1.fussLinks.set_x(0);
							Player1.fussRechts.set_x(Player1.breite);
							Player1.hitboxOben.set_y(-Player1.hoehe + bodenEbene);
							Player1.hitboxUnten.set_y(bodenEbene);
							Player1.fussLinks.set_y(bodenEbene);
							Player1.fussRechts.set_y(bodenEbene);
							Player1.ground = bodenEbene;
							gespiegelt = false;
						}
					}
				}
				//cout << "hoehe: " << kugelPtr->hitboxLinks.get_y();
			}
			else
			{
				Vektor2d tmp = KugelWilli.hitboxUnten;
				tmp.add_y(-KugelWilli.hoehe / 2 - 10);
				Projektil p(tmp, 5, fbreite / 2, true);
				unique_ptr<Projektil> uP = make_unique<Projektil>(p);
				kugelPtr = move(uP);
			}
		}

		if (Player1.ground == 145 || wT >= 1)
		{
			wT++;
			cout << "du hast gewonnen :)" << endl;
			if (wT >= 180)
			{
				Player1.level++;
				Player1.hitboxOben.set_x(Player1.breite / 2);
				Player1.hitboxUnten.set_x(Player1.breite / 2);
				Player1.fussLinks.set_x(0);
				Player1.fussRechts.set_x(Player1.breite);
				Player1.hitboxOben.set_y(-Player1.hoehe + bodenEbene);
				Player1.hitboxUnten.set_y(bodenEbene);
				Player1.fussLinks.set_y(bodenEbene);
				Player1.fussRechts.set_y(bodenEbene);
				Player1.ground = bodenEbene;
				gespiegelt = false;
				wT = 0;
			}

		}
		if (shoot_CD > 0)
		{
		shoot_CD--;
		}
		//cout << "KugelWilli: " << KugelWilli.alive << endl;
		for (int i = 0; i < 5; i++)
		{
			//Projektil* pP = Player1.shotsVec.at(i).get();
			if (Player1.shotsVec.at(i)->move())
			{
				cout << "Schuss " << i << " bewegt zu " << Player1.shotsVec.at(i)->hitboxLinks.get_x() << " , " << Player1.shotsVec.at(i)->hitboxLinks.get_y() << "Maximum : " << Player1.shotsVec.at(i)->maxX << endl;
				for (Gegner& elem : Gegnervec)
				{
					if (Player1.shotsVec.at(i)->hitboxLinks.get_x() <= elem.fussRechts.get_x() && Player1.shotsVec.at(i)->hitboxRechts.get_x() >= elem.fussLinks.get_x())
					{
						if (Player1.shotsVec.at(i)->height <= elem.hitboxUnten.get_y() && Player1.shotsVec.at(i)->height >= elem.hitboxOben.get_y())
						{
							cout << "Treffer" << elem.grafik << endl;
							if (elem.grafik == "BowserSwag.png")
							{
								Bowser1.alive = false;
							}
							if (elem.grafik == "Kanone.png")
							{
								KugelWilli.alive = false;
							}
						}
					}
				}
			}
			else
			{
				//cout << "Schuss " << i << " ueber Maximum"<< endl;
				if (aktive_projektile > 0)
				{
					aktive_projektile--;
				}
			}
		}
		//cout << "KugelWilli: " << KugelWilli.alive << " , " << KugelWilli.al << endl;

		if (input().down(Gosu::KB_P))
		{
			cout << "Fuss Links: " << Player1.fussLinks << endl << "Tragendes Gelaende: " << Player1.ground << endl;
		}


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
			//cout << "ask_Boden" << endl;
			ask_boden();
		}
		ask_KB_W();
		if(input().down(Gosu::KB_SPACE)) // Leer gedrückt
		{
			//cout << "Leer gedrueckt! Index: " << ProjektilIndex << endl;
			//cout << "Cooldown noch: " << shoot_CD << endl;
			if (shoot_CD == 0)
			{
				ProjektilIndex = shoot(gespiegelt, ProjektilIndex);
				if (ProjektilIndex == 5)
				{
					ProjektilIndex = 0;
				}
				//cout << "Index hoch/runter auf: " << ProjektilIndex << endl;
			}
		}
	}
	
};

// C++ Hauptprogramm
int main()
{
	Vektor2d tempVec(0, KugelWilli.hoehe / 2);
	Projektil kugel(KugelWilli.hitboxUnten - tempVec, 5, 1920 / 2, true);
	unique_ptr<Projektil>kugelPtr = make_unique<Projektil>(kugel);

	cout << Bowser1.hitboxOben.get_y() << " . " << Bowser1.hitboxUnten.get_y() << endl;
	cout << KugelWilli.hitboxOben.get_y() << " , " << KugelWilli.hitboxUnten.get_y() << endl;
	bool first = true;
	if (first)
	{
		Vektor2d v(0, 0);
		Projektil p(v, 1, 1, true);
		for (int i = 0; i < 5; i++)
		{
			unique_ptr<Projektil> uP = make_unique<Projektil>(p);
			Player1.shotsVec.push_back(move(uP));
		}
	}
	GameWindow window;
	window.show();
}
