#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	rng(std::random_device{}()),
	xDist(5, Graphics::ScreenWidth - 5), // 5 is the particles radius, if you want to change it then change it by hand here too
	yDist(5, Graphics::ScreenHeight - 5),
	vDist(-4, 4),
	attractor(Vec2(float(Graphics::ScreenWidth / 2), float(Graphics::ScreenHeight / 2)), Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f), 100.0f)
{
	for (int i = 0; i < 100; i++) //Number of particles
	{
		particles.push_back(Particle(Vec2(float(xDist(rng)), float(yDist(rng))), Vec2(float(vDist(rng)), float(vDist(rng))), Vec2(0.0f, 0.0f), 10.0f));
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
	for (unsigned int i = 0; i < particles.size(); i++)
	{
		attractor.CollisionWithAnotherParticle(particles.at(i));

		for (unsigned int j = 0; j < particles.size(); j++)
		{
			if (i != j)
			{
				particles.at(i).CollisionWithAnotherParticle(particles.at(j));

				if (particles.at(j).collision)
				{
					particles.erase(particles.begin() + j);
				}
			}
		}
	}
	//Collision

	//Update
	for (unsigned int i = 0; i < particles.size(); i++)
	{
		if (particles.at(i).collision != true)
		{
			particles.at(i).Update();
		}
	}
	attractor.Update(); //This function basically does nothing because the attractor particle doesn't move
						//Update

						//Gravity
	for (unsigned int i = 0; i < particles.size(); i++)
	{
		if (particles.at(i).collision != true)
		{
			particles.at(i).Attracted(attractor);
		}
	}
	//Gravity
}

void Game::ComposeFrame()
{
	attractor.Draw(gfx);
	for (unsigned int i = 0; i < particles.size(); i++)
	{
		if (particles.at(i).collision != true)
		{
			particles.at(i).Draw(gfx);
		}
	}
}
