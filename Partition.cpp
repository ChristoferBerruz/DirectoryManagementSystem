#include "Partition.h"


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