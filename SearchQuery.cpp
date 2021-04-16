#include "SearchQuery.h"

/// <summary>
/// Children can use this function to format their results
/// </summary>
/// <param name="queryResult"></param>
/// <param name="columnOne"></param>
/// <param name="columnTwo"></param>
/// <returns></returns>
string SearchQuery::FormatAsTable(const map<string, int>& queryResult, const string& columnOne, const string& columnTwo)
{
	ostringstream buffer;

	int cellLen = 20;
	buffer << setw(cellLen) << left << columnOne << setw(cellLen) << left << columnTwo << endl;

	map<string, int>::const_iterator currentRecord;

	for (currentRecord = queryResult.begin(); currentRecord != queryResult.end(); currentRecord++)
	{
		buffer << setw(cellLen) << left << currentRecord->first << setw(cellLen) << currentRecord->second << endl;
	}

	return buffer.str();
}