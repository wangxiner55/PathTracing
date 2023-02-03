#include "LightBase.h"

RT::LightBase::LightBase()
{
}

RT::LightBase::~LightBase()
{
}

bool RT::LightBase::ComputeIllumination(const vec3& intPoint, const vec3& normal, const std::vector<std::shared_ptr<RT::ObjectBase>>& objectList, const std::shared_ptr<RT::ObjectBase>& currentObject, vec3& color, double& intensity)
{
    return false;
}
