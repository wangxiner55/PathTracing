#pragma once



#include "LightBase.h"

namespace RT
{
	class PointLight : public LightBase
	{
	public:

		PointLight();

		virtual ~PointLight() override;

		virtual bool ComputeIllumination(const vec3& intPoint, const vec3& normal,
			const std::vector<std::shared_ptr<RT::ObjectBase>>& objectList,
			const std::shared_ptr<RT::ObjectBase>& currentObject,
			vec3& color, double& intensity);



	};
}