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
			Vektor2d tmpVec(i, 0);
			this->fuesseVec.push_back(fuss + tmpVec);
		}
		for (int i = 0; i < hoehe; i++)
		{
			Vektor2d tmpVec(0, i);
			this->hitboxVec.push_back(hitbox - tmpVec);
		}
	}



	Gosu::Image bild;
	unsigned score;
	

	Gosu::Image.new("Zombie.png")
	

	Spieler() :bild("Zombie.png")
	{
		this->fuesseVec.at(0).get_x(), this->hitboxVec.at(this->hoehe - 1).get_y();
	}


	void draw() const
	{
		bild.draw(this->fuesseVec.at(0).get_x(), this->hitboxVec.at(this->hoehe-1).get_y(),1);
	}

	void move()
	{
		/*pos_x = Gosu::wrap(pos_x, 0.0, fbreite);
		pos_y = Gosu::wrap(pos_y, 0.0, fhoehe);*/

		
	}

};

