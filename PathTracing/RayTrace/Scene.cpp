#include "Scene.h"
#include "../Comman/Unit.h"


RT::Scene::Scene()
{
	m_camera.SetPosition(vec3(0.0, -10.0, 0.0));
	m_camera.SetLookAt(vec3(0.0, 0.0, 0.0));
	m_camera.SetUp(vec3(0.0, 0.0, 1.0));
	m_camera.SetHorzSize(0.25);
	m_camera.SetAspect(16.0 / 9.0);
	m_camera.UpdateCameraGeometry();


	m_objectList.push_back(std::make_shared<RT::ObjectSphere>(RT::ObjectSphere()));
	m_objectList.push_back(std::make_shared<RT::ObjectSphere>(RT::ObjectSphere()));
	m_objectList.push_back(std::make_shared<RT::ObjectSphere>(RT::ObjectSphere()));


	RT::Transform TMatrix1, TMatrix2, TMatrix3;
	TMatrix1.SetTransform(vec3(1.5, 0.0, 0.0), vec3(0.0, 0.0, 0.0), vec3(0.50, 1.0, 1.0));
	TMatrix2.SetTransform(vec3(-1.5, 0.0, 0.0), vec3(0.0, 0.0, 0.0), vec3(0.5, 1.0, 1.0));
	TMatrix3.SetTransform(vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 0.0), vec3(1.0, 0.50, 1.0));

	

	m_objectList.at(0)->SetTransformMatrix(TMatrix1);
	m_objectList.at(1)->SetTransformMatrix(TMatrix2);
	m_objectList.at(2)->SetTransformMatrix(TMatrix3);


	m_objectList.at(0)->m_baseColor = vec3(255.0, .0, .0);
	m_objectList.at(1)->m_baseColor = vec3(255.0, 100.0, .0);
	m_objectList.at(2)->m_baseColor = vec3(255.0, .0, 100.0);

	m_lightList.push_back(std::make_shared<RT::PointLight>(RT::PointLight()));
	m_lightList.at(0)->m_light_Location = vec3(5.0, -10.0, -5.0);
	m_lightList.at(0)->m_light_Color = vec3(255.0, 0.0, 255.0);
}


bool RT::Scene::render(Image& outputImage)
{
	int xSize = outputImage.GetXSize();
	int ySize = outputImage.GetYSize();

	RT::Ray cameraRay;
	vec3 intPoint;
	vec3 localNormal;
	vec3 localColor;
	double xFact = 1.0 / (static_cast<double>(xSize) / 2.0);
	double yFact = 1.0 / (static_cast<double>(ySize) / 2.0);
	double minDist = 1e6;
	double maxDist = 0.0;

	for (int x = 0; x < xSize; ++x)
	{
		double cc = 0.0;
		for (int y = 0; y < ySize; ++y)
		{
			double normX = (static_cast<double>(x) * xFact) - 1.0;
			double normY = (static_cast<double>(y) * yFact) - 1.0;

			m_camera.GenerateRay(normX, normY, cameraRay);

			for (auto currentObject : m_objectList)
			{
				bool validInt = currentObject -> TestIntersections(cameraRay, intPoint, localNormal, localColor);

				if (validInt)
				{

					double intensity = 0.0;
					vec3 color;
					bool validIllum = false;
					for (auto currentLight : m_lightList)
					{
						validIllum = currentLight->ComputeIllumination(intPoint, localNormal, m_objectList, currentObject, color, intensity);
					}
					outputImage.SetPixel(x, y, localColor[0] * intensity,localColor[1] * intensity, localColor[2] * intensity);

				}
				else
				{
					//outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);

				}

			}
			
		}
		Clear();
		std::cout << std::setprecision(2) << "Precent : " << x / static_cast<double>(xSize) << "%" << std::endl;

	}

	
	return true;
}