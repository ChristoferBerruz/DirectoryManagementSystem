#include "AreaCodesBook.h"
#include <fstream>
using namespace std;
AreaCodesBook::AreaCodesBook()
{
	ifstream inputFile("areacodes.txt");
	while(!inputFile.eof())
	{
		string areaCode;

		getline(inputFile, areaCode, ',');

		string state;
		getline(inputFile, state);
		areaCodesToStates[areaCode] = state;

		if (statesToAreaCodes.find(state) == statesToAreaCodes.end())
		{
			vector<string> vec{ areaCode };
			statesToAreaCodes[state] = vec;
		}
		else {
			statesToAreaCodes[state].push_back(areaCode);
		}
	}
}

string AreaCodesBook::GetState(const string& areaCode) const
{
	if (areaCodesToStates.find(areaCode) != areaCodesToStates.end())
	{
		return areaCodesToStates.at(areaCode);
	}

	return "";
}

bool AreaCodesBook::IsAreaCodeInState(const string& areaCode, const string& state)
{
	if (statesToAreaCodes.find(state) != statesToAreaCodes.end())
	{
		vector<string> areaCodes = statesToAreaCodes.at(state);
		for (auto code = areaCodes.begin(); code != areaCodes.end(); code++)
		{
			if (*code == areaCode)
				return true;
		}
	}

	return false;
}