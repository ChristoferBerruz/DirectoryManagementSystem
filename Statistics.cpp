#include "Statistics.h"
#include <iomanip>
#include <sstream>

using namespace std;
void Statistics::UpdateQueryFrequencies(const string& queryType)
{
	if (frequenciesOfQueryType.find(queryType) == frequenciesOfQueryType.end())
		frequenciesOfQueryType[queryType] = 0;

	frequenciesOfQueryType[queryType]++;
}

void Statistics::UpdateServerFrequencies(int serverNum)
{
	string server = to_string(serverNum);
	if (frequenciesOfServer.find(server) == frequenciesOfServer.end())
		frequenciesOfServer[server] = 0;

	frequenciesOfServer[server]++;
}

void Statistics::UpdateQueriesServedByServer(const string& queryType, int serverNum)
{
	// First, check if table was created
	auto queryTable = serverStats.find(serverNum);
	if (queryTable == serverStats.end())
		serverStats[serverNum][queryType] = 0;

	auto queryRow = serverStats[serverNum].find(queryType);
	if (queryRow == serverStats[serverNum].end())
		serverStats[serverNum][queryType] = 0;

	serverStats[serverNum][queryType]++;
}

void Statistics::UpdateStats(const string& queryType, int serverNum)
{
	UpdateQueryFrequencies(queryType);
	UpdateServerFrequencies(serverNum);
	UpdateQueriesServedByServer(queryType, serverNum);
}

string Statistics::GenerateReport()
{
	ostringstream buffer;
	buffer << StatsAsTable(frequenciesOfQueryType, "QueryType", "Frequency") << endl;
	buffer << StatsAsTable(frequenciesOfServer, "ServerNum", "Frequency") << endl;
	return buffer.str();
}

string Statistics::StatsAsTable(const map<string, int>& dictionary, const string& columnOne, const string& columnTwo)
{
	ostringstream buffer;

	int cellLen = 40;
	buffer << setw(cellLen) << left << columnOne << setw(cellLen) << left << columnTwo << endl;

	for (auto currentRecord = dictionary.begin(); currentRecord != dictionary.end(); currentRecord++)
	{
		buffer << setw(cellLen) << left << currentRecord->first << setw(cellLen) << currentRecord->second << endl;
	}

	return buffer.str();
}