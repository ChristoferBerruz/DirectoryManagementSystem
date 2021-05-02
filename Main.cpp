#include "DirectoryManagementSystem.h"
#include "TimingWheel.h"
#include <iostream>
#include "BaseQuery.h"
#include "SearchPersonByName.h"
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


UserInput getUserInput();
queue<BaseQuery*> generateQueryQueue(int queryNum);

int main()
{
	DirectoryManagementSystem dms;
	TimingWheel wheel(10);
	int totalSimulationTime = 0;
	int simulationTime = 10;

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

	queue<BaseQuery*> queryQueue = generateQueryQueue(userInput.queryNum);
	while (!queryQueue.empty())
	{
		wheel.Schedule(dms, queryQueue, availableServers);
		cout << wheel;
		wheel.IncreaseInternalTime();
		totalSimulationTime++;
	}

	cout << wheel.GetInternalStats();

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

queue<BaseQuery*> generateQueryQueue(int queryNum)
{
	queue<BaseQuery*> queries;
	for (int i = 0; i < queryNum; i++)
	{
		queries.push(new SearchPersonByName("Freya McDaniel"));
	}
	return queries;
}