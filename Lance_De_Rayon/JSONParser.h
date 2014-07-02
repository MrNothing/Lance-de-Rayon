#pragma once
#include <string>
#include <map>
#include <vector>
#include "utils.h"

class JSONParser
{
public:
	JSONParser(void);
	~JSONParser(void);
	std::map<std::string, serializedData> JSONToMap(std::string obj);
private:
	std::map<std::string, serializedData> parseConvertedJson(std::string data, std::vector<std::string> strings);
	std::string simpleReplace(std::string str, std::string oldValue, std::string newValue);
	int simpleIndexOf(std::string str, std::string pattern);
	int stringToInt(std::string myString);
};

