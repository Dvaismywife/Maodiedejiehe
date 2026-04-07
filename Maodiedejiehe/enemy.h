#pragma once
#include"skills.h"
#include<easyx.h>
#include<Windows.h>
class enemy {
	char name[50];
	int hp;
	int x, y;
	IMAGE* skin;
	enemy() :hp(50), x(0), y(0), skin(nullptr) {};
};