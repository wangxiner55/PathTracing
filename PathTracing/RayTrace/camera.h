#pragma once


#include "../Comman/vec3.h"
#include "ray.h"
#include <math.h>

namespace RT
{
	class Camera
	{
	public:
		Camera();

		void SetPosition(const vec3& newPosition);
		void SetLookAt(const vec3& newLookAt);
		void SetUp(const vec3& newUp);
		void SetLength(double newLength);
		void SetHorzSize(double newSize);
		void SetAspect(double newAspect);



		vec3 GetPosition();
		vec3 GetLookAt();
		vec3 GetUp();
		vec3 GetU();
		vec3 GetV();
		vec3 GetScreenCenter();
		double GetLength();
		double GetHorzSize();
		double GetAspect();

		Ray GenerateRayt(float proScreenX, float proScreenY);
		bool GenerateRay(float proScreenX, float proScreenY, RT::Ray& cameraRay);

		void UpdateCameraGeometry();

	private:

		vec3 m_cameraPosition;
		vec3 m_cameraLookAt;
		vec3 m_cameraUp;
		double m_cameraLength;
		double m_cameraHorzSize;
		double m_cameraAspectRatio;

		vec3 m_alignmentVector;
		vec3 m_projectionScreenU;
		vec3 m_projectionScreenV;
		vec3 m_projectionScreenCenter;



	};
}