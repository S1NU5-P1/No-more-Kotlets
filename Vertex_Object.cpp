#include "Vertex_Object.h"
#include "templates.h"

#include <iostream>

using namespace std;
using namespace sf;

//Vertex_Object////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Private Functions

void Vertex_Object::findCenter()
{
	float x_max = collision_template[0].x;
	float y_max = collision_template[0].y;

	for (int i = 1; i < collision_template.size(); i++)
	{
		if (x_max < collision_template[i].x)
		{
			x_max = collision_template[i].x;
		}

		if (y_max < collision_template[i].y)
		{
			y_max = collision_template[i].y;
		}
	}

	center = Vector2f(x_max / 2, y_max / 2);
	left_down_corner = Vector2f(x_max, y_max);
	//cout << center.x << "," << center.y << endl;
}

void Vertex_Object::findRadious()
{
	radious = 0;
	float temp_rad = 0;
	for (int i = 0; i < collision.getVertexCount(); i++)
	{
		temp_rad = sqrt(pow(center.x - collision_template[i].x, 2) + pow(center.y - collision_template[i].y, 2)) + 1;
		//cout << center.x << " - " << collision_template[i].x << " | " << center.y << " - " << collision_template[i].y << " || " << temp_rad << endl;
		if (temp_rad > radious)
		{
			radious = temp_rad;
		}
	}
	collision_radious = radious;
}

void Vertex_Object::vertexUpdate()
{
	for (int i = 0; i < object_template.size(); i++)
	{
		object[i].position.x = (object_template[i].x * size) + position.x;
		object[i].position.y = (object_template[i].y * size) + position.y;
	}

	for (int i = 0; i < collision_template.size(); i++)
	{
		collision[i].position.x = (collision_template[i].x * size) + position.x;
		collision[i].position.y = (collision_template[i].y * size) + position.y;
	}

	centerUpdate();
}

void Vertex_Object::centerUpdate()
{
	collision_center.x = (center.x * size) + position.x;
	collision_center.y = (center.y * size) + position.y;
}

void Vertex_Object::radiusUpdate()
{
	collision_radious = radious * size;
}

//Constructors

Vertex_Object::Vertex_Object()
{
	size = 1;
	collision_radious = 1;
	position = Vector2f(0, 0);

	object_template.push_back(Vector2f(0, 0));
	object.append(Vertex(Vector2f(0, 0)));

	collision_template.push_back(Vector2f(0, 0));
	collision.append(Vertex(Vector2f(0, 0), Color::Red));
	center = Vector2f(0, 0);

	object.setPrimitiveType(PrimitiveType::LineStrip);
	collision.setPrimitiveType(PrimitiveType::LineStrip);

	collision[0].color = Color::Red;
	
	def_color = Color::White;
}

Vertex_Object::Vertex_Object(vector <Vector2f> obj, vector <Vector2f> col, Color color)
{
	size = 1;

	position = Vector2f(0, 0);

	object_template = obj;
	collision_template = col;


	object.resize(object_template.size());
	collision.resize(collision_template.size());

	def_color = color;

	vertexUpdate();

	findCenter();

	findRadious();

	object.setPrimitiveType(PrimitiveType::LineStrip);
	collision.setPrimitiveType(PrimitiveType::LineStrip);

	for (int i = 0; i < object_template.size(); i++)
	{
		object[i].color = color;
	}

	for (int i = 0; i < collision_template.size(); i++)
	{
		collision[i].color = Color::Red;
	}
}

//Public Funcions

void Vertex_Object::setScale(float k)
{
	size = k;
	vertexUpdate();
	radiusUpdate();
}

void Vertex_Object::setColor(Color color)
{
	for (int i = 0; i < object.getVertexCount(); i++)
	{
		object[i].color = color;
	}
}

void Vertex_Object::setPosition(Vector2f position_vector)
{
	position = position_vector;
	vertexUpdate();
}

void Vertex_Object::move(Vector2f moving_vector)
{
	position.x += moving_vector.x;
	position.y += moving_vector.y;
	vertexUpdate();
}

float Vertex_Object::getRadious()
{
	return collision_radious;
}

Vector2f Vertex_Object::getCenter()
{
	return collision_center;
}

VertexArray Vertex_Object::getCollision()
{
	return collision;
}

Vector2f Vertex_Object::getPosition()
{
	return position;
}

Vector2f Vertex_Object::getLeft_down_corner()
{
	return Vector2f((left_down_corner.x * size), (left_down_corner.y * size));
}

void Vertex_Object::draw(RenderWindow& window)
{
	window.draw(object);
}

void Vertex_Object::drawDebug(RenderWindow& window)
{
	VertexArray debugArray(PrimitiveType::Points);

	CircleShape collision_circle;
	collision_circle.setRadius(collision_radious);
	collision_circle.setOutlineColor(Color::Red);
	collision_circle.setPosition(Vector2f(collision_center.x - collision_radious, collision_center.y - collision_radious));
	collision_circle.setFillColor(Color::Transparent);
	collision_circle.setOutlineThickness(2);

	debugArray.append(Vertex(collision_center, Color::Yellow));
	debugArray.append(Vertex(position, Color::Blue));
	window.draw(debugArray);
	window.draw(collision_circle);
	window.draw(collision);
}

void Vertex_Object::getDamage(int howMuch)
{
	cout << "OOF!" << endl;
}

//Player////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void player_object::update()
{
	for (int i = 0; i < fire_points.size(); i++)
	{
		fire_points[i].x = (fire_points_template[i].x * size) + position.x;
		fire_points[i].y = (fire_points_template[i].y * size) + position.y;
	}
}

inline player_object::player_object()
	:Vertex_Object(player_Template, player_Collision_Template, Color::White)
{
	health = 10;
	strength = 10;
	acceleration = 10;
	deceleration = 10;
	target_speed = 10;
	speed = Vector2f(0, 0);
	isColliding = false;

	fire_points_template = player_fire_points;
	fire_points = fire_points_template;
	which_fire_point = 0;

	update();
}

player_object::player_object(int hp, int str, float aacceleration, float adeceleration, float vmax)
	:Vertex_Object(player_Template, player_Collision_Template, Color::White)
{
	health = hp;
	strength = str;
	acceleration = aacceleration;
	deceleration = adeceleration;
	target_speed = vmax;

	speed = Vector2f(0, 0);
	isColliding = false;

	fire_points_template = player_fire_points;
	fire_points = fire_points_template;
	which_fire_point = 0;

	update();
}

void player_object::accelerate(Vector2f direction, Time deltaTime)
{

	if (fabs(speed.x) < target_speed || !((direction.x * speed.x) > 0))
	{
		speed.x += direction.x * acceleration * deltaTime.asMilliseconds() / 100;
	}

	if (fabs(speed.y) < target_speed || !((direction.y * speed.y) > 0))
	{
		speed.y += direction.y * acceleration * deltaTime.asMilliseconds() / 100;
	}
	//cout << "fabs(speed.y) < target_speed / 1,41: " << (fabs(speed.y) < (target_speed / 1, 41)) << " fabs(speed.y) = " << fabs(speed.y) << " !(direction.y * speed.y): " << !((direction.y * speed.y) > 0 ) << endl;
	key_pressed = direction;
}

void player_object::move(Time deltaTime)
{
	if (isColliding)
	{
		speed.x = -speed.x;
		speed.y = -speed.y;
	}

	if (speed.x != 0 && key_pressed.x == 0)
	{
		if (speed.x > 0 && key_pressed.x != 1)
			speed.x -= deceleration * deltaTime.asMilliseconds() / 100;
		else if (speed.x < 0 && key_pressed.x != -1)
			speed.x += deceleration * deltaTime.asMilliseconds() / 100;
		if (abs(speed.x) < (deceleration * deltaTime.asMilliseconds() / 100))
			speed.x /= 2;
		else if (abs(speed.x) < 2)
			speed.x = 0;
	}

	if (speed.y != 0 && key_pressed.y == 0)
	{
		if (speed.y > 0 && key_pressed.y != 1)
			speed.y -= deceleration * deltaTime.asMilliseconds() / 100;
		else if (speed.y < 0 && key_pressed.y != -1)
			speed.y += deceleration * deltaTime.asMilliseconds() / 100;
		if (abs(speed.y) < (deceleration * deltaTime.asMilliseconds() / 100))
			speed.y /= 2;
		else if (abs(speed.y) < 1)
			speed.y = 0;
	}

	Vector2f temp;
	temp.x = speed.x * deltaTime.asMilliseconds() / 100;
	temp.y = speed.y * deltaTime.asMilliseconds() / 100;
	Vertex_Object::move(temp);

	update();
}

void player_object::setPosition(Vector2f position_vector)
{
	Vertex_Object::setPosition(position_vector);
	update();
}

void player_object::setScale(float k)
{
	Vertex_Object::setScale(k);
	update();
}

Vector2f player_object::getFirePoint()
{
	which_fire_point++;
	if (which_fire_point >= fire_points.size())
	{
		which_fire_point = 0;
	}
	return fire_points[which_fire_point];
}

//Laser Object//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Vector2f> laser_object::makeTemplate(float length)
{
	vector<Vector2f> temp;

	temp.push_back(Vector2f(0, 0));
	temp.push_back(Vector2f(0, length));
	temp.push_back(Vector2f(1, length));
	temp.push_back(Vector2f(1, 0));

	return temp;
}

laser_object::laser_object()
	:Vertex_Object(makeTemplate(10), makeTemplate(10), Color::Green)
{
	damage = 10;
	speed = 50;
	direction = 1;

}

laser_object::laser_object(int dm, float length, Color color, float v, int dir)
	:Vertex_Object(makeTemplate(length), makeTemplate(length), color)
{
	damage = dm;
	speed = v;
	direction = dir;
	//cout << object[0].position.x << " , " << object[0].position.y << " || " << object[1].position.x << " , " << object[1].position.y << endl;
}

void laser_object::move(Time deltaTime)
{
	Vector2f temp;
	temp.y = speed * direction * deltaTime.asMilliseconds() / 100;
	temp.x = 0;
	Vertex_Object::move(temp);

}

Vector2f laser_object::getPosition()
{
	return position;
}

//Enemy Object/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void enemy_object::update()
{
	for (int i = 0; i < fire_points.size(); i++)
	{
		fire_points[i].x = (fire_points_template[i].x * size) + position.x;
		fire_points[i].y = (fire_points_template[i].y * size) + position.y;
	}
}

inline enemy_object::enemy_object()
	:Vertex_Object(player_Template, player_Collision_Template, Color::White)
{
	health = 10;
	strength = 10;
	acceleration = 10;
	deceleration = 10;
	target_speed = 10;
	speed = Vector2f(0, 0);
	isColliding = false;

	fire_points_template = player_fire_points;
	fire_points = fire_points_template;
	which_fire_point = 0;

	update();
}

enemy_object::enemy_object(vector <Vector2f> obj, vector <Vector2f> col, Color color, int hp, int str, float aacceleration, float adeceleration, float vmax)
	:Vertex_Object(obj, col, color)
{
	health = hp;
	strength = str;
	acceleration = aacceleration;
	deceleration = adeceleration;
	target_speed = vmax;

	speed = Vector2f(0, 0);
	isColliding = false;

	fire_points_template = player_fire_points;
	fire_points = fire_points_template;
	which_fire_point = 0;

	update();
}

void enemy_object::accelerate(Vector2f direction, Time deltaTime)
{

	if (fabs(speed.x) < target_speed || !((direction.x * speed.x) > 0))
	{
		speed.x += direction.x * acceleration * deltaTime.asMilliseconds() / 100;
	}

	if (fabs(speed.y) < target_speed || !((direction.y * speed.y) > 0))
	{
		speed.y += direction.y * acceleration * deltaTime.asMilliseconds() / 100;
	}
	//cout << "fabs(speed.y) < target_speed / 1,41: " << (fabs(speed.y) < (target_speed / 1, 41)) << " fabs(speed.y) = " << fabs(speed.y) << " !(direction.y * speed.y): " << !((direction.y * speed.y) > 0 ) << endl;
	force_vector = direction;
}

void enemy_object::move(Time deltaTime)
{
	if (isColliding)
	{
		speed.x = -speed.x;
		speed.y = -speed.y;
	}

	if (speed.x != 0 && force_vector.x == 0)
	{
		if (speed.x > 0 && force_vector.x != 1)
			speed.x -= deceleration * deltaTime.asMilliseconds() / 100;
		else if (speed.x < 0 && force_vector.x != -1)
			speed.x += deceleration * deltaTime.asMilliseconds() / 100;
		if (abs(speed.x) < (deceleration * deltaTime.asMilliseconds() / 100))
			speed.x /= 2;
		else if (abs(speed.x) < 2)
			speed.x = 0;
	}

	if (speed.y != 0 && force_vector.y == 0)
	{
		if (speed.y > 0 && force_vector.y != 1)
			speed.y -= deceleration * deltaTime.asMilliseconds() / 100;
		else if (speed.y < 0 && force_vector.y != -1)
			speed.y += deceleration * deltaTime.asMilliseconds() / 100;
		if (abs(speed.y) < (deceleration * deltaTime.asMilliseconds() / 100))
			speed.y /= 2;
		else if (abs(speed.y) < 1)
			speed.y = 0;
	}

	Vector2f temp;
	temp.x = speed.x * deltaTime.asMilliseconds() / 100;
	temp.y = speed.y * deltaTime.asMilliseconds() / 100;
	Vertex_Object::move(temp);

	update();
}

void enemy_object::setPosition(Vector2f position_vector)
{
	Vertex_Object::setPosition(position_vector);
	update();
}

void enemy_object::setScale(float k)
{
	Vertex_Object::setScale(k);
	update();
}

Vector2f enemy_object::getFirePoint()
{
	which_fire_point++;
	if (which_fire_point >= fire_points.size())
	{
		which_fire_point = 0;
	}
	return fire_points[which_fire_point];
}

void enemy_object::getDamage(int damage, Color color)
{
	health -= damage;
	setColor(color);
	color_time = 0;
}

void enemy_object::back2color()
{
	if (color_time > 1)
		setColor(Vertex_Object::def_color);
}

fighter_enemy::fighter_enemy()
	:enemy_object(fighter_template, fighter_Collision_template, Color(180,150,150,255), 20, 10, 10, 10, 20)
{

}

void fighter_enemy::AI()
{
	cout << "Work in progress" << endl;
}
