#include "stellar_background.h"
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;


void stellar_background::speedRand()
{
	speedTab = new float[stars_count];
	for (int i = 0; i < stars_count; i++)
	{
		if(i < stars_count/4)
			speedTab[i] = speed + speed * (rand() % deltaSpeed);
		else
			speedTab[i] = speed + speed * (rand() % (deltaSpeed/3));
		float k = (speed/speedTab[i]); 
		Color temp_color = star_color;
		temp_color.a = temp_color.a / deltaSpeed / k;
		stars[i].color = temp_color;
	}
}

stellar_background::stellar_background()
{
	window_width = 100;
	window_height = 100;

	stars_count = 20;

	star_color = Color::White;
	background_color = Color::Black;

	speed = 0;

	for (int i = 0; i < stars_count; i++)
	{
		stars.append(Vector2f(rand() % window_width, rand() % window_height));
	}

	speedRand();
}

stellar_background::stellar_background(unsigned int w_width = 100, unsigned int w_height = 100, unsigned int s_count = 20, 
	Color s_color = Color::White, Color b_color = Color::Black, float v = 0)
{
	window_width = w_width;
	window_height = w_height;

	stars_count = s_count;

	star_color = s_color;
	background_color = b_color;

	speed = v/1000;

	for (int i = 0; i < stars_count; i++)
	{
		stars.append(Vector2f(rand() % window_width, rand() % window_height));
	}
	for (int i = 0; i < stars_count; i++)
	{
		stars[i].color = star_color;
	}

	speedRand();
}

stellar_background::~stellar_background()
{
	delete[] speedTab;
}

void stellar_background::draw(RenderWindow &window)
{
	RectangleShape background;
	background.setSize(Vector2f(window_width, window_height));
	background.setFillColor(background_color);
	background.setOutlineColor(background_color);
	
	window.draw(background);
	window.draw(stars);

	//I draw points 4 times to make them look bigger
	for (int i = 0; i < stars_count; i++)
	{
		stars[i].position += Vector2f(1, 0);
	}
	window.draw(stars);

	for (int i = 0; i < stars_count; i++)
	{
		stars[i].position += Vector2f(0, 1);
	}
	window.draw(stars);

	for (int i = 0; i < stars_count; i++)
	{
		stars[i].position += Vector2f(-1, 0);
	}
	window.draw(stars);

	for (int i = 0; i < stars_count; i++)
	{
		stars[i].position += Vector2f(0, -1);
	}
}

void stellar_background::move(Time deltaTime)
{
	for (int i = 0; i < stars_count; i++)
	{
		stars[i].position += Vector2f(0, speedTab[i] * deltaTime.asMilliseconds());
	}

	for (int i = 0; i < stars_count; i++)
	{
		if (stars[i].position.y > window_height)
		{
			stars[i].position = Vector2f(rand() % window_width, -10);
			
			//speedTab[i] = speed + speed * 0,2 + speed * (rand() % deltaSpeed); // more fast stars
			//float k = (speedTab[i] / speed);
			//stars[i].color = Color(255 / k, 255 / k, 255 / k);
		}
	}
}
