#pragma once

#include "Vec2.h"
#include "Graphics.h"

class Particle
{
public:
	void Init(Vec2 in_pos, Vec2 in_vel);
	void Draw(Graphics& gfx);
private:
	Vec2 pos;
	Vec2 vel;
	static constexpr int Radius = 20;
};