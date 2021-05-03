#include "TimingWheel.h"
#include <iostream>
#include <typeinfo>

using namespace std;
TimingWheel::TimingWheel(int maxDelay)
{
	this->maxDelay = maxDelay;
	currentSlot = 0;

	// Mark every slot as NULL
	for (int i = 0; i < maxDelay; i++)
	{
		wheelSlots.push_back(NULL);
	}
	partitionsAllocated = 0;
}


/// <summary>
/// Whether the TimingWheel has queries to process
/// </summary>
/// <returns></returns>
bool TimingWheel::IsEmpty()
{
	return partitionsAllocated == 0;
}


/// <summary>
/// Creates a parition and adds it to the corresponding slot in the TimingWheel.
/// If no partition is present at slot, it creates a new partition. Otherwise,
/// it adds it at the end of the list.
/// </summary>
/// <param name="processingTime">Processing time for the query</param>
/// <param name="serverNum">The server to be allocated</param>
/// <param name="query">The query that needs to be processing</param>
void TimingWheel::Insert(int processingTime, int serverNum, BaseQuery* query)
{
	// Mark that a partition was allocated
	partitionsAllocated++;

	// Calculate slot that the partition should be allocated at
	int slotNum = (currentSlot + processingTime) % maxDelay;

	// Get the current partition at slot number
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


/// <summary>
/// Handles serving partitions at current slot, deleting them, and allocating new ones.
/// </summary>
/// <param name="dms">DirectoryManagementSystem that queries need to run onto</param>
/// <param name="queryQueue">The queue of queries</param>
/// <param name="availableServers">All available server</param>
void TimingWheel::Schedule(DirectoryManagementSystem& dms, queue<QueryRequest>& queryQueue, queue<int>& availableServers)
{
	// Get partition at slot
	Partition* currentPartition = wheelSlots[currentSlot];

	cout << "+++ TimingWheel scheduling at " << currentSlot << " +++" << endl;

	// If parititon is null, nothing to serve
	if (!currentPartition)
		cout << "[NOTHING TO SERVE] No partitions to process in current slot\n";

	// Else, serve all partitions in the linked list until you reach the end
	while (currentPartition)
	{
		// Server partition
		BaseQuery* query = currentPartition->GetQuery();
		string result = query->Execute(dms.GetContacts());
		cout << "[SERVE] Serving a query.\n";
		cout << "[QUERY RES]\n" << result << endl;
		cout << "[FREEING SERVER] Server number " << currentPartition->GetServerNum() << endl;
		availableServers.push(currentPartition->GetServerNum());

		// Acknowledge that this partition was served
		partitionsAllocated--;

		// Update states
		stats.UpdateStats(typeid(*query).name(), currentPartition->GetServerNum());

		// Move to the nex partition in LinkedList
		currentPartition = currentPartition->GetNextPartition();
	}

	// Clear it, because it was serve
	ClearCurrentSlot();

	// Allocate until no more servers available and queryQueue is not empty
	while (!availableServers.empty() && !queryQueue.empty())
	{
		QueryRequest request = queryQueue.front();
		Insert(request.GetDuration(), availableServers.front(), request.GetQuery());
		queryQueue.pop();
		availableServers.pop();
	}

	cout << "+++ END +++ " << endl << endl << endl;
}


/// <summary>
/// Clears all parititons in current slot
/// </summary>
void TimingWheel::ClearCurrentSlot()
{
	// Take advantage of cascade deletion of the Partition
	delete wheelSlots[currentSlot];

	// Mark slot as NULL
	wheelSlots[currentSlot] = NULL;
}


/// <summary>
/// Tells the TimingWheel that it needs to 'rotate' one unit in time forward.
/// </summary>
void TimingWheel::IncreaseInternalTime()
{
	currentSlot = (currentSlot + 1) % maxDelay;
}


/// <summary>
/// Returns internal stats of the TimingWheel, useful for simulation.
/// </summary>
/// <returns></returns>
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
