#include "TimingWheel.h"
#include <iostream>
#include <typeinfo>

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
		cout << "[NEW PARTITION] No partition in slot. Allocating a new partition at " << slotNum << endl;
		wheelSlots[slotNum] = new Partition(query, serverNum);
	}
	else {
		// Continue until you find end of the linked list
		while (partition->GetNextPartition() != NULL)
		{
			partition = partition->GetNextPartition();
		}
		cout << "[APPEND PARTITION] Appending partition at the end of the partition at " << slotNum << endl;
		partition->SetNextPartition(new Partition(query, serverNum));
	}
}

void TimingWheel::Schedule(DirectoryManagementSystem& dms, queue<BaseQuery*>& queryQueue, queue<int>& availableServers)
{
	// First, serve the current slot
	Partition* currentPartition = wheelSlots[currentSlot];

	cout << "+++ TimingWheel scheduling at " << currentSlot << " +++" << endl;
	if (!currentPartition)
		cout << "[NOTHING TO SERVE] No partitions to process in current slot\n";
	while (currentPartition)
	{
		BaseQuery* query = currentPartition->GetQuery();
		string result = query->Execute(dms.GetContacts());
		cout << "[SERVE] Serving a query.\n";
		cout << "[QUERY RES]\n" << result << endl;
		cout << "[FREEING SERVER] Server number " << currentPartition->GetServerNum() << endl;
		availableServers.push(currentPartition->GetServerNum());
		stats.UpdateStats(typeid(*query).name(), currentPartition->GetServerNum());
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

	cout << "+++ END +++ " << endl << endl << endl;
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

string TimingWheel::GetInternalStats()
{
	return stats.GenerateReport();
}

/// <summary>
/// Simply show the status of the timing wheel by looking at the partitions
/// </summary>
/// <returns></returns>
string TimingWheel::PrintStatus()
{
	ostringstream buffer;

	buffer << "--- Status of timing Wheel ---" << endl;
	for (int idx = 0; idx < wheelSlots.size(); idx++)
	{
		buffer << idx << " -> ";
		if (wheelSlots[idx])
			buffer << *wheelSlots[idx];
		else
			buffer << "NULL";
		buffer << endl;
	}

	buffer << "--- END ---\n\n";

	return buffer.str();
}

ostream& operator<<(ostream& os, TimingWheel& wheel)
{
	os << wheel.PrintStatus();
	return os;
}
