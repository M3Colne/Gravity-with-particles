#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	rng(std::random_device{}()),
	xDist(int(Particle::GetRadius()), int(Graphics::ScreenWidth - Particle::GetRadius())),
	yDist(int(Particle::GetRadius()), int(Graphics::ScreenWidth - Particle::GetRadius())),
	vDist(-4.0f, 4.0f)
{
	attractor.Init(Vec2(float(Graphics::ScreenWidth / 2), float(Graphics::ScreenHeight / 2)), Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f), 100.0f);

	for (int i = 0; i < nParticles; i++)
	{
		particle[i].Init(Vec2(float(xDist(rng)), float(yDist(rng))), Vec2(float(vDist(rng)), float(vDist(rng))), Vec2(0.0f, 0.0f), 1.0f);
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
	for (int i = 0; i < nParticles; i++)
	{
		particle[i].Update();

		if (particle[i].GetVel().GetLength() > Friction - 0.1f)
		{
			particle[i].SetVel(particle[i].GetVel().NormalizeTo(particle[i].GetVel().GetLength() - Friction));
		}
	}
	attractor.Update(); //This function basically does nothing because the attractor particle doesn't move
	
	for (int i = 0; i < nParticles; i++)
	{
		particle[i].Attracted(attractor);
	}
}

void Game::ComposeFrame()
{
	attractor.Draw(gfx);
	for (int i = 0; i < nParticles; i++)
	{
		particle[i].Draw(gfx);
	}
}
