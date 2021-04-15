#include "DisplayQuery.h"
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