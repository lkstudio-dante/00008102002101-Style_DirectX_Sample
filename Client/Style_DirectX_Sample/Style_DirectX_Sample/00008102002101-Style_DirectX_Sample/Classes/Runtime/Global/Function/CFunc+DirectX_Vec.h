#pragma once

#include "../Define/KCDefine+DirectX_Abs.h"

namespace CFunc
{
	/** GL 벡터 -> D3D 벡터로 변환한다 */
	D3DXVECTOR3 GLToD3DVec(const glm::vec3& a_rstSender);

	/** D3D 벡터 -> GL 벡터로 변환한다 */
	glm::vec3 D3DToGLVec(const D3DXVECTOR3& a_rstSender);
};
