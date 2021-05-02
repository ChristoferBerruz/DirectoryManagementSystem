#include "Statistics.h"
#include <iomanip>
#include <sstream>
#include <algorithm>

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

	int statisticsShown = 0;
	buffer << "Statistics Report for Servers & Queries \n";

	int totalQueries = 0;
	for (auto row : frequenciesOfQueryType)
	{
		totalQueries += row.second;
	}

	buffer << ++statisticsShown << ") Total queries served: " << totalQueries << endl;
	buffer << ++statisticsShown <<  ") Number of queries served by each server \n";
	buffer << StatsAsTable(frequenciesOfServer, "Sever Number", "Number of queries served");
	buffer << ++statisticsShown << ") Frequencies of queries per type\n";
	buffer << StatsAsTable(frequenciesOfQueryType, "Query Type", "Frequency") << endl;

	vector<pair<string, int>>sortedServers = GetSortedKeyVals(frequenciesOfServer);
	if (sortedServers.size() > 0)
	{
		buffer << ++statisticsShown << ") The most BUSY server: ";
		buffer << sortedServers[0].first << " with " << sortedServers[0].second << " queries\n";
	}

	if (sortedServers.size() > 1)
	{
		buffer << ++statisticsShown << ") the most IDLE server: ";
		buffer << sortedServers.back().first << " with " << sortedServers.back().second << " queries\n";
	}

	vector<pair<string, int>> sortedQueries = GetSortedKeyVals(frequenciesOfQueryType);
	if (sortedQueries.size() > 0)
	{
		buffer << ++statisticsShown << ") The MOST served type of query: ";
		buffer << sortedQueries[0].first << " with " << sortedQueries[0].second << " appearances\n";
	}

	if (sortedQueries.size() > 1)
	{
		buffer << ++statisticsShown << ") The LEAST served type of query: ";
		buffer << sortedQueries.back().first << " with " << sortedQueries.back().second << " appearances\n";
	}
	return buffer.str();
}


/// <summary>
/// Sorts the dictionary by frequencies
/// </summary>
/// <param name="dictionary"></param>
/// <returns></returns>
vector<pair<string, int>> Statistics::GetSortedKeyVals(const map<string, int>& dictionary)
{
	vector<pair<string, int>> res;
	for (auto row : dictionary)
	{
		res.push_back(row);
	}

	sort(res.begin(), res.end(), [](pair<string, int>& left, pair<string, int>& right) {
		return left.second > right.second;
	});

	return res;
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