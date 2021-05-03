#include "DisplayQuery.h"

/// <summary>
/// Formats a vector by dumping all elements separated by commas
/// </summary>
/// <param name="elements"></param>
/// <returns></returns>
string DisplayQuery::FormatVector(const vector<string>& elements)
{
	ostringstream buffer;
	for (int i = 0; i < elements.size(); i++)
	{
		buffer << elements[i];
		if (i != elements.size() - 1)
			buffer << ", ";
	}

	return buffer.str();
}


/// <summary>
/// Returns a string with fixed spacing between words
/// </summary>
/// <param name="label"></param>
/// <param name="content"></param>
/// <returns></returns>
string DisplayQuery::FormatSimpleLine(const string& label, const string& content)
{
	ostringstream buffer;

	int cellLen = 20;
	buffer << setw(cellLen) << left << label << setw(cellLen) << left << content << endl;
	return buffer.str();
}


/// <summary>
/// Returns a string with fixed spacing between words and padding at the beginning
/// </summary>
/// <param name="label"></param>
/// <param name="content"></param>
/// <returns></returns>
string DisplayQuery::FormatPaddedLine(const string& label, const string& content)
{
	ostringstream buffer;
	int cellLen = 10;
	buffer << setw(cellLen) << right<< "" << setw(cellLen) << left << label << setw(cellLen) << left << content << endl;
	return buffer.str();
}