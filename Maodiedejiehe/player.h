#pragma once
#include<easyx.h>
#include"skills.h"
struct player {
	char name[50];
	int hp;
	IMAGE *skin;
	int x, y;
	player() :x(0), y(0), skin(nullptr),hp(100) {};
};