#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

vector <Vector2f> player_Template
{
	Vector2f(0, 6), //0
	Vector2f(3, 0), //1
	Vector2f(6, 6), //2
	Vector2f(3, 5), //3
	Vector2f(0, 6)  //0
};

vector <Vector2f> player_Collision_Template
{
	Vector2f(0,6), //0
	Vector2f(3,0), //1
	Vector2f(6,6)  //2
};

vector <Vector2f> player_fire_points
{
	Vector2f(0,6), //0
	Vector2f(6,6)  //1
};

vector <Vector2f> fighter_template
{
	Vector2f(2,4),
	Vector2f(2,1),
	Vector2f(1,0),
	Vector2f(0,1),
	Vector2f(0,1),
	Vector2f(0,7),
	Vector2f(1,8),
	Vector2f(2,7),
	Vector2f(2,4),
	Vector2f(1,4),
	Vector2f(3,3),
	Vector2f(4,2),
	//Vector2f(5,2),
	Vector2f(6,2),
	Vector2f(7,3),
	Vector2f(7,4),
	Vector2f(7,5),
	Vector2f(6,6),
	//Vector2f(5,6),
	Vector2f(4,6),
	Vector2f(3,5), Vector2f(1,4), Vector2f(3,5),
	Vector2f(3,3),
	Vector2f(3,4),
	Vector2f(4,4),
	Vector2f(5,3),
	Vector2f(5,2),
	Vector2f(5,3),
	Vector2f(6,4),
	Vector2f(7,4),
	Vector2f(7,3),
	Vector2f(9,4),
	Vector2f(8,4),
	Vector2f(8,1),
	Vector2f(9,0),
	Vector2f(10,1),
	Vector2f(10,7),
	Vector2f(9,8),
	Vector2f(8,7),
	Vector2f(8,4),
	Vector2f(9,4),
	Vector2f(7,5),
	Vector2f(7,4),
	Vector2f(6,4),
	Vector2f(5,5),
	Vector2f(5,6),
	Vector2f(5,5),
	Vector2f(4,4),
};

vector <Vector2f> fighter_Collision_template
{
	Vector2f(0,0),
	Vector2f(2,0),
	Vector2f(4,2),
	Vector2f(6,2),
	Vector2f(9,0),
	Vector2f(10,0),
	Vector2f(10,8),
	Vector2f(9,8),
	Vector2f(6,6),
	Vector2f(4,6),
	Vector2f(1,8),
	Vector2f(0,8)
};