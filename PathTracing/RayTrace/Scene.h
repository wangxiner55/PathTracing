#pragma once


#include <vector>
#include <SDL/SDL.h>
#include "image.h"
#include "camera.h"
#include "ObjectSphere.h"
#include <memory>
#include "PointLight.h"

namespace RT
{
	class Scene
	{
	public:
		Scene();
		

		bool render(Image& outputImage);



	private:




	private:

		RT::Camera m_camera;


		std::vector<std::shared_ptr<RT::ObjectBase>> m_objectList;

		std::vector<std::shared_ptr<RT::LightBase>>  m_lightList;

	};

}