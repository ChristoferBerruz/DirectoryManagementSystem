#include "DirectoryManagementSystem.h"
#include <iostream>
#include <fstream>
#include "AreaCodesBook.h"
using namespace std;

int main()
{
	DirectoryManagementSystem dms;
	cout << "Welcome to the Directory Management System" << endl;

	bool promptUser = true;
	int numFile;
	while (promptUser)
	{
		cout << "Please enter the number of files: ";
		string fileNumber;
		getline(cin, fileNumber);
		try
		{
			numFile = stoi(fileNumber);
			promptUser = false;
		}
		catch (...)
		{
			
		}
	}
	

	string fileName;

	cout << "Enter the file names one at a time: " << endl;
	for (int i = 0; i < numFile; i++)
	{
		getline(cin,fileName);
		try {
			ifstream inputFile(fileName);
			dms.IngestData(inputFile);
		}
		catch (exception e)
		{
			cout << "Unable to read the file: " << e.what() << endl;
		}
	}

	string response;
	cout << "Querying the Directory Management System (DMS). Enter c to continue. Enter n to stop: ";
	getline(cin, response);

	while (response != "n")
	{
		dms.Query();
		dms.DisplayResult();
		cout << "Querying the Directory Management System (DMS). Enter c to continue. Enter n to stop: ";
		getline(cin, response);
	}

	cout << "Exiting the Directory Management System." << endl;
}