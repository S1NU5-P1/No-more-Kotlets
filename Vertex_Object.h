#include <SFML\Graphics.hpp>

#ifndef Vertex_Object_h
#define Vertex_Object_h

using namespace std;
using namespace sf;

class Vertex_Object
{
protected:
	float size;
	Vector2f position;
	Vector2f left_down_corner;

	vector <Vector2f> object_template;
	VertexArray object;

	vector <Vector2f> collision_template;
	VertexArray collision;
	Vector2f center; // center of Collision polygon (template)
	Vector2f collision_center; // center of Collision polygon (object)

	float radious;
	float collision_radious;
	Color def_color;
	Color act_color;

	void findCenter();
	void findRadious();

	void vertexUpdate();
	void centerUpdate();
	void radiusUpdate();

public:
	Vertex_Object();
	Vertex_Object(vector <Vector2f> obj, vector <Vector2f> col, Color color);

	void setScale(float k);
	void setColor(Color color);
	void setPosition(Vector2f position_vector);
	void move(Vector2f moving_vector);

	float getRadious();
	Vector2f getCenter();
	VertexArray getCollision();
	Vector2f getPosition();
	Vector2f getLeft_down_corner();

	void draw(RenderWindow& window);
	void drawDebug(RenderWindow& window);

	void getDamage(int howMuch);

};

class player_object
	:public Vertex_Object
{
	Vector2f speed;
	float acceleration;
	float deceleration;
	float target_speed;

	Vector2f key_pressed;

	vector <Vector2f> fire_points_template;
	vector <Vector2f> fire_points;
	int which_fire_point;

	float color_time;

	void update();

public:
	int health;
	int strength;


	bool isColliding;

	player_object();
	player_object(int hp, int str, float aacceleration, float adeceleration, float vmax);

	void accelerate(Vector2f direction, Time deltaTime);
	void move(Time deltaTime);
	void setPosition(Vector2f position_vector);
	void setScale(float k);

	void getDamage(int damage, Color color);
	void back2color(Time deltaTime);

	Vector2f getFirePoint();
};

class laser_object
	:public Vertex_Object
{
	Vector2f speed;
	int damage;
	int direction;

	vector <Vector2f> makeTemplate(float length);
	vector <Vector2f> makeTemplate(float length, Vector2f k_length);

public:

	laser_object();
	laser_object(int dm, float length, Color color, float v, int dir);
	laser_object(int dm, float length, Color color, float v, Vector2f speed_factor);

	void move(Time deltaTime);
	Vector2f getPosition();
};

class enemy_object
	:public Vertex_Object
{

protected:
	Vector2f speed;
	Vector2f acceleration;
	Vector2f deceleration;
	Vector2f target_speed;

	Vector2f force_vector;

	vector <Vector2f> fire_points_template;
	vector <Vector2f> fire_points;
	int which_fire_point;

	float color_time;

	void update();

	double AI_time;
	double shoot_time;

	Vector2f deltaPosition;
	Vector2f direction = Vector2f(1,1);

	bool randomShoot(int x, int enemy_count);
	void shoot(vector<laser_object>& enemy_missiles, Vector2f direction);
	
public:
	int health;
	int strength;


	bool isColliding;

	enemy_object();
	enemy_object(vector <Vector2f> obj, vector <Vector2f> col, Color color, int hp, int str, Vector2f aacceleration, Vector2f adeceleration, Vector2f vmax);
	
	void accelerate(Vector2f direction, Time deltaTime);
	void move(Time deltaTime);
	void setPosition(Vector2f position_vector);
	void setScale(float k);

	Vector2f getFirePoint();

	void getDamage(int damage, Color color);

	void time_update(Time deltaTime);

	void simpleMovement(Time deltaTime);

	
	void simple_shoot(Time deltaTime, vector <laser_object>& enemy_missiles, int x, int enemy_count);//x is a denominator of probability (1/x); 
	void aimed_shoot(Time deltaTime, vector <laser_object>& enemy_missiles, Vector2f player_position, int x, int enemy_count);

	void back2color();

	virtual void AI(Time deltaTime, vector <laser_object>& enemy_missiles, Vector2f player_position, int enemy_count) = 0;

};

class fighter_enemy
	:public enemy_object
{
	
public:
	fighter_enemy();

	void AI(Time deltaTime, vector <laser_object> &enemy_missiles, Vector2f player_position, int enemy_count);
};

class special_fighter_enemy
	:public enemy_object
{

public:
	special_fighter_enemy();

	void AI(Time deltaTime, vector <laser_object>& enemy_missiles, Vector2f player_position, int enemy_count);
};

#endif