#pragma once

#include <SDL/SDL.h>
#include "RayTrace/image.h"
#include "RayTrace/Scene.h"
#include "RayTrace/camera.h"


class CAPP
{
public:
	CAPP();

	int OnExecute();
	bool OnInit();
	void OnEvent(SDL_Event* event);
	void OnLoop();
	void OnRender();
	void OnExit();

private:
	void PrintVector(const vec3& inputVector);

private:

	Image m_image;

	RT::Scene m_scene;

	bool isRunning;
	SDL_Window* pWindow;
	SDL_Renderer* pRenderer;

};