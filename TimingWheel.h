#ifndef TIMING_WHEEL_H
#define TIMING_WHEEL_H

#include <vector>
#include <queue>
#include "Partition.h"
#include "DirectoryManagementSystem.h"
class TimingWheel
{
private:
	vector<Partition*> wheelSlots;
	int maxDelay;
	int currentSlot;
public:
	TimingWheel(int maxDelay);
	void Insert(int processingTime, int serverNum, BaseQuery* query);
	void Schedule(DirectoryManagementSystem& dms, queue<BaseQuery*>& queryQueue, queue<int>& availableServers);
	void ClearCurrentSlot();
	void IncreaseInternalTime();
};
#endif // !TIMING_WHEEL_H