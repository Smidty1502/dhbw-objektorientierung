#pragma once
#include <vector>
#include "Vektor2d.h"
#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <Windows.h>
#include <string>
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
	string grafikl;
	string grafik;
};

