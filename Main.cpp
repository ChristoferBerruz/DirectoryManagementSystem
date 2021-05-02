#include "DirectoryManagementSystem.h"
#include "TimingWheel.h"
#include <iostream>
#include <fstream>
#include "BaseQuery.h"
#include "DisplayBusiness.h"
#include "DisplayPerson.h"
#include "SearchBusinessByEmailOrWebsite.h"
#include "SearchBusinessByPhoneNumber.h"
#include "SearchPeopleLivingInCT.h"
#include "SearchPersonByEmail.h"
#include "SearchPersonByName.h"
#include "QueryRequest.h"
#include <fstream>
#include <queue>
using namespace std;

struct UserInput
{
	int inputFileNum;
	vector<string> fileNames;
	int serverNum;
	int queryNum;
};


// Routines to be implemented in main module
UserInput getUserInput();
queue<QueryRequest> generateQueryQueue(int queryNum, int maxDelay);
void printStatus(ofstream& outputFile, queue<QueryRequest> requests, int totalSimulationTime, TimingWheel& wheel);
void printFinalStatistics(TimingWheel& wheel, int totalSimulationTime);


int main()
{
	// Needed information for simulation
	int totalSimulationTime = 0;
	const int MAX_DELAY = 10;
	DirectoryManagementSystem dms;
	TimingWheel wheel(MAX_DELAY);

	UserInput userInput = getUserInput();
	for (string fname : userInput.fileNames)
	{
		ifstream inputFile(fname); 
		dms.IngestData(inputFile);
	}

	queue<int> availableServers;
	for (int i = 0; i < userInput.serverNum; i++)
	{
		availableServers.push(i + 1);
	}

	ofstream outputFile("status.txt");

	queue<QueryRequest> queryQueue = generateQueryQueue(userInput.queryNum, MAX_DELAY);
	while (!queryQueue.empty() || !wheel.IsEmpty())
	{
		wheel.Schedule(dms, queryQueue, availableServers);
		printStatus(outputFile, queryQueue,totalSimulationTime, wheel);
		wheel.IncreaseInternalTime();
		totalSimulationTime++;
	}

	printFinalStatistics(wheel, totalSimulationTime);

}

void printFinalStatistics(TimingWheel& wheel, int totalSimulationTime)
{
	cout << "--------------------------- FINAL STATISTICS--------------------------------" << endl;
	cout << "Total simulation time: " << totalSimulationTime << endl;
	cout << wheel.GetInternalStats();
}

void printStatus(ofstream& outputFile, queue<QueryRequest> requests, int totalSimulationTime, TimingWheel& wheel)
{
	ostringstream buffer;
	buffer << "Simulation time: " << totalSimulationTime << endl;
	buffer << "Query Queue: [";
	while (!requests.empty())
	{
		buffer << requests.front();
		buffer << ", ";
		requests.pop();
	}
	buffer << "]" << endl;
	buffer << wheel;
	cout << buffer.str();
	outputFile << buffer.str();
}

UserInput getUserInput()
{

	int numberOfFiles;
	cout << "Please enter the number of file: ";
	cin >> numberOfFiles;
	vector<string> fileNames;
	cout << "Please enter the name of files. One at a time.\n";

	// Dump remaining new line
	string dummy;
	getline(cin, dummy);
	for (int i = 0; i < numberOfFiles; i++)
	{
		cout << "Filename: ";
		string fname;
		getline(cin, fname);
		fileNames.push_back(fname);
	}

	int serverNum;
	cout << "Please enter the number of servers: ";
	cin >> serverNum;

	int queryNum;
	cout << "Please enter the number of queries: ";
	cin >> queryNum;

	UserInput userInput{numberOfFiles, fileNames, serverNum, queryNum};

	return userInput;
}

queue<QueryRequest> generateQueryQueue(int queryNum, int maxDelay)
{
	queue<QueryRequest> queries;

	// 7 query types, so 7 query options
	int totalOptions = 7;
	int option = 0;
	for (int i = 0; i < queryNum; i++)
	{
		option = rand() % totalOptions + 1;
		int dueAfter = rand() % maxDelay + 1;
		BaseQuery* query = NULL;
		switch (option)
		{
		case 1:
			query = new DisplayPerson("Freya McDaniel");
			break;
		case 2:
			query = new DisplayBusiness("Vidoo");
			break;
		case 3:
			query = new SearchBusinessByEmailOrWebsite("com", "com");
			break;
		case 4:
			query = new SearchBusinessByPhoneNumber("203");
			break;
		case 5:
			query = new SearchPeopleLivingInCT("203");
			break;
		case 6:
			query = new SearchPersonByEmail(".org");
			break;
		case 7:
			query = new SearchPersonByName("Freya McDaniel");
			break;
		default:
			throw exception("QUERY NOT SUPPORTED.");
			break;
		}

		if (query)
		{
			QueryRequest request(query, dueAfter);
			queries.push(request);
		}
	}
	return queries;
}