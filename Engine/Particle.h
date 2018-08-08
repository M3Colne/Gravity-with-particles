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
	Vec2 GetVel();
	void SetVel(Vec2 in_vel);
	static float GetRadius();
private:
	Vec2 pos;
	Vec2 vel;
	Vec2 acc;
	float mass;
	static constexpr float Radius = 5.0f;
};