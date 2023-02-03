#include "Transform.h"

RT::Transform::Transform()
{
	m_bcktfm.SetToIdentity();
	m_fwdtfm.SetToIdentity();
}

RT::Transform::~Transform()
{
}

RT::Transform::Transform(const qbMatrix2<double>& fwd, const qbMatrix2<double>& bck)
{
	if ((fwd.GetNumRows() != 4) || (fwd.GetNumCols() != 4) || (bck.GetNumRows() != 4) || (bck.GetNumCols() != 4))
	{
		throw std::invalid_argument("Cannot construct Tranform, inputs are not all 4x4");
	}

	m_fwdtfm = fwd;
	m_bcktfm = bck;
}

void RT::Transform::SetTransform(const vec3& translation, const vec3& rotation, const vec3& scale)
{

	qbMatrix2<double> translationMatrix{ 4,4 };
	qbMatrix2<double> rotationMatrixX  { 4,4 };
	qbMatrix2<double> rotationMatrixY  { 4,4 };
	qbMatrix2<double> rotationMatrixZ  { 4,4 };
	qbMatrix2<double> scaleMatrix      { 4,4 };

	translationMatrix.SetToIdentity();
	rotationMatrixX.SetToIdentity();
	rotationMatrixY.SetToIdentity();
	rotationMatrixZ.SetToIdentity();
	scaleMatrix.SetToIdentity();


	translationMatrix.SetElement(0, 3, translation[0]);
	translationMatrix.SetElement(1, 3, translation[1]);
	translationMatrix.SetElement(2, 3, translation[2]);


	//rotationMatrix ZYX;
	rotationMatrixZ.SetElement(0, 0, cos(rotation[2]));
	rotationMatrixZ.SetElement(0, 1, sin(rotation[2]));
	rotationMatrixZ.SetElement(1, 0, -sin(rotation[2]));
	rotationMatrixZ.SetElement(1, 1, cos(rotation[2]));

	rotationMatrixY.SetElement(0, 0, cos(rotation[1]));
	rotationMatrixY.SetElement(0, 2, -sin(rotation[1]));
	rotationMatrixY.SetElement(2, 0, sin(rotation[1]));
	rotationMatrixY.SetElement(2, 2, cos(rotation[1]));

	rotationMatrixX.SetElement(1, 1, cos(rotation[0]));
	rotationMatrixX.SetElement(1, 2, sin(rotation[0]));
	rotationMatrixX.SetElement(2, 1, -sin(rotation[0]));
	rotationMatrixX.SetElement(2, 2, cos(rotation[0]));

	//scaleMatrix;
	scaleMatrix.SetElement(0, 0, scale[0]);
	scaleMatrix.SetElement(1, 1, scale[1]);
	scaleMatrix.SetElement(2, 2, scale[2]);

	m_fwdtfm = translationMatrix * scaleMatrix * rotationMatrixX * rotationMatrixY * rotationMatrixZ;
	m_bcktfm = m_fwdtfm;
	m_bcktfm.Inverse();


}



qbMatrix2<double> RT::Transform::GetForward()
{
	return m_fwdtfm;
}

qbMatrix2<double> RT::Transform::GetBackward()
{
	return m_bcktfm;
}

RT::Ray RT::Transform::Apply(const RT::Ray& inputRay, bool dirFlag)
{
	RT::Ray outputRay;

	if (dirFlag)
	{
		outputRay.m_point1 = this->Apply(inputRay.m_point1, RT::FWDTFORM);
		outputRay.m_point2 = this->Apply(inputRay.m_point2, RT::FWDTFORM);
		outputRay.m_lab = outputRay.m_point2 - outputRay.m_point1;
	}
	else
	{
		outputRay.m_point1 = this->Apply(inputRay.m_point1, RT::BCKTFORM);
		outputRay.m_point2 = this->Apply(inputRay.m_point2, RT::BCKTFORM);
		outputRay.m_lab = outputRay.m_point2 - outputRay.m_point1;
	}
	return outputRay;
}

vec3 RT::Transform::Apply(const vec3& inputVector, bool dirFlag)
{
	std::vector<double> tempData{ inputVector[0],inputVector[1],inputVector[2],1.0 };
	qbVector<double> tempVector{ tempData };
	qbVector<double> resultVector;

	if (dirFlag)
	{
		resultVector = m_fwdtfm * tempVector;
	}
	else
	{
		resultVector = m_bcktfm * tempVector;
	}

	//qbVector<double> outputVectortemp = {std::vector<double>{resultVector.GetElement(0), resultVector.GetElement(1), resultVector.GetElement(2)}};
	vec3 outputVector = vec3(resultVector.GetElement(0), resultVector.GetElement(1), resultVector.GetElement(2));

	return outputVector;
}


namespace RT
{
	RT::Transform operator* (const RT::Transform& lhs, const RT::Transform& rhs)
	{
		qbMatrix2<double> fwdResult = lhs.m_fwdtfm * rhs.m_fwdtfm;

		qbMatrix2<double> bckResult = fwdResult;
		bckResult.Inverse();

		RT::Transform finalResult(fwdResult, bckResult);
		return finalResult;
	}
}

namespace RT
{
	RT::Transform RT::Transform::operator= (const RT::Transform & rhs)
	{
		if (this != &rhs)
		{
			m_fwdtfm = rhs.m_fwdtfm;
			m_bcktfm = rhs.m_bcktfm;
		}
		return *this;
	}
}


void RT::Transform::PrintMatrix(bool dirFlag)
{
	if (dirFlag)
	{
		Print(m_fwdtfm);
	}
	else
	{
		Print(m_bcktfm);
	}
}

void RT::Transform::PrintVector(const vec3& vector)
{
	std::cout << vector;
}

void RT::Transform::Print(const qbMatrix2<double>& matrix)
{
	int nRows = matrix.GetNumRows();
	int nCols = matrix.GetNumCols();
	for (int row = 0; row < nRows; ++row)
	{
		for (int col = 0; col < nCols; ++col)
		{
			std::cout << std::fixed << std::setprecision(3) << matrix.GetElement(row, col) << " ";
		}
	}

}

