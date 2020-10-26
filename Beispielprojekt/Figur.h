#pragma once
#include <vector>
#include "Vektor2d.h"
using namespace std;

class Figur
{
public:
	int Leben = 0;
	int breite, hoehe;
	vector<Vektor2d> fuesseVec;
	vector<Vektor2d> hitboxVec;
	//double pos_x, pos_y;
};

