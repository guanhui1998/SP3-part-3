#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"
#include <string>

using std::string;

struct GameObject
{
	enum GAMEOBJECT_TYPE
	{
		GO_NONE = 0,
		GO_BALL,

		// Buttons
		GO_PLAY,
		GO_PLAYHOVER,
		GO_MENU,
		GO_MENUHOVER,
		GO_HIGHSCORE,
		GO_HIGHSCOREHOVER,
		GO_EXIT,
		GO_EXITHOVER,
		GO_RESTART,
		GO_RESTARTHOVER,
		GO_OKAYHOVER,
		GO_HELP,
		GO_HELPHOVER,
		GO_RESUME,
		GO_RESUMEHOVER,

		GO_TOTAL, //must be last
	};
	GAMEOBJECT_TYPE type;
	Vector3 pos;
	Vector3 vel;
	Vector3 scale;
    Vector3 normal;
	bool active;
	float mass;
    string name;

	GameObject(GAMEOBJECT_TYPE typeValue = GO_BALL);
    void Init();
    void exit();
	~GameObject();
};

#endif