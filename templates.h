#include <SFML\Graphics.hpp>


#ifndef templates_h
#define templates_h

using namespace std;
using namespace sf;

vector <Vector2f> player_Template
{
	Vector2f(14, 0), 
	Vector2f(15, 0),
	Vector2f(16, 2),
	Vector2f(17, 12),
	Vector2f(17, 24),

	Vector2f(17, 23),
	Vector2f(18, 24),
	Vector2f(20, 24),
	Vector2f(21, 23),
	Vector2f(21, 17),
	Vector2f(21, 22),
	Vector2f(27, 24),
	Vector2f(27, 19),
	Vector2f(27, 24),
	Vector2f(28, 25),
	Vector2f(29, 24),
	Vector2f(29, 19),
	Vector2f(28, 18),
	Vector2f(28, 14),
	Vector2f(28, 18),
	Vector2f(27, 19),
	Vector2f(21, 17),
	Vector2f(21, 16),
	Vector2f(20, 15),
	Vector2f(18, 15),
	Vector2f(17, 16),

	Vector2f(16, 16),
	Vector2f(16, 18),
	Vector2f(15, 19),
	Vector2f(14, 19),
	Vector2f(13, 18),
	Vector2f(13, 16),
	Vector2f(12, 16),
	Vector2f(13, 16),
	Vector2f(14, 10),
	Vector2f(15, 10),
	Vector2f(16, 16),

	Vector2f(17, 16),
	Vector2f(17, 24),
	Vector2f(16, 25),
	Vector2f(13, 25),
	Vector2f(12, 24),
	Vector2f(12, 12),

	Vector2f(12, 23),
	Vector2f(11, 24),
	Vector2f(9, 24),
	Vector2f(8, 23),
	Vector2f(8, 17),
	Vector2f(8, 22),
	Vector2f(2, 24),
	Vector2f(2, 19),
	Vector2f(2, 24),
	Vector2f(1, 25),
	Vector2f(0, 24),
	Vector2f(0, 19),
	Vector2f(1, 18),
	Vector2f(1, 14),
	Vector2f(1, 18),
	Vector2f(2, 19),
	Vector2f(8, 17),
	Vector2f(8, 16),
	Vector2f(9, 15),
	Vector2f(11, 15),
	Vector2f(12, 16),
	
	Vector2f(12, 12),
	Vector2f(13, 2),

	Vector2f(14, 0)
};

vector <Vector2f> player_Collision_Template
{
	Vector2f(14, 0),
	Vector2f(15, 0),
	Vector2f(16, 2),
	Vector2f(17, 12),
	Vector2f(20, 15),
	Vector2f(21, 16),
	Vector2f(21, 17),
	Vector2f(27, 19),
	Vector2f(29, 19),
	Vector2f(29, 24),
	Vector2f(27, 24),
	Vector2f(21, 22),
	Vector2f(21, 23),
	Vector2f(20, 24),
	Vector2f(16, 25),
	Vector2f(13, 25),
	Vector2f(9, 24),
	Vector2f(8, 23),
	Vector2f(8, 22),
	Vector2f(2, 24),
	Vector2f(0, 24),
	Vector2f(0, 19),
	Vector2f(2, 19),
	Vector2f(8, 17),
	Vector2f(8, 16),
	Vector2f(9, 15),
	Vector2f(12, 12),
	Vector2f(13, 2)
};

vector <Vector2f> player_fire_points
{
	Vector2f(1,14), //0
	Vector2f(28,14)  //1
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

vector <Vector2f> fighter_fire_points
{
	Vector2f(5,6)
};

#endif