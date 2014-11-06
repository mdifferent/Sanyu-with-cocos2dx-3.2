#ifndef __Sanyu__ScriptProcessor__
#define __Sanyu__ScriptProcessor__

class ScriptProcessor
{
public:
	static ScriptProcessor* getInstance();

	int nextLine();

private:
	ScriptProcessor() {}
	~ScriptProcessor() {}

	static ScriptProcessor* _sharedInstance;
};

#endif