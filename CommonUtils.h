#include <string>

#define CREATE_FUNC_WITH_STRING(__TYPE__, para) \
	static __TYPE__* create(std::string para) \
{ \
	__TYPE__ *pRet = new __TYPE__(para); \
if (pRet && pRet->init()) \
	{ \
	pRet->autorelease(); \
	return pRet; \
	} \
	else \
	{ \
	delete pRet; \
	pRet = NULL; \
	return NULL; \
	} \
}

