#pragma once
#include "Figur.h"
class Gegner :
	public Figur
{
	public:
	bool alive;
	//unique_ptr<Projektil> kugelPtr;
	Gegner(Vektor2d Mitte, int breite, Vektor2d hitbox, int hoehe, string grafik)
	{
		//Vektor2d tempVec(0, hoehe / 2);
		//Projektil kugel(hitbox - tempVec, 5, 1920 /2, true);
		//kugelPtr = make_unique<Projektil>(kugel);
		this->breite = breite;
		this->hoehe = hoehe;
		this->hitboxUnten = hitbox;
		hitbox.add_y(-hoehe);
		this->hitboxOben = hitbox;
		Vektor2d tmpVec((breite / 2), 0);
		this->fussLinks = (Mitte - tmpVec);
		this->fussRechts = (Mitte + tmpVec);
		this->grafik = grafik + ".png";
		this->alive = true;
	}
	void die()
	{
		this->alive = false;
		std::cout << "STIRB!" << endl;
	}
};

