#pragma once


#include "objectbase.h"
#include "Transform.h"

namespace RT
{
	class ObjectSphere : public ObjectBase
	{
	public:

		ObjectSphere();


		virtual ~ObjectSphere() override;

		virtual bool TestIntersections(const Ray& castRay, vec3& intPoint, vec3& localNormal, vec3& localColor) override;


	private:


	};
}