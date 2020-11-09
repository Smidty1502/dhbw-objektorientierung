#pragma once
#include "Figur.h"
#include <string>

class Spieler :
	public Figur
{
public:
	int ground = 935; //Bodenebene
	Spieler(Vektor2d Mitte, int breite, Vektor2d hitbox, int hoehe)
	{
		
		this->breite = breite;
		this->hoehe = hoehe;
		this->hitboxUnten = hitbox;
		hitbox.add_y(hoehe);
		this->hitboxOben = hitbox;
		Vektor2d tmpVec((breite/2), 0);
		this->fussLinks = (Mitte - tmpVec);
		this->fussRechts = (Mitte + tmpVec);
		
	}
	string grafik = "MarioChar.png";
	string grafikl = "MarioCharlinks.png";
	vector<Projektil> shotsVec;
	
	
};
