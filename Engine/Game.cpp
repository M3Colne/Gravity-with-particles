#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	rng(std::random_device{}()),
	xDist(5, 794),
	yDist(5, 594),
	vDist(-4, 4)
{
	attractor.Init(Vec2(float(Graphics::ScreenWidth / 2), float(Graphics::ScreenHeight / 2)), Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f), 70.0f);

	for (int i = 0; i < nParticles; i++)
	{
		particle[i].Init(Vec2(float(xDist(rng)), float(yDist(rng))), Vec2(float(vDist(rng)), float(vDist(rng))), Vec2(0.0f, 0.0f), 10.0f);
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	//Collision
	for (int i = 0; i < nParticles; i++)
	{
		if (particle[i].collision != true)
		{
			Vec2 distanceBetweenAttrAndParticle = attractor.pos - particle[i].pos;

			if (distanceBetweenAttrAndParticle.GetLength() <= attractor.Radius + particle[i].Radius)
			{
				const float PI = 3.141592;
				const float bothSurfaces =
					PI * (attractor.Radius * attractor.Radius) +
					PI * (particle[i].Radius * particle[i].Radius);

				attractor.Radius = float(sqrt(bothSurfaces / PI));
				attractor.mass += particle[i].mass;

				particle[i].collision = true;
			}
		}
	}
	//Collision

	//Update
	for (int i = 0; i < nParticles; i++)
	{
		if (particle[i].collision != true)
		{
			particle[i].Update();
		}
	}
	attractor.Update(); //This function basically does nothing because the attractor particle doesn't move
	//Update

	//Gravity
	for (int i = 0; i < nParticles; i++)
	{
		if (particle[i].collision != true)
		{
			particle[i].Attracted(attractor);
		}
	}
	//Gravity
}

void Game::ComposeFrame()
{
	attractor.Draw(gfx);
	for (int i = 0; i < nParticles; i++)
	{
		if (particle[i].collision != true)
		{
			particle[i].Draw(gfx);
		}
	}
}
