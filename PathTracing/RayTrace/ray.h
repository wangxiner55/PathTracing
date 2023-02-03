#pragma once
#include <qbLinAlg-main/qbVector.h>
#include "../Comman/vec3.h"

namespace RT
{
	class Ray
	{
	public:
		Ray();
		/*Ray(const qbVector<double>& point1, qbVector<double>& point2);*/
		Ray(const vec3& point1, vec3& point2);

		vec3 GetPoint1() const;
		vec3 GetPoint2() const;

		/*qbVector<double> GetPoint1() const;
		qbVector<double> GetPoint2() const;*/

	public:

		vec3 m_point1;
		vec3 m_point2;
		vec3 m_lab;

		/*qbVector<double> m_point1 (3);
		qbVector<double> m_point2 (3);
		qbVector<double> m_lab    (3);*/
	};

}