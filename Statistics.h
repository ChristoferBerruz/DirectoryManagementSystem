#ifndef  STATISTICS_H
#define STATICTIS_H
#include <map>
#include <string>
using namespace std;
class Statistics
{
private:
	map<string, int> frequenciesOfQueryType;
	map<string, int> frequenciesOfServer;
	map<int, map<string, int>> serverStats;
	void UpdateQueryFrequencies(const string& queryType);
	void UpdateServerFrequencies(int serverNum);
	void UpdateQueriesServedByServer(const string& queryType, int serverNum);
	string StatsAsTable(const map<string, int>& dictionary, const string& columnOne, const string& columnTwo);
public:
	void UpdateStats(const string& queryType, int serverNum);
	string GenerateReport();
};
#endif // ! STATISTICS_H
