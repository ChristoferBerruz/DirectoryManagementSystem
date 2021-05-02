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
queue<BaseQuery*> generateQueryQueue(int queryNum);
void printStatus(ofstream& outputFile);
void printFinalStatistics();

// Global variables used
int totalSimulationTime = 0;
const int MAX_DELAY = 10;
DirectoryManagementSystem dms;
TimingWheel wheel(MAX_DELAY);


int main()
{

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

	queue<BaseQuery*> queryQueue = generateQueryQueue(userInput.queryNum);
	while (!queryQueue.empty() || !wheel.IsEmpty())
	{
		wheel.Schedule(dms, queryQueue, availableServers);
		printStatus(outputFile);
		wheel.IncreaseInternalTime();
		totalSimulationTime++;
	}

	printFinalStatistics();

}

void printFinalStatistics()
{
	cout << "--------------------------- FINAL STATISTICS--------------------------------" << endl;
	cout << "Total simulation time: " << totalSimulationTime << endl;
	cout << wheel.GetInternalStats();
}

void printStatus(ofstream& outputFile)
{
	ostringstream buffer;
	buffer << "Simulation time: " << totalSimulationTime << endl;
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

queue<BaseQuery*> generateQueryQueue(int queryNum)
{
	queue<BaseQuery*> queries;

	// 7 query types, so 7 query options
	int totalOptions = 7;
	int option = 0;
	for (int i = 0; i < queryNum; i++)
	{
		option = rand() % totalOptions + 1;
		switch (option)
		{
		case 1:
			queries.push(new DisplayPerson("Freya McDaniel"));
			break;
		case 2:
			queries.push(new DisplayBusiness("Vidoo"));
			break;
		case 3:
			queries.push(new SearchBusinessByEmailOrWebsite("com", "com"));
			break;
		case 4:
			queries.push(new SearchBusinessByPhoneNumber("203"));
			break;
		case 5:
			queries.push(new SearchPeopleLivingInCT("203"));
			break;
		case 6:
			queries.push(new SearchPersonByEmail(".org"));
			break;
		case 7:
			queries.push(new SearchPersonByName("Freya McDaniel"));
			break;
		default:
			throw exception("QUERY NOT SUPPORTED.");
			break;
		}
	}
	return queries;
}