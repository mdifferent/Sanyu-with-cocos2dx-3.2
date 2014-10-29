#include "GlobalConfig.h"

GlobalConfig* GlobalConfig::_sharedInstance = new GlobalConfig();
GlobalConfig* GlobalConfig::getInstance()
{
	if (_sharedInstance == NULL)
		_sharedInstance = new GlobalConfig();
	return _sharedInstance;
}