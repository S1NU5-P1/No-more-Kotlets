#include "level_loader.h"
#include <iostream>;
#include <sstream>

bool level::IsFileOver(fstream& file)
{
	int actual_position = file.tellg();
	file.seekg(0, ios::end);
	int file_size = file.tellg();
	file.seekg(actual_position);
	if (actual_position < file_size - 5)
		return true;
	else
		return false;
}

level_loader::level_loader(string path, bool& error_handle)
{
	level_path_container_file.open(path, ios::in);
	lvl = new level("data\placeholder", error_handle);

	if (!level_path_container_file.good())
	{
		cout << "Level container file is corrupted or doesn't exist." << endl;
		error_handle = 1;
		return;
	}

	string level_path;

	while (getline(level_path_container_file, level_path))
	{
		level_paths.push_back(level_path);
	}

	level_path_container_file.close();
}


void level_loader::load_level(int level_number, bool& error_handle)
{
	if (level_number > level_paths.size())
	{
		cout << "Level number " << level_number << " path is corrupted or doesn't exist." << endl;
		error_handle = 1;
		return;
	}

	delete lvl;
	lvl = new level(level_paths[level_number], error_handle);
}

void level_loader::checkLevelEvent(Time deltaTime, vector<enemy_object*>& enemies)
{
	lvl->checkLevelEvent(deltaTime, enemies);
}

void level_loader::showLoadedData()
{
	lvl->showLoadedData();
}

level::level(string lv_path, bool& error_handle)
{
	time = Time::Zero;

	if (lv_path == "data\placeholder")
	{
		return;
	}

	fstream level_file;
	level_file.open(lv_path, ios::in);
	if (!level_file.good())
	{
		cout << "File: " << lv_path << " is corrupted or doesn't exist." << endl;
		error_handle = 1;
		return;
	}

	string line;

	unsigned int t = 0;
	unsigned short id = 0;
	Vector2f position;

	int i = 0;
	while (IsFileOver(level_file))
	{
		i++;
		level_file >> t >> id >> position.x >> position.y;
		if (!level_file.good())
		{
			cout << "Level file is corupted." << endl;
			cout << "Line: " << i << endl;
			cout << "Atributes: " << t << " " << id << " " << position.x << " " << position.y << endl;
			cout << "Position: " << level_file.tellg() << endl;
			error_handle = 1;
			level_file.close();
			return;
		}
		level_s_events.push_back(level_event(t, id, position));
	}
	cout << "Position: " << level_file.tellg() << endl;
	level_file.close();

}

void level::checkLevelEvent(Time deltaTime, vector<enemy_object*>& enemies)
{
	time += deltaTime;
	//cout << "Time: " << time.asSeconds() << endl;
	while (!level_s_events.empty()) // poprawic
	{
		if (floor(time.asMilliseconds()) >= level_s_events.begin()->time)
		{
			level_s_events.begin()->doEvent(enemies);
			level_s_events.pop_front();
		}
		else
		{
			break;
		}
		
	}
}

void level::showLoadedData()
{
	for (int i = 0; i < level_s_events.size(); i++)
	{
		cout << i + 1 << ")" << endl;
		level_s_events[i].showLoadedData();
	}
}

level_event::level_event(int t, int id, Vector2f pos)
{
	time = t;
	enemy_id = id;
	position = pos;
}

void level_event::showLoadedData()
{
	cout << "time = " << time << endl;
	cout << "enemy_id = " << enemy_id << endl;
	cout << "position: (" << position.x << "," << position.y << ")" << endl;
}

void level_event::doEvent(vector<enemy_object*>& enemies)
{
	const map <int, enemy_object*> enemies_template
	{
		{0, new fighter_enemy()},
		{1, new special_fighter_enemy()}
	};
	const map <int, int> enemies_scale
	{
		{0, 5},
		{1, 5}
	};

	enemies.push_back(enemies_template.at(enemy_id));
	enemies.back()->setScale(enemies_scale.at(enemy_id));
	enemies.back()->setPosition(position);
}
