#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <Windows.h>

#include "Figur.h"
#include "Spieler.h"
#include "Vektor2d.h"

// Simulationsgeschwindigkeit
const double DT = 100.0;
int x = 0;
int y = 0;
bool jmp = false;

//Auflösung
const int  fbreite = 1280;
const int  fhoehe = 720;
const int bodenEbene = 150;


class GameWindow : public Gosu::Window
{
	std::unique_ptr<Gosu::Image> background_image;

public:
	Gosu::Image bild;
	GameWindow() 
		: Window(fbreite, fhoehe)

	{
		set_caption("Bestes Game ever!!!");

		background_image.reset(new Gosu::Image("HintergrundGameTest.png", Gosu::IF_TILEABLE));		//Hintergrund
	}

	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override
	{
		background_image->draw(0, 0, 0);

		graphics().draw_triangle(
			50 + x, 450 + y, Gosu::Color::GREEN,
			100 + x, 499 + y, Gosu::Color::GREEN,
			0 + x, 499 + y, Gosu::Color::GREEN,
			0.0
		);


		graphics().draw_line(
			0.0, (fhoehe - bodenEbene), Gosu::Color::WHITE,
			fbreite, (fhoehe - bodenEbene), Gosu::Color::WHITE,
			0.0
		);
	}

	void ask_KB_W()		//Tastaturabfrage für W
	{
		if (input().down(Gosu::KB_W) && y>= -100) //W gedrückt und Sprunghöhe nicht erreicht
		{
			if(y<=-95)
			{
				jmp = true;
			}
			if(!jmp)
			{
				y -= 5;		//Sprung
			}
		}
		if((!input().down(Gosu::KB_W) && y< 0) || jmp)	//W nicht gedrückt oder Sprung durchgeführt
		{
			y += 5;		//Fallen
			jmp = true;
			if( y== 0)
			{
				jmp = false;
			}
		}
	}

	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		//Dreieck mit Bewegung
		if (input().down(Gosu::KB_D) && x <= (fbreite -100))
		{
			x += 5;
		}
		if (input().down(Gosu::KB_A) && x >= 0)
		{
			x -= 5;
		}
		ask_KB_W();
	}
};

// C++ Hauptprogramm
int main()
{
	GameWindow window;
	window.show();
}
