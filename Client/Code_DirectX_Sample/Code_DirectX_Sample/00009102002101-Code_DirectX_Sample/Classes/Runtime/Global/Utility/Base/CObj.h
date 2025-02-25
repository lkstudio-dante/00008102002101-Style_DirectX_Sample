#pragma once

#include "../../Define/KCDefine+Cpp_Abs.h"

#include "../Interface/IInitializable.h"
#include "../Interface/IReleasable.h"
#include "../Interface/IUpdateable.h"
#include "../Interface/IRenderable.h"

/**
* 객체
*/
class CObj : public virtual IInitializable, 
	public virtual IReleasable, virtual public IUpdateable, public virtual IRenderable
{
public:			// public 함수

	/** 소멸자 */
	virtual ~CObj(void) = 0;
};
