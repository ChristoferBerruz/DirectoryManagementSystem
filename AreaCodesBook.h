#ifndef AREA_CODES_BOOK_H
#define AREA_CODES_BOOK_H
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

class AreaCodesBook
{
private:
	unordered_map<string, string> areaCodesToStates;
	unordered_map<string, vector<string>> statesToAreaCodes;
public:
	AreaCodesBook();
	string GetState(const string& areaCode) const;
	bool IsAreaCodeInState(const string& areaCode, const string& state);
};
#endif
