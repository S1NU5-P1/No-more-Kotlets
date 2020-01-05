#include "Vertex_Object.h"
#include "templates.h"

#include <iostream>

using namespace std;
using namespace sf;

//Vertex_Object////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Private Functions

void Vertex_Object::findCenter()
{
	//cout << collision_template.size() << endl;
	float x_max = collision_template.front().x;
	float y_max = collision_template.front().y;

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
	act_color = def_color;
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
	act_color = def_color;

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
	act_color = color;
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

void player_object::getDamage(int damage, Color color)
{
	health -= damage;
	setColor(color);
	color_time = 0;
}

void player_object::back2color(Time deltaTime)
{
	color_time += deltaTime.asMilliseconds();
	if (color_time > 250 && act_color != def_color)
		setColor(Vertex_Object::def_color);
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

vector<Vector2f> laser_object::makeTemplate(float length, Vector2f length_factor)
{
	vector<Vector2f> temp;

	temp.push_back(Vector2f(0, 0));
	temp.push_back(Vector2f(length * length_factor.x, length * length_factor.y));
	temp.push_back(Vector2f(length * length_factor.x + 1, length * length_factor.y));
	temp.push_back(Vector2f(1, 0));
	return temp;
}

laser_object::laser_object()
	:Vertex_Object(makeTemplate(10), makeTemplate(10), Color::Green)
{
	damage = 10;
	speed =  Vector2f(50,50);
	direction = 1;

}

laser_object::laser_object(int dm, float length, Color color, float v, int dir)
	:Vertex_Object(makeTemplate(length), makeTemplate(length), color)
{
	damage = dm;
	speed = Vector2f(0, v);
	direction = dir;
}

laser_object::laser_object(int dm, float length, Color color, float v, Vector2f speed_factor)
	:Vertex_Object(makeTemplate(length, speed_factor), makeTemplate(length, speed_factor), color)
{
	damage = dm;
	speed = Vector2f(v * speed_factor.x, v * speed_factor.y);
	direction = 1;
}

void laser_object::move(Time deltaTime)
{
	Vector2f temp;
	temp.y = speed.y * direction * deltaTime.asMilliseconds() / 100;
	temp.x = speed.x * direction * deltaTime.asMilliseconds() / 100;
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
	acceleration = Vector2f(10, 10);
	deceleration = Vector2f(10, 10);
	target_speed = Vector2f(10, 10);
	speed = Vector2f(0, 0);
	isColliding = false;

	fire_points_template = player_fire_points;
	fire_points = fire_points_template;
	which_fire_point = 0;

	AI_time = 0;
	shoot_time = 0;
	color_time = 0;

	deltaPosition = Vector2f(0, 0);
	direction = Vector2f(1, 1);

	update();
}

enemy_object::enemy_object(vector <Vector2f> obj, vector <Vector2f> col, Color color, int hp, int str, Vector2f aacceleration, Vector2f adeceleration, Vector2f vmax)
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

	AI_time = 0;
	shoot_time = 0;
	color_time = 0;

	deltaPosition = Vector2f(0, 0);
	direction = Vector2f(1,1);
	update();
}

void enemy_object::accelerate(Vector2f direction, Time deltaTime)
{

	if (fabs(speed.x) < target_speed.x || !((direction.x * speed.x) > 0))
	{
		speed.x += direction.x * acceleration.x * deltaTime.asMilliseconds() / 100;
	}

	if (fabs(speed.y) < target_speed.y || !((direction.y * speed.y) > 0))
	{
		speed.y += direction.y * acceleration.x * deltaTime.asMilliseconds() / 100;
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
			speed.x -= deceleration.x * deltaTime.asMilliseconds() / 100;
		else if (speed.x < 0 && force_vector.x != -1)
			speed.x += deceleration.x * deltaTime.asMilliseconds() / 100;
		if (abs(speed.x) < (deceleration.x * deltaTime.asMilliseconds() / 100))
			speed.x /= 2;
		else if (abs(speed.x) < 2)
			speed.x = 0;
	}

	if (speed.y != 0 && force_vector.y == 0)
	{
		if (speed.y > 0 && force_vector.y != 1)
			speed.y -= deceleration.y * deltaTime.asMilliseconds() / 100;
		else if (speed.y < 0 && force_vector.y != -1)
			speed.y += deceleration.y * deltaTime.asMilliseconds() / 100;
		if (abs(speed.y) < (deceleration.y * deltaTime.asMilliseconds() / 100))
			speed.y /= 2;
		else if (abs(speed.y) < 1)
			speed.y = 0;
	}

	Vector2f temp;
	temp.x = speed.x * deltaTime.asMilliseconds() / 100;
	temp.y = speed.y * deltaTime.asMilliseconds() / 100;

	deltaPosition.x += temp.x;
	deltaPosition.y += temp.y;

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

void enemy_object::time_update(Time deltaTime)
{
	AI_time += deltaTime.asMilliseconds();
	shoot_time += deltaTime.asMilliseconds();
	color_time += deltaTime.asMilliseconds();
}

void enemy_object::simpleMovement(Time deltaTime)
{
	accelerate(direction, deltaTime);
	//cout << speed.x << " , " << speed.y << "  |  " << deltaTime.asMilliseconds() <<endl;
	if (deltaPosition.x > 30) direction.x = -1;
	else if (deltaPosition.x < -30) direction.x = 1;
	//cout << deltaPosition.x << " , " << deltaPosition.y << "  |  " << deltaTime.asMilliseconds() << endl;

	back2color();

	move(deltaTime);
}

bool enemy_object::randomShoot(int x, int enemy_count)
{
	return ((rand() % (x * enemy_count)) + 1 == 1);
}

void enemy_object::shoot(vector<laser_object>& enemy_missiles, Vector2f direction)
{
	enemy_missiles.push_back(laser_object(10, 35, Color::Green, 50, direction));
	Vector2f temp_fire_point = getFirePoint();
	enemy_missiles[enemy_missiles.size() - 1].setPosition(Vector2f(temp_fire_point.x, temp_fire_point.y));
	shoot_time = 0;
}

void enemy_object::simple_shoot(Time deltaTime, vector<laser_object>& enemy_missiles, int x, int enemy_count)
{
	if (randomShoot(x,enemy_count) && deltaTime.asMilliseconds() != 0 && shoot_time > 500 && position.y > 0)
	{
		shoot(enemy_missiles, Vector2f(0, 1));
	}
}

void enemy_object::aimed_shoot(Time deltaTime, vector<laser_object>& enemy_missiles, Vector2f player_position, int x, int enemy_count)
{
	if (randomShoot(x, enemy_count) && deltaTime.asMilliseconds() != 0 && shoot_time > 500 && position.y > 0)
	{
		Vector2f delta_position;
		delta_position.x = player_position.x - position.x;
		delta_position.y = player_position.y - position.y;
		float denominator = sqrtf(pow(delta_position.x, 2) + pow(delta_position.y, 2));
		Vector2f speed_factor;
		speed_factor.x = delta_position.x / denominator;
		speed_factor.y = delta_position.y / denominator;

		shoot(enemy_missiles, speed_factor);
	}
}

void enemy_object::back2color()
{
	if (color_time > 250 && act_color != def_color)
		setColor(Vertex_Object::def_color);
}

fighter_enemy::fighter_enemy()
	:enemy_object(fighter_template, fighter_Collision_template, Color(180, 150, 150, 255), 20, 10, Vector2f(10,0.02), Vector2f(10, 0.02), Vector2f(20, 0.2))
{
	fire_points_template = fighter_fire_points;
	fire_points = fighter_fire_points;
}


void fighter_enemy::AI(Time deltaTime, vector<laser_object> &enemy_missiles, Vector2f player_position, int enemy_count)
{
	time_update(deltaTime);
	simpleMovement(deltaTime);
	if(position.y > 0)
	simple_shoot(deltaTime, enemy_missiles, 300, enemy_count);
}

special_fighter_enemy::special_fighter_enemy()
	:enemy_object(fighter_template, fighter_Collision_template, Color::Blue, 20, 10, Vector2f(10, 0.02), Vector2f(10, 0.02), Vector2f(20, 0.2))
{
	fire_points_template = fighter_fire_points;
	fire_points = fighter_fire_points;
}

void special_fighter_enemy::AI(Time deltaTime, vector<laser_object>& enemy_missiles, Vector2f player_position, int enemy_count)
{
	time_update(deltaTime);
	simpleMovement(deltaTime);
	aimed_shoot(deltaTime, enemy_missiles, player_position, 300, enemy_count);
}
