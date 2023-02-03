#include "CAPP.h"


CAPP::CAPP()
{
	isRunning = true;
	pWindow = NULL;
	pRenderer = NULL;
}

int CAPP::OnExecute()
{
	SDL_Event event;
	if (OnInit() == false)
	{
		return -1;
	}
	while (isRunning)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			OnEvent(&event);
		}

		OnLoop();
		OnRender();
	}

}

bool CAPP::OnInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	pWindow = SDL_CreateWindow("PathTracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

	if (pWindow != NULL)
	{
		pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

		m_image.Initialize(1280, 720, pRenderer);


		//
		SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
		SDL_RenderClear(pRenderer);

		m_scene.render(m_image);

		m_image.Display();

		SDL_RenderPresent(pRenderer);
	}
	else
	{
		return false;
	}

	return true;

}

void CAPP::OnEvent(SDL_Event* event)
{
	if (event->type == SDL_QUIT)
	{
		isRunning = false;
	}

}

void CAPP::OnLoop()
{
}

void CAPP::OnRender()
{

	//// set the background color to white
	//SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
	//SDL_RenderClear(pRenderer);

	////render the scene
	//m_scene.render(m_image);

	////display the image
	//m_image.Display();



	//SDL_RenderPresent(pRenderer);
}

void CAPP::OnExit()
{
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	pWindow = NULL;
	SDL_Quit();
}

void CAPP::PrintVector(const vec3& inputVector)
{
	std::cout << inputVector;
}
