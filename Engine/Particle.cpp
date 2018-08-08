#include "Particle.h"
#include <cmath>

void Particle::Init(Vec2 in_pos, Vec2 in_vel)
{
	pos = in_pos;
	vel = in_vel;
}

void Particle::Draw(Graphics & gfx)
{
	const int topLeftX = int(pos.x) - Radius;
	const int topLeftY = int(pos.y) - Radius;
	const int diameter = (Radius * 2) + 1;

	for (int y = topLeftY; y < topLeftY + diameter; ++y) {
		for (int x = topLeftX; x < topLeftX + diameter; ++x) {
			const int DistanceSquared = (int)pow(pos.x - x, 2) + (int)pow(pos.y - y, 2);

			if (DistanceSquared <= pow(Radius, 2)) {
				gfx.PutPixel(x, y, 255,255,255);
			}
		}
	}
}
