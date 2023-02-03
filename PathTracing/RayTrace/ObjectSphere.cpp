#include "ObjectSphere.h"
#include <cmath>

RT::ObjectSphere::ObjectSphere()
{
}

RT::ObjectSphere::~ObjectSphere()
{
}

bool RT::ObjectSphere::TestIntersections(const Ray& castRay, vec3& intPoint, vec3& localNormal, vec3& localColor)
{
    RT::Ray bckRay = m_transformMatrix.Apply(castRay, BCKTFORM);

    //compute dis
    vec3 vhat = bckRay.m_lab;
    vhat.normalize();

    double b = 2.0 * dot(bckRay.m_point1, vhat);

    double c = dot(bckRay.m_point1, bckRay.m_point1) - 1.0 ;

    double intTest = (b * b) - 4.0 * c;


    vec3 poi;
    if (intTest > 0.0)
    {
        double numSQRT = sqrtf(intTest);
        double t1 = (-b + numSQRT) / 2.0;
        double t2 = (-b - numSQRT) / 2.0;

        if ((t1 < 0.0) || (t2 < 0.0))
        {
            return false;
        }
        else 
        {
            if (t1 < t2)
            {
                poi = bckRay.m_point1 + (vhat * t1);
            }
            else
            {
                poi = bckRay.m_point1 + (vhat * t2);
            }


            intPoint = m_transformMatrix.Apply(poi, FWDTFORM);


            vec3 objOrigin = vec3(0.0, 0.0, 0.0);
            vec3 newObjOrigin = m_transformMatrix.Apply(objOrigin, FWDTFORM);

            localNormal = intPoint - newObjOrigin;
            localNormal.normalize();

            localColor = m_baseColor;
        }
        return true;
    }
    else
    {
        return false;
    }
}
