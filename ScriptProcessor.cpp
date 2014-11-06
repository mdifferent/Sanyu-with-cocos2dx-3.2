#include "ScriptProcessor.h"

ScriptProcessor* ScriptProcessor::_sharedInstance = new ScriptProcessor();
ScriptProcessor* ScriptProcessor::getInstance()
{
	if (_sharedInstance == nullptr)
		_sharedInstance = new ScriptProcessor();
	return _sharedInstance;
}

int ScriptProcessor::nextLine()
{
	return 0;
}