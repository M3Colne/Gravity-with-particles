#include "Particle.h"
#include <cmath>

void Particle::Init(Vec2 in_pos, Vec2 in_vel)
{
	pos = in_pos;
	vel = in_vel;
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
