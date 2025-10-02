#include "CFunc+DirectX_Vec.h"

namespace CFunc
{
    D3DXVECTOR3 GLToD3DVec(const glm::vec3& a_rstSender)
    {
        return D3DXVECTOR3(a_rstSender.x, a_rstSender.y, a_rstSender.z);
    }

    glm::vec3 D3DToGLVec(const D3DXVECTOR3& a_rstSender)
    {
        return glm::vec3(a_rstSender.x, a_rstSender.y, a_rstSender.z);
    }
}
