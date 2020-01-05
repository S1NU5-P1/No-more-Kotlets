#include <SFML\Graphics.hpp>
#include <math.h>
#include "physics.h"
#include "Vertex_Object.h"

using namespace std;
using namespace sf;

physics::physics()
{
}

bool physics::checkCollision(Vertex_Object* obj1, Vertex_Object* obj2)
{
	float distance = sqrt(pow(obj2->getCenter().x - obj1->getCenter().x, 2) + pow(obj2->getCenter().y - obj1->getCenter().y, 2)); // distance between two centers of objects

	if (obj1->getRadious() + obj2->getRadious() < distance) // Circles of Collision activator don't cross
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

				if ((i + int(1)) == obj1Array.getVertexCount())
					k = 0;
				else
					k = i + 1;

				if ((j + int(1)) == obj2Array.getVertexCount())
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

float physics::cross_product(Vector2f X, Vector2f Y, Vector2f Z)
{
	float x1 = Z.x - X.x, y1 = Z.y - X.y;
	float x2 = Y.x - X.x, y2 = Y.y - X.y;
	return x1 * y2 - x2 * y1;
}
bool physics::isBelongToStraight(Vector2f X, Vector2f Y, Vector2f Z)
{
	return min(X.x, Y.x) <= Z.x && Z.x <= max(X.x, Y.x)
		&& min(X.y, Y.y) <= Z.y && Z.y <= max(X.y, Y.y);
}
bool physics::areCrossing(Vector2f A, Vector2f B, Vector2f C, Vector2f D)
{
	float v1 = cross_product(C, D, A),
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