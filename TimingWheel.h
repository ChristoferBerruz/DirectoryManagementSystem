#ifndef TIMING_WHEEL_H
#define TIMING_WHEEL_H

#include <vector>
#include <queue>
#include "Partition.h"
#include "Statistics.h"
#include "DirectoryManagementSystem.h"
#include "QueryRequest.h"
class TimingWheel
{
private:
	vector<Partition*> wheelSlots;
	int maxDelay;
	int currentSlot;
	Statistics stats;
	ostringstream status;
	int partitionsAllocated;
public:
	TimingWheel(int maxDelay);
	void Insert(int processingTime, int serverNum, BaseQuery* query);
	void Schedule(DirectoryManagementSystem& dms, queue<QueryRequest>& queryQueue, queue<int>& availableServers);
	void ClearCurrentSlot();
	bool IsEmpty();
	void IncreaseInternalTime();
	string GetInternalStats();
	string PrintStatus();
	friend ostream& operator<<(ostream& os, TimingWheel& wheel);
};
#endif // !TIMING_WHEEL_H
