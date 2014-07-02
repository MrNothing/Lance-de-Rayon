#include "stdafx.h"
#include "JSONParser.h"


JSONParser::JSONParser(void)
{
}


JSONParser::~JSONParser(void)
{
}

std::map<std::string, serializedData> JSONParser::JSONToMap(std::string obj)
{
	bool inSring = false;
	std::vector<std::string> strings;
		
	std::string objClone = obj;
		
	std::string currentString="";
		
	//first we capture all the strings...
	for(int i=0; i<objClone.size(); i++)
	{
		char c = objClone[i];
			
		if(!inSring)
		{
			if(c=='"')
			{
				inSring = true;
			}
		}
		else
		{
			if(c=='"')
			{
				//Debug.Log("currentString: "+currentString);
				obj = simpleReplace(obj, std::to_string('"')+currentString+'"', strings.size()+"");
				strings.push_back(currentString);
				currentString = "";
				inSring = false;
			}
			else
			{
				currentString+=c;
			}
		}
	}
		
	return parseConvertedJson(obj, strings);
		
}
	
std::map<std::string, serializedData> JSONParser::parseConvertedJson(std::string data, std::vector<std::string> strings)
{
	std::map<std::string, serializedData> res;
		
	int depth = 0;
		
	std::string rawKey="";
	std::string rawValue="";
		
	bool isValue = false;
		
	for(int i=0; i<data.size(); i++)
	{
		if(data[i]=='{')
		{
			depth++;
			if(depth<=1)
			{
				isValue = false;
			}
		}
		else if(data[i]=='}' || data[i]==',')
		{
			if(data[i]!=',')
				depth--;
				
			if(depth<=1)
			{
				isValue = false;
			}
				
			if(depth==0 || (!isValue && data[i]==','))
			{
				//Debug.Log("rawKey: "+rawKey);
				//Debug.Log("rawValue: "+rawValue);
			
				if(simpleIndexOf(rawValue,"{")>=0)
				{
					serializedData data;
					data.childs = parseConvertedJson(rawValue, strings);

					res[strings[stringToInt(rawKey)]] = data;
				}
				else
				{
					serializedData data;
					data.data = strings[stringToInt(rawValue)];
					data.size = 0;

					res[strings[stringToInt(rawKey)]] = data;
				}
					
				rawValue="";
				rawKey="";
			}
		}
		else if(data[i]==':')
		{
			if(depth<=1)
			{
				isValue = true;
			}
		}
		else
		{
			if(isValue)
			{
				rawValue+=data[i];
			}
			else
			{
				rawKey+=data[i];
			}
		}
	}
		
	return res;
}

std::string JSONParser::simpleReplace(std::string str, std::string oldValue, std::string newValue)
{
	unsigned found = str.rfind(oldValue);

	if (found!=std::string::npos)
		str.replace (found,oldValue.length(),newValue);

	return str;
}

int JSONParser::simpleIndexOf(std::string str, std::string pattern)
{
	std::string::size_type loc = str.find( pattern, 0 );
	if( loc != std::string::npos ) {
		return loc;
	} else {
		return -1;
	}
}

int JSONParser::stringToInt(std::string myString)
{
	return atoi(myString.c_str()); //value = 45 
}