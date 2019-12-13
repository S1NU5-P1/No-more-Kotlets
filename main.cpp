#include <SFML\Graphics.hpp>
#include <iostream>
#include <sstream>
#include <math.h>
#include "stellar_background.h"
#include "Vertex_Object.h"


using namespace std;
using namespace sf;

View getLetterboxView(View view, int windowWidth, int windowHeight);

void game(RenderWindow& window, View& view); // True game function
void keyBindings(Event& event, player_object& player, vector <laser_object>& missiles, Time& deltaTime, Clock& time_between_fire);
bool checkCollision(Vertex_Object* obj1, Vertex_Object* obj2);

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
	vector <fighter_enemy> fighters;

	for (size_t i = 0; i < 15; i++)
	{
		fighters.push_back(fighter_enemy());
		Vector2f position;
		position.x = 45 + 80 * (i % 5);
		position.y = 30 + 80 * ceil(i / 5);
		fighters[i].setPosition(position);
		fighters[i].setScale(5);
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

		//Colliding
		
		//Coliding ememy - missilies
		for (int i = 0; i < fighters.size(); i++)
		{
			Vertex_Object* obj1 = &fighters[i];
			for (int j = 0; j < allied_missiles.size(); j++)
			{
				Vertex_Object* obj2 = &allied_missiles[j];
				if (checkCollision(obj1, obj2))
				{
					swap(allied_missiles[j], allied_missiles[allied_missiles.size() - 1]);
					allied_missiles.pop_back();

					swap(fighters[i], fighters[fighters.size() - 1]);
					fighters.pop_back();
				}

			}
		}
		

		
		//}

		//Is the player outside the window 


		if(player.getPosition().x > view.getSize().x + player.getLeft_down_corner().x)
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
	

		//cout << player.getLeft_down_corner().x << " , " << player.getLeft_down_corner().y << endl;
		//

		

		player.move(deltaTime);

		Text fps("PH", openSans);

		//fps metter
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
		//

		//Drawing Objects

		player.draw(window);

		for (int i = 0; i < fighters.size(); i++) //Drawig enemy; Type -  Fighters
			fighters[i].draw(window);

		for (int i = 0; i < allied_missiles.size(); i++)	//Drawing allied_missiles
			allied_missiles[i].draw(window);
		
		

		//Drawing debug objects (like colisions, or checking circles)

		if (debugMode)
		{
			window.draw(fps);
			player.drawDebug(window);
			
			for (int i = 0; i < fighters.size(); i++) //Drawig enemy; Type -  Fighters
				fighters[i].drawDebug(window);

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
			missiles.push_back(laser_object(10, 35, Color::Red, 300, -1));
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

//collision || Transfer to class Phisics
float cross_product(Vector2f X, Vector2f Y, Vector2f Z);
bool isBelongToStraight(Vector2f X, Vector2f Y, Vector2f Z);
bool areCrossing(Vector2f A, Vector2f B, Vector2f C, Vector2f D);

bool checkCollision(Vertex_Object* obj1, Vertex_Object* obj2)
{
	float distance = sqrt(pow(obj2->getCenter().x - obj1->getCenter().x, 2) + pow(obj2->getCenter().y - obj1->getCenter().y, 2)); // distance between two centers of objects

	if (obj1->getRadious() + obj2->getRadious() < distance ) // Circles of Collision activator don't cross
	{
		return false;
	}
	else
	{
		VertexArray obj1Array;
		for (int i = 0; i < obj1->getCollision().getVertexCount(); i++)
		{
			obj1Array.append(obj1->getCollision()[i]);
		}
		VertexArray obj2Array;
		for (int i = 0; i < obj2->getCollision().getVertexCount(); i++)
		{
			obj2Array.append(obj2->getCollision()[i]);
		}

		for (int i = 0; i < obj1Array.getVertexCount(); i++)
		{

			for (int j = 0; j < obj2Array.getVertexCount(); j++)
			{
				int k, l;

				if ((i + 1) == obj1Array.getVertexCount())
					k = 0;
				else
					k = i + 1;

				if ((j + 1) == obj2Array.getVertexCount())
					l = 0;
				else
					l = j + 1;

				if (areCrossing(obj1Array[i].position, obj1Array[k].position, obj2Array[j].position, obj2Array[l].position))
					return true;

			}
		}
		return false;
	}

}

float cross_product(Vector2f X, Vector2f Y, Vector2f Z)
{
	float x1 = Z.x - X.x, y1 = Z.y - X.y;
	float x2 = Y.x - X.x, y2 = Y.y - X.y;
	return x1 * y2 - x2 * y1;
}
bool isBelongToStraight(Vector2f X, Vector2f Y, Vector2f Z)
{
	return min(X.x, Y.x) <= Z.x && Z.x <= max(X.x, Y.x)
		&& min(X.y, Y.y) <= Z.y && Z.y <= max(X.y, Y.y);
}
bool areCrossing(Vector2f A, Vector2f B, Vector2f C, Vector2f D)
{
	int v1 = cross_product(C, D, A),
		v2 = cross_product(C, D, B),
		v3 = cross_product(A, B, C),
		v4 = cross_product(A, B, D);
	if ((v1 > 0 && v2 < 0 || v1 < 0 && v2>0) && (v3 > 0 && v4 < 0 || v3 < 0 && v4>0)) return 1;

	if (v1 == 0 && isBelongToStraight(C, D, A)) return 1;
	if (v2 == 0 && isBelongToStraight(C, D, B)) return 1;
	if (v3 == 0 && isBelongToStraight(A, B, C)) return 1;
	if (v4 == 0 && isBelongToStraight(A, B, D)) return 1;

	return 0;
}

