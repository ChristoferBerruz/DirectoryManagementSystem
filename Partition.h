#ifndef PARTITION_H
#define PARTITION_H
#include "BaseQuery.h"
class Partition
{
private:
	BaseQuery* query;
	int serverNum;
	Partition* nextPartition;
public:
	Partition(BaseQuery* query, int serverNum);
	~Partition();
	int GetServerNum() const;
	Partition* GetNextPartition() const;
	void SetNextPartition(Partition* partition);
	BaseQuery* GetQuery() const;
};
#endif // !PARTITION_H
