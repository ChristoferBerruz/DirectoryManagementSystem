#include "DirectoryManagementSystem.h"
#include <iostream>
#include <fstream>
#include "AreaCodesBook.h"
using namespace std;

int main()
{
	DirectoryManagementSystem dms;
	cout << "Welcome to the Directory Management System" << endl;
	cout << "Please enter the number of files: ";
	int numFile;
	cin >> numFile;

	string* fileNames = new string[numFile];

	cout << "Enter the file names one at a time: " << endl;
	for (int i = 0; i < numFile; i++)
	{
		cin >> fileNames[i];
		try {
			ifstream inputFile(fileNames[i]);
			dms.IngestData(inputFile);
		}
		catch (exception e)
		{
			cout << "Unable to read the file: " << e.what() << endl;
		}
	}

	char response;
	cout << "Querying the Directory Management System (DMS). Enter c to continue. Enter n to stop: ";
	cin >> response;

	while (response != 'n')
	{
		dms.Query();
		dms.DisplayResult();
		cout << "Querying the Directory Management System (DMS). Enter c to continue. Enter n to stop: ";
		cin >> response;
	}

	cout << "Exiting the Directory Management System." << endl;
}