#include <SFML\Graphics.hpp>
#include <deque>
#include <fstream>
#include "Vertex_Object.h"

using namespace std;
using namespace sf;

#ifndef level_loader_h
#define level_loader_h

class level_event
{

public:
	unsigned int time;
	unsigned short enemy_id;
	Vector2f position;


	level_event(int t, int id,	Vector2f pos);

	void showLoadedData();

	void doEvent(vector <enemy_object*> &enemies);
};

class level
{
	deque <level_event> level_s_events;
	Time time;

	bool IsFileOver(fstream &file);

public:

	level(string lv_path, bool& error_handle);

	void checkLevelEvent(Time deltaTime, vector <enemy_object*> &enemies);
	
	void showLoadedData();
};

class level_loader
{
	fstream level_path_container_file;
	deque <string> level_paths;
	level* lvl;

public:

	level_loader(string path, bool &error_handle);

	void load_level(int level_number, bool &error_handle);

	void checkLevelEvent(Time deltaTime, vector <enemy_object*>& enemies);

	void showLoadedData();

};

#endif