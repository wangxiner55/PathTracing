#include "PointLight.h"

RT::PointLight::PointLight()
{
    m_light_Color = vec3(1.0, 1.0, 1.0);
    m_light_Intensity = 1.0;
    m_light_Location = vec3(0.0, 0.0, 0.0);
}

RT::PointLight::~PointLight()
{
}

bool RT::PointLight::ComputeIllumination(const vec3& intPoint, const vec3& normal, const std::vector<std::shared_ptr<RT::ObjectBase>>& objectList, const std::shared_ptr<RT::ObjectBase>& currentObject, vec3& color, double& intensity)
{
    
    vec3 lightDir = (m_light_Location - intPoint).normalize();

    vec3 startPoint = intPoint;

    double angle = dot(normal, lightDir);

    intensity = std::max(0.0,angle);

    color = m_light_Color * std::max(0.0,angle);

    return true;
}
