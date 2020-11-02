#pragma once
#include <vector>
#include "Vektor2d.h"
#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <Windows.h>
#include "Projektil.h"


using namespace std;

class Figur
{
public:
	int Leben = 0;
	int breite, hoehe;
	Vektor2d fussLinks;
	Vektor2d fussRechts;
	Vektor2d hitboxOben;
	Vektor2d hitboxUnten;
	
	/*void shoot(bool links)
	{ 
		Vektor2d hitboxP(this->hitboxUnten.get_x(), this->hitboxUnten.get_y() + (hoehe / 2));
		Projektil projektil(hitboxP, 3, 200);
		for(int i = 0; i<projektil.range; i = i+projektil.speed)
		{
			projektil.move(links);
		}

	}*/
};

