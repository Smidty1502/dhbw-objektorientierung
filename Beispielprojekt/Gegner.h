#pragma once
#include "Figur.h"
class Gegner :
	public Figur
{
	public:
	Gegner(Vektor2d Mitte, int breite, Vektor2d hitbox, int hoehe, string grafik)
	{
		this->breite = breite;
		this->hoehe = hoehe;
		this->hitboxUnten = hitbox;
		hitbox.add_y(-hoehe);
		this->hitboxOben = hitbox;
		Vektor2d tmpVec((breite / 2), 0);
		this->fussLinks = (Mitte - tmpVec);
		this->fussRechts = (Mitte + tmpVec);
		this->grafik = grafik + ".png";
	}
};

