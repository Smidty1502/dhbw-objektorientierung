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
		hitbox.add_y(-hoehe);	// war mit plus... Ich glaube aber minus is richtig
		this->hitboxOben = hitbox;
		Vektor2d tmpVec((breite/2), 0);
		this->fussLinks = (Mitte - tmpVec);
		this->fussRechts = (Mitte + tmpVec);
		this->grafik = "MarioChar.png";
		this->grafikl = "MarioCharlinks.png";
		
	}
	vector<unique_ptr<Projektil>> shotsVec;
	int level = 1;
	
};
