#pragma once

#include <map>;
#include <string>
#include <functional>
#include "../Controller/IController.h"

class Player
{

public:
	Player();
	
private:
	IController controller;
};