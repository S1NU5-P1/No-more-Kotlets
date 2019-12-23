#include <SFML\Graphics.hpp>

#ifndef stellar_background_h
#define stellar_background_h

using namespace std;
using namespace sf;

class stellar_background
{
	unsigned int window_width;
	unsigned int window_height;

	unsigned int stars_count;

	Color star_color;
	Color background_color;
	
	float speed;

	VertexArray stars;
	float* speedTab;
	
	void speedRand();

public:

	int deltaSpeed = 51;

	stellar_background();
	stellar_background(unsigned int w_width, unsigned int w_height, unsigned int s_count, Color s_color, Color b_color, float v);

	~stellar_background();

	void draw(RenderWindow& window);
	void move(Time deltaTime);

	
};

#endif