#include "Vertex_Object.h"

#ifndef collision_cpp
#define collision_cpp

class physics
{
public:
	bool checkCollision(Vertex_Object* obj1, Vertex_Object* obj2);
	float cross_product(Vector2f X, Vector2f Y, Vector2f Z);
	bool isBelongToStraight(Vector2f X, Vector2f Y, Vector2f Z);
	bool areCrossing(Vector2f A, Vector2f B, Vector2f C, Vector2f D);
};

#endif