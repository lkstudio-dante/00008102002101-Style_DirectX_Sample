#include "Factory+Global.h"

namespace Factory
{
	template<typename TObj, typename ...ARGS>
	TObj* CreateObj(const ARGS&& ...args)
	{
		auto pObj = new TObj(args...);
		pObj->Init();

		return pObj;
	}
}
