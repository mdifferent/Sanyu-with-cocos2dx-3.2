#ifndef __Sanyu__CommonUtils__
#define __Sanyu__CommonUtils__

#include <string>
#include <list>
using namespace std;

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

class CommonUtils {
public:
	static list<string>* splitString(string &input, string token);
};
#endif