#ifndef QUERY_REQUEST_H
#define QUERY_REQUEST_H
#include "BaseQuery.h"
#include <typeinfo>
#include <iostream>
class QueryRequest
{
private:
	BaseQuery* query;
	int duration;
public:
	QueryRequest(BaseQuery* query, int duration):query(query), duration(duration){}
	friend ostream& operator<<(ostream& os, QueryRequest request)
	{
		os << "{ QueryType: " << typeid(*request.query).name() << ", duration: " << request.duration << " }";
		return os;
	}
	BaseQuery* GetQuery() { return query; }
	int GetDuration() { return duration; }
};
#endif