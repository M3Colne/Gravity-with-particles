#include "Particle.h"
#include <cmath>

void Particle::Init(Vec2 in_pos, Vec2 in_vel, Vec2 in_acc, float in_mass)
{
	pos = in_pos;
	vel = in_vel;
	acc = in_acc;
	mass = in_mass;
}

void Particle::Draw(Graphics & gfx)
{
	const float topLeftX = pos.x - Radius;
	const float topLeftY = pos.y - Radius;
	const float diameter = (Radius * 2) + 1;

	for (float y = topLeftY; y < topLeftY + diameter; ++y) {
		for (float x = topLeftX; x < topLeftX + diameter; ++x) {
			const float DistanceSquared = (pow(pos.x - x, 2) + pow(pos.y - y, 2));

			if (DistanceSquared + 0.5f <= pow(Radius, 2)) {
				gfx.PutPixel(int(x), int(y), 255,255,255);
			}
		}
	}
}

void Particle::Update()
{
	vel += acc;
	pos += vel;
	acc *= 0;

	ClampToScreenAndBounce();
}

void Particle::Attracted(Particle target)
{
	Vec2 force = target.pos - pos;

	const float G = 6.67408f;

	const float strenght = G * target.mass * mass / force.GetLengthSq();

	force.NormalizeTo(strenght);

	const float NUMBER = 1 / mass;

	acc += force * NUMBER;
	// I created this variable because there is no operator for / in the vector so I made force * 1 / mass
	//which is the same with force / mass;
}

void Particle::ClampToScreenAndBounce()
{
	if (pos.x + Radius >= Graphics::ScreenWidth)
	{
		pos.x = Graphics::ScreenWidth - Radius - 1;
		vel.x = -vel.x;
	}
	if (pos.x - Radius <= 0)
	{
		pos.x = Radius;
		vel.x = -vel.x;
	}

	if (pos.y + Radius >= Graphics::ScreenHeight)
	{
		pos.y = Graphics::ScreenHeight - Radius - 1;
		vel.y = -vel.y;
	}
	if (pos.y - Radius <= 0)
	{
		pos.y = Radius;
		vel.y = -vel.y;
	}
}
