#include "CommonUtils.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
#include "../proj.win32/WIN32Utils.h"
#endif 

list<string>* CommonUtils::splitString(string &input, string token)
{
	list<string> *res = new list<string>();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
	GBKToUTF(input);
#endif 
	if (input.length() == 0 || token.length() == 0 || input.find(token) == string::npos) {
		res->push_back(input);
	}
	else {
		size_t idx = 0;
		size_t beginIdx = 0;
		do {
			idx = input.find(token, beginIdx);
			if (idx != string::npos) {
				res->push_back(input.substr(beginIdx, idx - beginIdx));
				beginIdx = idx + token.length();
			}
			else {
				res->push_back(input.substr(beginIdx, string::npos));
			}
		} while (idx != string::npos);
	}
	return res;
}