#pragma once
#include "Vektor2d.h"
#include <vector>
using namespace std;

class Gelaende
{
public:
	Vektor2d left, right;
	int breite, height;
	Gelaende(Vektor2d left, int b)
	{
		this->left = left;
		Vektor2d tmpVec(left.get_x() + b, left.get_y());
		this->right = tmpVec;
		this->breite = breite;
		this->height = left.get_y();
	}
};

