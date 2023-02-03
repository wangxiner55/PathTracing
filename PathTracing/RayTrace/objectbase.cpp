#include "objectbase.h"
#include <math.h>

RT::ObjectBase::ObjectBase()
{

}

RT::ObjectBase::~ObjectBase()
{
}

bool RT::ObjectBase::TestIntersections(const Ray& castRay, vec3& intPoint, vec3& localNormal, vec3& localColor)
{
	return false;
}

void RT::ObjectBase::SetTransformMatrix(const RT::Transform& transformMatrix)
{
	m_transformMatrix = transformMatrix;
}

bool RT::ObjectBase::CloseEnough(const double f1, const double f2)
{
	return fabs(f1-f2) < FLT_EPSILON;
}
