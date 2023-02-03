#pragma once


#include "../Comman/vec3.h"
#include <qbLinAlg-main/qbMatrix.h>
#include "ray.h"


namespace RT
{

	constexpr bool FWDTFORM = true;
	constexpr bool BCKTFORM = false;

	class Transform
	{
	public:

		Transform();
		~Transform();

		Transform(const qbMatrix2<double>& fwd, const qbMatrix2<double>& bck);

		void SetTransform(const vec3& translation, const vec3& rotation, const vec3& scale);

		qbMatrix2<double> GetForward();
		qbMatrix2<double> GetBackward();

		RT::Ray Apply(const RT::Ray& inputRay, bool dirFlag);
		vec3 Apply(const vec3& inputVector, bool dirFlag);

		friend Transform operator* (const RT::Transform& lhs, const RT::Transform& rhs);

		Transform operator= (const Transform& rhs);

		void PrintMatrix(bool dirFlag);

		static void PrintVector(const vec3& vector);


	private:

		void Print(const qbMatrix2<double>& matrix);

	private:
		qbMatrix2<double> m_fwdtfm{ 4,4 };
		qbMatrix2<double> m_bcktfm{ 4,4 };
	};

}