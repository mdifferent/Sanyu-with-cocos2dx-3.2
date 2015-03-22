#ifndef __Sanyu__ScriptProcessor__
#define __Sanyu__ScriptProcessor__
#include <list>
#include <tuple>
#include <vector>
#include <map>

using namespace std;

class ScriptProcessor
{
public:
	static ScriptProcessor* getInstance();
	void preprocess();
	int nextLine();

private:
	ScriptProcessor() {}
	~ScriptProcessor() {}

	void scanDirectory();
	void findLabels();
	vector<string> FindAllFileInDir(string folderPath);

	static ScriptProcessor* _sharedInstance;

	list<tuple<string, string, int>> _labelsInFiles;	//filename,labelname,line-in-file
	map<string, string> _variableList;
};

#endif