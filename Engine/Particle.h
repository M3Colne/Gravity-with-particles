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
private:
	Vec2 pos;
	Vec2 vel;
	Vec2 acc;
	float mass;
	static constexpr float Radius = 5.0f;
};