#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	rng(std::random_device{}()),
	xDist(5, Graphics::ScreenWidth - 5), // 5 is the particles radius, if you want to change it then change it by hand here too
	yDist(5, Graphics::ScreenHeight - 5),
	vDist(-4, 4)
{
	attractor.Init(Vec2(float(Graphics::ScreenWidth / 2), float(Graphics::ScreenHeight / 2)), Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f), 100.0f);

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
		for (int j = 0; j < nParticles; j++)
		{
			if (particle[i].collision != true && i != j)
			{
				particle[i].CollisionWithAnotherParticle(particle[j]);
			}
		}

		if (particle[i].collision != true)
		{
			attractor.CollisionWithAnotherParticle(particle[i]);
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
