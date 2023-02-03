#pragma once


#include <memory>
#include "../Comman/vec3.h"
#include "ray.h"
#include "objectbase.h"


namespace RT
{
	class LightBase
	{
	public:

		LightBase();

		virtual ~LightBase();


		virtual bool ComputeIllumination(const vec3& intPoint, const vec3& normal,
										 const std::vector<std::shared_ptr<RT::ObjectBase>>& objectList,
										 const std::shared_ptr<RT::ObjectBase>& currentObject,
										 vec3& color, double& intensity);




	public:
		vec3 m_light_Color;
		vec3 m_light_Location;
		double m_light_Intensity;



	};
}