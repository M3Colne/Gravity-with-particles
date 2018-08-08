#pragma once

#include "Vec2.h"
#include "Graphics.h"

class Particle
{
public:
	void Init(Vec2 in_pos, Vec2 in_vel, Vec2 in_acc, float in_mass);
	void Draw(Graphics& gfx);
	void Update();
	void Attracted(Particle target);
	void ClampToScreenAndBounce();
	float Radius = 5.0f; //If u change the radius then you have to change the values in the game.cpp constructor of the minimum value for xDist and yDist
	Vec2 pos;
	Vec2 vel;
	Vec2 acc;
	float mass;
	bool collision = false;
};