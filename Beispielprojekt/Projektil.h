#pragma once
#include"Vektor2d.h"
#include <string>


using namespace std;

class Projektil
{
public:
	Vektor2d hitboxLinks, hitboxRechts;
	string grafik;
	int speed = 1;
	int range = 1;
	Projektil(Vektor2d v, int speed, int range)
	{
		this->range = range;
		this->speed = speed;
		this->hitboxLinks = v;
		v.add_x(5);
		this->hitboxRechts = v;
	}

	void move(bool links)
	{
		if(links)
		{
			this->hitboxLinks.add_x(-speed);
			this->hitboxRechts.add_x(-speed);
		}
		if(!links)
		{
			this->hitboxLinks.add_x(speed);
			this->hitboxRechts.add_x(speed);
		}
	}
};

