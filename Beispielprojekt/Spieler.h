#pragma once
#include "Figur.h"

class Spieler :
	public Figur
{
public:
	Spieler(Vektor2d fuss, int breite, Vektor2d hitbox, int hoehe)
	{
		this->breite = breite;
		this->hoehe = hoehe;
		for (int i = 0; i < breite; i++)
		{
			Vektor2d tmpVec(1, 0);
			this->fuesseVec.push_back(fuss + tmpVec);
		}
		for (int i = 0; i < hoehe; i++)
		{
			Vektor2d tmpVec(0, 1);
			this->hitboxVec.push_back(hitbox - tmpVec);
		}
	}
	/*Gosu::Image image;
	unsigned score;
	double pos_x, pos_y;

public:
	Spieler()		:image("Zombie.png")
	{
		pos_x = pos_y = 200;
	}


	void draw() const
	{
		image.draw(pos_x, pos_y,1);
	}

	void move()
	{
		pos_x = Gosu::wrap(pos_x, 0.0, fbreite);
		pos_y = Gosu::wrap(pos_y, 0.0, fhoehe);

		
	}*/

};

