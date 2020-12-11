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
	bool links = false;
	int maxX;

	Projektil(Vektor2d v, int speed, int range, bool l)
	{
		this->speed = speed;
		this->hitboxLinks = v;
		v.add_x(5);
		this->hitboxRechts = v;
		this->links = l;
		if (links)
		{
			this->maxX = hitboxLinks.get_x() - range;
		}
		else
		{
			this->maxX = hitboxLinks.get_x() + range;
		}
		
	}

	void destroy()
	{
		//free(this);
	}

	bool move()
	{
		if(this->links)
		{
			if (this->hitboxRechts.get_x() > this->maxX)
			{
				this->hitboxLinks.add_x(-3);
				this->hitboxRechts.add_x(-3);
				return true;
			}
			else
			{
				return false;
			}
		}
		if(!this->links)
		{
			if (this->hitboxLinks.get_x() < this->maxX)
			{
				this->hitboxLinks.add_x(3);
				this->hitboxRechts.add_x(3);
				return true;
			}
			else
			{
				return false;
			}
		}
	}
};

