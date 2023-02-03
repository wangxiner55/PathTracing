#pragma once


#include "../Comman/vec3.h"
#include "ray.h"
#include "Transform.h"


namespace RT
{
	class ObjectBase
	{
	public:
		ObjectBase();
		virtual ~ObjectBase();

		virtual bool TestIntersections(const Ray& castRay, vec3& intPoint, vec3& localNormal, vec3& localColor);


		void SetTransformMatrix(const RT::Transform& transformMatrix);

		bool CloseEnough(const double f1, const double f2);

	public:

		vec3 m_baseColor;

		RT::Transform m_transformMatrix;
	};


}

