#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	rng(std::random_device{}()),
	xDist(5, Graphics::ScreenWidth - 5), // 5 is the particles radius, if you want to change it then change it by hand here too
	yDist(5, Graphics::ScreenHeight - 5),
	vDist(-4, 4),
	attractor(Vec2(float(Graphics::ScreenWidth / 2), float(Graphics::ScreenHeight / 2)), Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f), 100.0f)
{
	for (int i = 0; i < 20; i++)
	{
		particle.push_back(Particle(Vec2(float(xDist(rng)), float(yDist(rng))), Vec2(float(vDist(rng)), float(vDist(rng))), Vec2(0.0f, 0.0f), 10.0f));
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
	for (Particle& i : particle)
	{
		for (Particle& j : particle)
		{
			if (i != j)
			{
				i.CollisionWithAnotherParticle(j);
			}
		}

		attractor.CollisionWithAnotherParticle(i);
	}
	//Collision

	//Collision Killing
	particle.erase(std::remove_if(particle.begin(), particle.end(), [](Particle& p) {
		return p.collision;
	}), particle.end());
	//Collision Killing

	//Update
	for (Particle& i : particle)
	{
		i.Update();
	}
	attractor.Update(); //This function basically does nothing because the attractor particle doesn't move
	//Update

	//Gravity
	for (Particle& i : particle)
	{
		i.Attracted(attractor);
	}
	//Gravity
}

void Game::ComposeFrame()
{
	for (Particle& i : particle)
	{
		i.Draw(gfx);
	}
	attractor.Draw(gfx);
}
