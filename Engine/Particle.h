#pragma once

#include "Vec2.h"
#include "Graphics.h"

class Particle
{
private:
	Vec2 pos;
	Vec2 vel;
	Vec2 acc;
	float radius = 5.0f;
	float mass;
	static int nextId;
	int id;
public:
	Particle(Vec2 in_pos, Vec2 in_vel, Vec2 in_acc, float in_mass);
	bool operator !=(const Particle& rhs);
	void Draw(Graphics& gfx);
	void Update();
	void Attracted(Particle target);
	void ClampToScreenAndBounce();
	void CollisionWithAnotherParticle(Particle& p);
	bool collision = false;
};