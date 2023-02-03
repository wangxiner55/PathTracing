#include "camera.h"


RT::Camera::Camera()
{
	m_cameraPosition = vec3(0.0,-10.0,0.0);
	m_cameraLookAt = vec3();
	m_cameraUp = vec3(0.0, 0.0, 1.0);
	m_cameraLength = 1.0;
	m_cameraHorzSize = 1.0;
	m_cameraAspectRatio = 1.0;
}

void RT::Camera::SetPosition(const vec3& newPosition)
{
	m_cameraPosition = newPosition;
}

void RT::Camera::SetLookAt(const vec3& newLookAt)
{
	m_cameraLookAt = newLookAt;
}

void RT::Camera::SetUp(const vec3& newUp)
{
	m_cameraUp = newUp;
}

void RT::Camera::SetLength(double newLength)
{
	m_cameraLength = newLength;
}

void RT::Camera::SetHorzSize(double newSize)
{
	m_cameraHorzSize = newSize;
}

void RT::Camera::SetAspect(double newAspect)
{
	m_cameraAspectRatio = newAspect;
}

vec3 RT::Camera::GetPosition()
{
	return m_cameraPosition;
}

vec3 RT::Camera::GetLookAt()
{
	return m_cameraLookAt;
}

vec3 RT::Camera::GetUp()
{
	return m_cameraUp;
}

vec3 RT::Camera::GetU()
{
	return m_projectionScreenU;
}

vec3 RT::Camera::GetV()
{
	return m_projectionScreenV;
}

vec3 RT::Camera::GetScreenCenter()
{
	return m_projectionScreenCenter;
}

double RT::Camera::GetLength()
{
	return m_cameraLength;
}

double RT::Camera::GetHorzSize()
{
	return m_cameraHorzSize;
}

double RT::Camera::GetAspect()
{
	return m_cameraAspectRatio;
}

RT::Ray RT::Camera::GenerateRayt(float proScreenX, float proScreenY)
{
	vec3 screenWorldU = m_projectionScreenCenter + (m_projectionScreenU * proScreenX);
	vec3 screenWorldCoordinate = screenWorldU + (m_projectionScreenV * proScreenY);

	return RT::Ray(m_cameraPosition, screenWorldCoordinate);
}



bool RT::Camera::GenerateRay(float proScreenX, float proScreenY, RT::Ray& cameraRay)
{
	vec3 screenWorldU = m_projectionScreenCenter + (m_projectionScreenU * proScreenX);
	vec3 screenWorldCoordinate = screenWorldU + (m_projectionScreenV * proScreenY);

	cameraRay.m_point1 = m_cameraPosition;
	cameraRay.m_point2 = screenWorldCoordinate;
	cameraRay.m_lab = screenWorldCoordinate - m_cameraPosition;
	return true;
}

void RT::Camera::UpdateCameraGeometry()
{
	m_alignmentVector = m_cameraLookAt - m_cameraPosition;
	m_alignmentVector.normalize();

	m_projectionScreenU = cross(m_alignmentVector, m_cameraUp);
	m_projectionScreenU.normalize();
	m_projectionScreenV = cross(m_projectionScreenU, m_alignmentVector);
	m_projectionScreenV.normalize();

	m_projectionScreenCenter = m_cameraPosition +(m_cameraLength * m_alignmentVector);

	m_projectionScreenU = m_projectionScreenU * m_cameraHorzSize;
	m_projectionScreenV = m_projectionScreenV * (m_cameraHorzSize / m_cameraAspectRatio);

}

