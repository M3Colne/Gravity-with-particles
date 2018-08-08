#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	attractor.Init(Vec2(float(Graphics::ScreenWidth / 2), float(Graphics::ScreenHeight / 2)), Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f), 1.0f);
	particle.Init(Vec2(float(Graphics::ScreenWidth / 2), float(Graphics::ScreenHeight / 2 - 100)), Vec2(-1.0f, 1.5f), Vec2(0.0f, 0.0f), 1.0f);
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
	particle.Update();
	attractor.Update(); //This function basically does nothing because the attractor particle doesn't move
	particle.Attracted(attractor);
}

void Game::ComposeFrame()
{
	attractor.Draw(gfx);
	particle.Draw(gfx);
}
