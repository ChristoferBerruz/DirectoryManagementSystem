#include "Partition.h"
#include <typeinfo>
#include <iostream>
using namespace std;

/// <summary>
/// A partition OWNS the query pointer passed to it. This is important because once a partition
/// is deleted, we assume the query associated with it must also be eliminated.
/// </summary>
/// <param name="query"></param>
/// <param name="serverNum"></param>
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

/// <summary>
/// Beautifully smart destructor. Given that a Parition is a LinkedList
/// calling delete to a node causes a deletion of the next node. And recursively
/// until the last partition.
/// </summary>
Partition::~Partition()
{
	if (query)
		delete query;
	if (nextPartition)
		delete nextPartition;
}


/// <summary>
/// Returns a simple string representation of a Partition.
/// </summary>
/// <param name="os"></param>
/// <param name="partition"></param>
/// <returns></returns>
ostream& operator<<(ostream& os, Partition& partition)
{
	os << "{severNum: " << partition.serverNum << ", query: " <<
		typeid(*partition.query).name() << "}";
	if (partition.nextPartition)
		os << " -> "  << *partition.nextPartition;
	return os;
}