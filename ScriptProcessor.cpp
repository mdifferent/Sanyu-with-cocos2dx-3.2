#include "ScriptProcessor.h"
#include "DataModel\GlobalConfig.h"
#include "platform\CCFileUtils.h"
#include "CommonUtils.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
#include <regex>  
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID||CC_TARGET_PLATFORM == CC_PLATFORM_IOS)  
#include <regex.h>
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
#include <io.h>  
#else  
#include <dirent.h>  
#include <sys/stat.h>
#endif  

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
#include "../proj.win32/WIN32Utils.h"
#endif 

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

void ScriptProcessor::preprocess()
{
	scanDirectory();
}

void ScriptProcessor::scanDirectory()
{
	auto config = GlobalConfig::getInstance();
	string scriptDir = config->getScriptDirectory();
	auto fileUtil = FileUtils::getInstance();
	fileUtil->addSearchPath(scriptDir);
	if (!fileUtil->isFileExist("script.rpy")) {
		CCLOG("cannot find file: script.rpy.");
		return;
	}

	//Scan script directory
	vector<string> scriptList = FindAllFileInDir(GlobalConfig::getInstance()->getScriptDirectory());
	for (string file : scriptList) {
		string fileContent = FileUtils::getInstance()->getStringFromFile(file);
		list<string> *stmts = CommonUtils::splitString(fileContent, "\r\n");
		if (stmts != nullptr) {
			//Scan each line of script file
			for (string stmt : *stmts) {

			}
			delete stmts;
			stmts = nullptr;
		}
	}

	findLabels();

}

void ScriptProcessor::findLabels()
{
	
}

vector<string> ScriptProcessor::FindAllFileInDir(string folderPath)
{
	vector<string> fileList;
	// Window处理方式  
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
	_finddata_t FileInfo;
	string strfind = folderPath + "\\*";
	long Handle = _findfirst(strfind.c_str(), &FileInfo);
	if (Handle == -1L) {
		log("can not match the folder path");
		return fileList;
	}
	do{
		//判断是否有子目录  
		if (FileInfo.attrib & _A_SUBDIR) {
			//这个语句很重要  
			if ((strcmp(FileInfo.name, ".") != 0) && (strcmp(FileInfo.name, "..") != 0)) {
				string newPath = folderPath + "\\" + FileInfo.name;
				FindAllFileInDir(newPath);
			}
		}
		else {
			fileList.push_back(FileInfo.name);
			log("%s\\%s", folderPath.c_str(), FileInfo.name);
		}
	} while (_findnext(Handle, &FileInfo) == 0);
	_findclose(Handle);
#else  
	CCLog(folderPath.c_str());
	DIR *dp;
	struct dirent* dirp;

	if ((dp = opendir(folderPath.c_str())) == NULL)
	{
		CCLog("can not match the folder path");
		return;
	}
	while ((dirp = readdir(dp)) != NULL)
	{
		struct stat buf;
		stat(folderPath.c_str(), &buf);

		// 如果是目录  
		if (S_ISDIR(buf.st_mode))
		{
			string path;
			if ((strcmp(dirp->d_name, ".") != 0) && (strcmp(dirp->d_name, "..") != 0))
			{
				path = folderPath + "/" + dirp->d_name;
			}
			//如果是目录，递归调用  
			FindAllFile(path);
		}
		else
		{
			fileList.push_back(FileInfo.name);
			// 如果是文件直接打印  
			//CCLog("%s/%s\n", folderPath.c_str(), dirp->d_name);
		}
	}
	CCLog("\n");
	closedir(dp);
#endif  
	return fileList;
}