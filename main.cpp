#include <SFML\Graphics.hpp>
#include <iostream>
#include <sstream>
#include <math.h>
#include "stellar_background.h"
#include "Vertex_Object.h"
#include "physics.h"


using namespace std;
using namespace sf;

View getLetterboxView(View view, int windowWidth, int windowHeight);

void game(RenderWindow& window, View& view); // True game function
void keyBindings(Event& event, player_object& player, vector <laser_object>& missiles, Time& deltaTime, Clock& time_between_fire);

int main()
{

	auto resX = 460;
	auto resY = 720;

	bool frame_lock = true;

	srand(time(NULL));

	//Window Inicialisation
	RenderWindow window(VideoMode(resX, resY), "NO MORE KOTLETS?");
	window.setActive();
	if (frame_lock)
		window.setFramerateLimit(240);

	View view;
	view.setSize(resX, resY);
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	view = getLetterboxView(view, resX, resY);
	//

	game(window, view);

	return 0;

}

void game(RenderWindow& window, View& view)
{
	physics gamePhysics;
	//Developer Options
	bool fps_bool = true;
	bool debugMode = false;
	//

	Clock deltaClock;

	///objects Initialisation
	stellar_background background(window.getSize().x, window.getSize().y, 1000, Color::White, Color::Black, 4); //background

	//Player
	player_object player(10, 10, 30, 10, 60);
	player.setScale(10);
	player.setPosition(Vector2f(200, view.getSize().y - player.getLeft_down_corner().y - 30));
	//

	//missiles
	vector <laser_object> allied_missiles;
	Clock Time_between_fire;
	vector <laser_object> enemy_missiles;
	//

	//enemies
	vector <enemy_object*> enemies;

	for (size_t i = 0; i < 15; i++)
	{
		enemies.push_back(new fighter_enemy());
		Vector2f position;
		position.x = 45 + 80 * (i % 5);
		position.y = 30 + 80 * ceil(i / 5);
		enemies[i]->setPosition(position);
		enemies[i]->setScale(5);
	}
	//

	//Debug

	//
	///

	//Fonts
	Font openSans;
	openSans.loadFromFile("OpenSans-Light.ttf");
	//

	while (window.isOpen())
	{
		Time deltaTime = deltaClock.restart(); //delta time betwen frames

		if (deltaTime.asMilliseconds() > 100)
		{
			deltaTime *= float(0);
		}

		// Events
		Event event;
		while (window.pollEvent(event))
		{

			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
				window.close();
			if (event.type == Event::Resized)
				view = getLetterboxView(view, event.size.width, event.size.height);

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Tilde)
				{
					if (debugMode)
						debugMode = 0;
					else
						debugMode = 1;

					cout << "Debug Mode is: " << debugMode << endl;
				}
			}

		}
		//

		keyBindings(event, player, allied_missiles, deltaTime, Time_between_fire);

		////Colliding

		//Coliding ememy - allied missilies
		for (int i = 0; i < enemies.size(); i++)
		{
			Vertex_Object* obj1 = enemies[i];
			for (int j = 0; j < allied_missiles.size(); j++)
			{
				Vertex_Object* obj2 = &allied_missiles[j];
				if (gamePhysics.checkCollision(obj1, obj2))
				{
					swap(allied_missiles[j], allied_missiles[allied_missiles.size() - 1]);
					allied_missiles.pop_back();

					enemies[i]->getDamage(10, Color::Red);
					if (enemies[i]->health < 0)
					{
						swap(enemies[i], enemies[enemies.size() - 1]);
						enemies.pop_back();
					}


				}

			}
		}
		//

		//Coliding player - enemy missilies
		for (int i = 0; i < enemy_missiles.size(); i++)
		{
			Vertex_Object* obj2 = &enemy_missiles[i];
			if (gamePhysics.checkCollision(&player, obj2))
			{
				swap(enemy_missiles[i], enemy_missiles[enemy_missiles.size() - 1]);
				enemy_missiles.pop_back();

				player.getDamage(10, Color::Red);
				if (player.health < 0)
				{
					cout << "GAME OVER" << endl;
					//GameOver = true;
				}
			}

		}
		//

		//Coliding player - enemy
		for (int i = 0; i < enemies.size(); i++)
		{
			Vertex_Object* obj2 = enemies[i];
			if (gamePhysics.checkCollision(&player, obj2))
			{
				swap(enemies[i], enemies[enemies.size() - 1]);
				enemies.pop_back();

				player.getDamage(50, Color::Red);
				if (player.health < 0)
				{
					cout << "GAME OVER" << endl;
					//GameOver = true;
				}
			}

		}
		//

		////

		//Destroing enemies out of view;
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i]->getLeft_down_corner().y > view.getSize().y)
			{
				swap(enemies[i], enemies[enemies.size() - 1]);
				enemies.pop_back();
			}
		}
		//


		//Destroing missiles out of view
		for (int i = 0; i < allied_missiles.size(); i++)
		{
			allied_missiles[i].move(deltaTime);
			if (allied_missiles[i].getPosition().y < -100 || allied_missiles[i].getPosition().y >(view.getSize().y + 100))
			{
				swap(allied_missiles[i], allied_missiles[allied_missiles.size() - 1]);
				allied_missiles.pop_back();
			}
		}

		for (int i = 0; i < enemy_missiles.size(); i++)
		{
			enemy_missiles[i].move(deltaTime);
			if (enemy_missiles[i].getPosition().y < -100 || enemy_missiles[i].getPosition().y >(view.getSize().y + 100))
			{
				swap(enemy_missiles[i], enemy_missiles[enemy_missiles.size() - 1]);
				enemy_missiles.pop_back();
			}
		}
		//

		//Is the player outside the window 
		if (player.getPosition().x > view.getSize().x + player.getLeft_down_corner().x)
		{
			player.setPosition(Vector2f(0 - player.getLeft_down_corner().x, player.getPosition().y));
		}
		else if (player.getPosition().x + player.getLeft_down_corner().x < 0)
		{
			player.setPosition(Vector2f(view.getSize().x + player.getLeft_down_corner().x, player.getPosition().y));
		}

		if (player.getPosition().y - player.getLeft_down_corner().y > view.getSize().y + player.getLeft_down_corner().y)
		{
			player.setPosition(Vector2f(player.getPosition().x, 0 - player.getLeft_down_corner().y));
		}
		else if (player.getPosition().y + player.getLeft_down_corner().y < 0)
		{
			player.setPosition(Vector2f(player.getPosition().x, view.getSize().y + player.getLeft_down_corner().y));
		}

		//Moving objects and AI

		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->AI(deltaTime, enemy_missiles, player.getCenter());
		}

		//player
		player.move(deltaTime);
		player.back2color(deltaTime);
		//

		//Lasers:
		for (int i = 0; i < allied_missiles.size(); i++)
			allied_missiles[i].move(deltaTime);
		for (int i = 0; i < enemy_missiles.size(); i++)
			enemy_missiles[i].move(deltaTime);
		//


		//


		//fps metter

		Text fps("PH", openSans);
		if (fps_bool)
		{
			//FPS count and convert
			string fps_string;
			stringstream ss;
			if (deltaTime.asMicroseconds() != 0)
				ss << 1000000 / deltaTime.asMicroseconds(); //Counting Frames and converting them from int to string
			else
				ss << 0;
			fps_string = ss.str();
			//

			fps.setString(fps_string);
			fps.setCharacterSize(30);
			fps.setFillColor(Color::Green);
			fps.setPosition(Vector2f(0, 0));
		}
		//

		//Window
		window.clear(Color::Black);
		window.setView(view);
		//

		//Background
		background.move(deltaTime);
		background.draw(window);
		//

		//Drawing Objects

		player.draw(window);

		for (int i = 0; i < enemies.size(); i++) //Drawig enemy; Type -  enemies
			enemies[i]->draw(window);

		for (int i = 0; i < allied_missiles.size(); i++)	//Drawing allied_missiles
			allied_missiles[i].draw(window);

		for (int i = 0; i < enemy_missiles.size(); i++)	//Drawing enemy_misi
			enemy_missiles[i].draw(window);


		//Drawing debug objects (like colisions, or checking circles)

		if (debugMode)
		{
			window.draw(fps);
			player.drawDebug(window);

			for (int i = 0; i < enemies.size(); i++) //Drawig enemy; Type -  enemies
				enemies[i]->drawDebug(window);

			for (int i = 0; i < allied_missiles.size(); i++)
				allied_missiles[i].drawDebug(window);
		}

		window.display();

	}
}

void keyBindings(Event& event, player_object& player, vector <laser_object>& missiles, Time& deltaTime, Clock& time_between_fire)
{
	//Movement
	Vector2f direction_temp = Vector2f(0, 0);

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		direction_temp.x += -1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		direction_temp.x += 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		direction_temp.y += -1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		direction_temp.y += 1;
	}

	//cout << direction_temp.x << " , " << direction_temp.y << endl;
	player.accelerate(direction_temp, deltaTime);

	//Firement

	if (Keyboard::isKeyPressed(Keyboard::Numpad0))
	{
		if (time_between_fire.getElapsedTime().asMilliseconds() > 200)
		{
			time_between_fire.restart();
			missiles.push_back(laser_object(10, 35, Color::Red, 50, -1));
			//missiles.push_back(laser_object(10, 35, Color::Red, 50, -1));
			int i = missiles.size() - 1;
			Vector2f temp_fire_point = player.getFirePoint();
			missiles[i].setPosition(Vector2f(temp_fire_point.x, temp_fire_point.y - 30));
			//missiles[i].setPosition(player.getCenter());
			//cout << "PIU!" << endl;
		}
	}

}

View getLetterboxView(View view, int windowWidth, int windowHeight) {

	// Compares the aspect ratio of the window to the aspect ratio of the view,
	// and sets the view's viewport accordingly in order to archieve a letterbox effect.
	// A new view (with a new viewport set) is returned.

	float windowRatio = windowWidth / (float)windowHeight;
	float viewRatio = view.getSize().x / (float)view.getSize().y;
	float sizeX = 1;
	float sizeY = 1;
	float posX = 0;
	float posY = 0;

	bool horizontalSpacing = true;
	if (windowRatio < viewRatio)
		horizontalSpacing = false;

	// If horizontalSpacing is true, the black bars will appear on the left and right side.
	// Otherwise, the black bars will appear on the top and bottom.

	if (horizontalSpacing)
	{
		sizeX = viewRatio / windowRatio;
		posX = (1 - sizeX) / 2.f;
	}
	else
	{
		sizeY = windowRatio / viewRatio;
		posY = (1 - sizeY) / 2.f;
	}

	view.setViewport(FloatRect(posX, posY, sizeX, sizeY));

	return view;
}
