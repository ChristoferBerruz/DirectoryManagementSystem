#include "TimingWheel.h"
#include <iostream>

using namespace std;
TimingWheel::TimingWheel(int maxDelay)
{
	this->maxDelay = maxDelay;
	currentSlot = 0;
	for (int i = 0; i < maxDelay; i++)
	{
		wheelSlots.push_back(NULL);
	}
}

void TimingWheel::Insert(int processingTime, int serverNum, BaseQuery* query)
{
	int slotNum = (currentSlot + processingTime) % maxDelay;
	Partition* partition = wheelSlots[slotNum];
	// If nothing in slot, just allocate partition
	if (!partition)
	{
		wheelSlots[slotNum] = new Partition(query, serverNum);
	}
	else {
		// Continue until you find end of the linked list
		while (partition->GetNextPartition() != NULL)
		{
			partition = partition->GetNextPartition();
		}
		partition->SetNextPartition(new Partition(query, serverNum));
	}
}

void TimingWheel::Schedule(DirectoryManagementSystem& dms, queue<BaseQuery*>& queryQueue, queue<int>& availableServers)
{
	// First, serve the current slot
	Partition* currentPartition = wheelSlots[currentSlot];
	while (currentPartition)
	{
		BaseQuery* query = currentPartition->GetQuery();
		string result = query->Execute(dms.GetContacts());
		cout << "Serving a query. Result: " << endl << result << endl;
		cout << "Server number: " << currentPartition->GetServerNum() << " became available\n";
		availableServers.push(currentPartition->GetServerNum());
		currentPartition = currentPartition->GetNextPartition();
	}
	
	// Clear it, because it was serve
	ClearCurrentSlot();

	// Allocate until no more servers available and queryQueue is not empty
	while (!availableServers.empty() && !queryQueue.empty())
	{
		Insert(1, availableServers.front(), queryQueue.front());
		queryQueue.pop();
		availableServers.pop();
	}
}

void TimingWheel::ClearCurrentSlot()
{
	delete wheelSlots[currentSlot];
	wheelSlots[currentSlot] = NULL;
}

void TimingWheel::IncreaseInternalTime()
{
	currentSlot = (currentSlot + 1) % maxDelay;
}
