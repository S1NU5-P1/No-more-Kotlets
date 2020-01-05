#include "Vertex_Object.h"

#ifndef physics_h
#define physics_h

class physics
{
	float cross_product(Vector2f X, Vector2f Y, Vector2f Z);
	bool isBelongToStraight(Vector2f X, Vector2f Y, Vector2f Z);
	bool areCrossing(Vector2f A, Vector2f B, Vector2f C, Vector2f D);
public:
	physics();
	bool checkCollision(Vertex_Object* obj1, Vertex_Object* obj2);
};

#endif