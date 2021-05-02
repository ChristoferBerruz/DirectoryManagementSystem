#include "Partition.h"
#include <typeinfo>
#include <iostream>
using namespace std;
Partition::Partition(BaseQuery* query, int serverNum)
{
	nextPartition = NULL;
	this->query = query;
	this->serverNum = serverNum;
}

int Partition::GetServerNum() const
{
	return serverNum;
}

Partition* Partition::GetNextPartition() const
{
	return nextPartition;
}

void Partition::SetNextPartition(Partition* partition)
{
	nextPartition = partition;
}

BaseQuery* Partition::GetQuery() const
{
	return query;
}

Partition::~Partition()
{
	if (nextPartition)
		delete nextPartition;
}

ostream& operator<<(ostream& os, Partition& partition)
{
	os << "{severNum: " << partition.serverNum << ", query: " <<
		typeid(*partition.query).name() << "}";
	if (partition.nextPartition)
		os << " -> "  << *partition.nextPartition;
	return os;
}