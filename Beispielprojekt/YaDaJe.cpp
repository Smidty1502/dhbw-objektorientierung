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
		set_caption("Gosu Tutorial mit Git Test_Aenderung von Davidv2, haksdljads");
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

	/*void jump()
	{
		for (int i = 0; i <= 30; i++)
		{
			y += 2;
			Sleep(50);
		}
		for (int i = 0; i <= 30; i++)
		{
			y -= 2;
			Sleep(50);
		}
	}*/

	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		//Dreieck mit Bewegung
		if (input().down(Gosu::KB_W) && y >= -450)
		{
			y -= 5;
		}
		if (input().down(Gosu::KB_S) && y <= 100)
		{
			y += 5;
		}
		if (input().down(Gosu::KB_D) && x <= 700)
		{
			x += 5;
		}
		if (input().down(Gosu::KB_A) && x >= 0)
		{
			x -= 5;
		}
		/*if (input().down(Gosu::KB_W))
		{
			if (!jmp)
			{
				jump();
			}
		}*/
	}
};

// C++ Hauptprogramm
int main()
{
	GameWindow window;
	window.show();
}
