#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <Windows.h>

#include "Vektor2d.h"

// Simulationsgeschwindigkeit
const double DT = 100.0;
int x = 0;
int y = 0;
bool jmp = false;

class GameWindow : public Gosu::Window
{
public:
	Gosu::Image bild;
	GameWindow()
		: Window(800, 600)
	{
		set_caption("Bestes Game ever!!!");
	}

	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override
	{
		graphics().draw_triangle(
			50 + x, 450 + y, Gosu::Color::GREEN,
			100 + x, 499 + y, Gosu::Color::GREEN,
			0 + x, 499 + y, Gosu::Color::GREEN,
			0.0
		);
		graphics().draw_line(
			0.0, 500, Gosu::Color::WHITE,
			800, 500, Gosu::Color::WHITE,
			0.0
		);
	}

	

	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		//Dreieck mit Bewegung
		if (input().down(Gosu::KB_D) && x <= 700)
		{
			x += 5;
		}
		if (input().down(Gosu::KB_A) && x >= 0)
		{
			x -= 5;
		}
		if (input().down(Gosu::KB_W) && y>= -100)
		{
			if(y<=-95)
			{
				jmp = true;
			}
			if(!jmp)
			{
				y -= 5;
			}
		}
		if((!input().down(Gosu::KB_W) && y< 0) || jmp)
		{
			y += 5;
			jmp = true;
			if( y== 0)
			{
				jmp = false;
			}
		}
	}
};

// C++ Hauptprogramm
int main()
{
	GameWindow window;
	window.show();
}
